#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector {
    void    *size;
    void    *head;
    void    *tail;
    void    (*helper)(void *, void *, void *);
} t_vect;

void resize_vector(t_vect **initial, t_vect *new) {
    if (!initial || !*initial || !new) return;

    size_t i = 0;
    size_t j = *(size_t *)(*initial)->size;
    unsigned char *n = (unsigned char *)new->head;
    unsigned char *init = (unsigned char *)(*initial)->head;

    while (i < j) {
        n[i] = init[i];
        i++;
    }

    free((*initial)->head);
    (*initial)->head = NULL;
    free(*initial);
    *initial = new; // Update the caller's pointer
}

void init_vector(t_vect *vector, void *esize, void *newsize) {
    size_t len = *(size_t *)esize * *(size_t *)newsize;
    vector->size = (void *)len;
    vector->head = malloc(len);
    if (!vector->head) {
        free(vector);
        return;
    }

    unsigned char *initializer = (unsigned char *)vector->head;
    for (size_t index = 0; index < len; index++) {
        initializer[index] = 0;
    }
    vector->tail = vector->head + (len - 1);
}

void helper(void **ptr, void *elem_size, void *new_size) {
    t_vect *initial = *(t_vect **)ptr;
    t_vect *vector = (t_vect *)malloc(sizeof(t_vect));
    if (!vector) return;

    init_vector(vector, elem_size, new_size);
    if (initial) {
        resize_vector((t_vect**)ptr, vector);
    } else {
        *ptr = vector; // Initialize the vector pointer if it's NULL
    }
}

int main(int argc, char **argv) {
    size_t size;
    size_t elen;
    char *text;
    t_vect *vector = NULL;

    if (argc > 2) {
        text = argv[1];
        for (int i = 2; argv[i]; i++) {
            elen = sizeof(char);
            size = atoi(argv[i]);
            helper((void **)&vector, (void *)&elen, (void *)&size);
            memcpy(vector->head, text, *(size_t *)vector->size);
            printf("%s\n", (char *)vector->head);
        }
    }

    // Free the final vector
    if (vector) {
        free(vector->head);
        free(vector);
    }

    return 0;
}

