#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*

Current List of vector functions:

1. void init(Vector *vector, size_t capacity, size_t sizeofElement)
--> handles initializing vector and setting starting fields in the vector struct

2. void push(Vector *vector, void *element)
--> adds an element to the end of the vector

3. void pop(Vector *vector)
--> removes the element at the end of the vector

4. void erase(Vector *vector, size_t index)
--> removes an element at a specific index

5. void *get(Vector *vector, size_t index)
--> retrives an element at a specific index

6. void clear(Vector *vector)
--> sets length of vector to 0 without changing capacity

7. void resize(Vector *vector, size_t capacity)
--> adjusts the current capacity of the vector and reallocates memory accordingly

8. void reverse(Vector *vector)
--> reverses vector by creating a new vector with the reversed order

9. int _compare(void *context, const void *a, const void *b)
--> private helper function for sort to compare to vector elements

10. void sort(Vector *vector)
--> quicksort algorithim to sort a vector

11. void printVector(Vector *vector, const char *format)
--> prints every element of the vector seperated by a ' '

12. bool isEmpty(Vector *vector)
--> checks if the vector length == 0

13. size_t elementSize(Vector *vector)
--> returns the size of the elements in the vector in bytes

14. size_t vectorCapacity(Vector *vector)
--> returns the current capacity of the vector

15. size_t length(Vector *vector)
--> returns current number of elements in the vector

*/

/*
NOTE: the length of the vector is the number of elements currently in the
vector while the capacity is the amount that can be stored without reallocating
more memory
*/

typedef struct
{
    void *elements;
    size_t capacity;
    size_t length;
    size_t sizeOfElement;
} Vector;

/*
the init function should be called immediatly after creating a new
vector. Its arguments are a pointer to that vector, the starting capacity,
and the datatype size of the vector. Note the vector is a homogeneous data
structure so all of the elements have to be of the same type.

As of now the vector only supports 3 datatypes: long, double, and char.
*/

