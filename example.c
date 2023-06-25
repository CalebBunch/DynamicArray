#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "..\include\vector.h"

int main()
{
    // these two following lines are mandatory when creating a new vector
    // init takes a pointer to a vector, an initial capacity, and the sizeof
    // the intended type.
    Vector v;
    init(&v, 10, sizeof(long));

    // after the vector is no longer needed free must be called to deallocate the memory
    free(v.elements);

    // another example
    Vector vector;
    size_t capacity = 100;
    size_t element_size = sizeof(double);
    init(&vector, capacity, element_size);

    for (double i = 1.0; i <= 100.0; i++)
    {
        push(&vector, &i);
    }

    printVector(&vector, "%lf ");

    printf("Vector length: %lu\n", length(&vector));
    printf("Vector capacity: %lu\n", vectorCapacity(&vector));
    printf("Vector Size of Elements: %lu\n", vectorElementSize(&vector));
    printf("Is vector empty: %s\n", isEmpty(&vector) ? " true " : " false ");

    // get vector[0]
    double index_0 = *(double *)get(&vector, 0);
    printf("vector[0]: %lf\n", index_0);

    // del vector[1]
    erase(&vector, 1);

    // resize vector capacity
    resize(&vector, 200);

    // remove end of vector
    pop(&vector);

    // reverse vector
    reverse(&vector);
    printVector(&vector, "%lf ");

    // sort vector
    sort(&vector);
    printVector(&vector, "%lf ");

    // clear vector
    clear(&vector);

    // do not forget to free the memory at the end
    free(vector.elements);

    return 0;
}