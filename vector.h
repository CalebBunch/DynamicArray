#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct
{
    void *elements;
    size_t capacity;
    size_t length;
    size_t sizeOfElement;
} Vector;

void init(Vector *vector, size_t capacity, size_t sizeofElement);
void push(Vector *vector, void *element);
void pop(Vector *vector);
void erase(Vector *vector, size_t index);
void *get(Vector *vector, size_t index);
void clear(Vector *vector);
void resize(Vector *vector, size_t capacity);
void reverse(Vector *vector);
void sort(Vector *vector);
void printVector(Vector *vector, const char *format);
bool isEmpty(Vector *vector);
size_t vectorElementSize(Vector *vector);
size_t vectorCapacity(Vector *vector);
size_t length(Vector *vector);

#endif /* VECTOR_H */