void init(Vector *vector, size_t capacity, size_t sizeofElement)
{
    if (sizeofElement != sizeof(long) && sizeofElement != sizeof(double) && sizeofElement != sizeof(char))
    {
        fprintf(stderr, "Invalid datatype. Try: long, double, or char.\n");
        exit(EXIT_FAILURE);
    }

    vector->capacity = capacity;
    vector->length = 0;
    vector->sizeOfElement = sizeofElement;
    vector->elements = malloc(capacity * vector->sizeOfElement);

    if (vector->elements == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*
push function checks value contained in vector->sizeOfElement and
makes void pointer conversions accordingly. It is VERY important that the
original sizeOfElement values passed as an argument to the init function
is accurate otherwise this push function will convert the values
incorrectly. If the vector length is equal to the vector size then
twice then memory is allocated to double the current capacity. Push adds the
element to the end of the vector.
*/

void push(Vector *vector, void *element)
{
    switch (vector->sizeOfElement)
    {
    case sizeof(long):
    {
        long value = *(long *)element;
        if (sizeof(value) != vector->sizeOfElement)
        {
            fprintf(stderr, "Invalid element size.\n");
            exit(EXIT_FAILURE);
        }
        break;
    }
    case sizeof(double):
    {
        double value = *(double *)element;
        if (sizeof(value) != vector->sizeOfElement)
        {
            fprintf(stderr, "Invalid element size.\n");
            exit(EXIT_FAILURE);
        }
        break;
    }
    case sizeof(char):
    {
        char value = *(char *)element;
        if (sizeof(value) != vector->sizeOfElement)
        {
            fprintf(stderr, "Invalid element size.\n");
            exit(EXIT_FAILURE);
        }
        break;
    }
    default:
        fprintf(stderr, "Unsupported element size.\n");
        exit(EXIT_FAILURE);
    }

    if (vector->length == vector->capacity)
    {
        vector->capacity *= 2;
        vector->elements = realloc(vector->elements, vector->capacity * vector->sizeOfElement);

        if (vector->elements == NULL)
        {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    void *destination = (char *)vector->elements + (vector->length * vector->sizeOfElement);
    memcpy(destination, element, vector->sizeOfElement);

    vector->length++;
}

/*
Pop is a fast operation because the vector does not have to move any memory
*/

void pop(Vector *vector)
{
    if (vector->length == 0)
    {
        fprintf(stderr, "Vector is empty. Cannot pop element.\n");
        exit(EXIT_FAILURE);
    }

    vector->length--;
}

/*
Note deleting an element from the vector by index becomes a more
expensive operation the closer the element is to the beginning of the vector
as the vector has to shift all of the other elements down.
*/

void erase(Vector *vector, size_t index)
{
    if (index >= vector->length)
    {
        fprintf(stderr, "Invalid index.\n");
        exit(EXIT_FAILURE);
    }

    void *element = (char *)vector->elements + (index * vector->sizeOfElement);
    void *nextElement = (char *)element + vector->sizeOfElement;
    size_t numBytesToMove = (vector->length - index - 1) * vector->sizeOfElement;

    memmove(element, nextElement, numBytesToMove);
    vector->length--;
}

/*
get function returns the vector element at the specified index as a void pointer
to retrieve the value being pointed at use something like this assuming
the vector's elements are of type double:

    double index_0 = *(double *)get(&vector2, 0);

*/

void *get(Vector *vector, size_t index)
{
    if (index >= vector->length)
    {
        fprintf(stderr, "Invalid index.\n");
        exit(EXIT_FAILURE);
    }

    char *begin = (char *)vector->elements;
    return (void *)(begin + (index * vector->sizeOfElement));
}

/*
The clear vector function effectivly removes all elements from the
vector, and sets the length of the vector to 0. It does not touch the current
capacity of the vector.
*/

void clear(Vector *vector)
{
    vector->length = 0;
}

/*
The resize function can result in data loss if the new capacity is less
than the current length of the vector.
*/

void resize(Vector *vector, size_t capacity)
{
    vector->capacity = capacity;

    if (vector->capacity < vector->length)
    {
        vector->length = vector->capacity;
    }

    vector->elements = realloc(vector->elements, vector->capacity * vector->sizeOfElement);

    if (vector->elements == NULL && vector->capacity > 0)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*
This function allocates memory for a new array so the space complexity is:
O(2n) where n is the length of the vector
*/

void reverse(Vector *vector)
{
    Vector temp;
    init(&temp, vector->length, vector->sizeOfElement);

    for (size_t i = vector->length; i > 0; i--)
    {
        void *value = get(vector, i - 1);
        push(&temp, value);
    }

    for (size_t i = 0; i < vector->length; i++)
    {
        void *value = get(&temp, i);
        memcpy((char *)vector->elements + (i * vector->sizeOfElement), value, vector->sizeOfElement);
    }

    free(temp.elements);
}

/*
helper function for sort which compares elements of the vector
*/

int _compare(void *context, const void *a, const void *b)
{
    Vector *vector = (Vector *)context;
    size_t index1 = *(size_t *)a;
    size_t index2 = *(size_t *)b;

    void *element1 = get(vector, index1);
    void *element2 = get(vector, index2);

    switch (vector->sizeOfElement)
    {
    case sizeof(long):
    {
        long value1 = *(long *)element1;
        long value2 = *(long *)element2;
        if (value1 < value2)
            return -1;
        if (value1 > value2)
            return 1;
        return 0;
    }
    case sizeof(double):
    {
        double value1 = *(double *)element1;
        double value2 = *(double *)element2;
        if (value1 < value2)
            return -1;
        if (value1 > value2)
            return 1;
        return 0;
    }
    case sizeof(char):
    {
        char value1 = *(char *)element1;
        char value2 = *(char *)element2;
        if (value1 < value2)
            return -1;
        if (value1 > value2)
            return 1;
        return 0;
    }
    default:
        fprintf(stderr, "Unsupported element size.\n");
        exit(EXIT_FAILURE);
    }
}

/*
uses the quicksort algorithm to sort the vector
*/

void sort(Vector *vector)
{
    size_t *indices = malloc(vector->length * sizeof(size_t));
    if (indices == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < vector->length; i++)
    {
        indices[i] = i;
    }

    qsort_s(indices, vector->length, sizeof(size_t), _compare, vector);

    Vector sorted;
    init(&sorted, vector->capacity, vector->sizeOfElement);

    for (size_t i = 0; i < vector->length; i++)
    {
        void *element = get(vector, indices[i]);
        push(&sorted, element);
    }

    memcpy(vector->elements, sorted.elements, vector->length * vector->sizeOfElement);
    vector->length = sorted.length;

    free(sorted.elements);
    free(indices);
}

void printVector(Vector *vector, const char *format)
{
    for (size_t i = 0; i < vector->length; i++)
    {
        char *element = (char *)vector->elements + (i * vector->sizeOfElement);

        if (vector->sizeOfElement == sizeof(long))
        {
            printf(format, *(long *)element);
        }
        else if (vector->sizeOfElement == sizeof(double))
        {
            printf(format, *(double *)element);
        }
        else if (vector->sizeOfElement == sizeof(char))
        {
            printf(format, *(char *)element);
        }
    }
    printf("\n");
}

bool isEmpty(Vector *vector)
{
    return vector->length == 0;
}

size_t vectorElementSize(Vector *vector)
{
    return vector->sizeOfElement;
}

size_t vectorCapacity(Vector *vector)
{
    return vector->capacity;
}

size_t length(Vector *vector)
{
    return vector->length;
}
