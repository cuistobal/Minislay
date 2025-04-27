#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector
{
    void	**data;
    size_t	size;
    size_t	capacity;
    size_t	elementSize;
}	t_vect;

//
void	init_vector(t_vect *vector, size_t cap, size_t esize)
{
	vector->data = (void **)malloc(cap * sizeof(void *));
    array->size = 0;
    array->capacity = cap;
    array->elementSize = esize;
}

// Free the memory allocated for the dynamic array
void	free_vector(t_vect *vector)
{
    free(array->data);
    array->data = NULL;
    array->size = array->capacity = 0;
}

// Resize the dynamic array when capacity is reached
void resizeDynamicArray(DynamicArray *array, size_t newCapacity) {
    array->data = (void **)realloc(array->data, newCapacity * sizeof(void *));
    array->capacity = newCapacity;
}

// Add an element to the dynamic array
void pushBack(DynamicArray *array, void *value) {
    if (array->size >= array->capacity) {
        resizeDynamicArray(array, array->capacity == 0 ? 1 : array->capacity * 2);
    }
    array->data[array->size] = malloc(array->elementSize);
    memcpy(array->data[array->size], value, array->elementSize);
    array->size++;
}

// Get an element from the dynamic array
void *get(DynamicArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return array->data[index];
}

// Set an element in the dynamic array
void set(DynamicArray *array, size_t index, void *value) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    memcpy(array->data[index], value, array->elementSize);
}

// Get the size of the dynamic array
size_t size(DynamicArray *array)
{
    return array->size;
}

// Get the capacity of the dynamic array
size_t capacity(DynamicArray *array)
{
    return array->capacity;
}

int main(int *argc, char **argv)
{
	char	*text;
    DynamicArray array;


	initDynamicArray(&array, (size_t)atoi(argv[1]), sizeof(char *)); // Initialize with an initial capacity of 2 for int elements


    pushBack(&array, &value1);
    pushBack(&array, &value2);
    pushBack(&array, &value3);

    printf("Size: %zu\n", size(&array));
    printf("Capacity: %zu\n", capacity(&array));

    for (size_t i = 0; i < size(&array); i++) {
        int *val = (int *)get(&array, i);
        printf("Element at index %zu: %d\n", i, *val);
    }

    int newValue = 25;
    set(&array, 1, &newValue);
    int *val = (int *)get(&array, 1);
    printf("Element at index 1 after set: %d\n", *val);

    freeDynamicArray(&array);

    return 0;
}

