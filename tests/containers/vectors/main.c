#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct vector
{
	void	*size;
	void	*head;
	void	*tail;
	void	(* helper)(void **, void *, void *);
}	t_vect;

//
void	free_vector(t_vect **vector)
{
	if (!*vector)
		return ;
	else
	{
		if ((*vector)->size)
		{
			free((*vector)->size);
			(*vector)->size = NULL;
		}
		if ((*vector)->head)
		{
			free((*vector)->head);
			(*vector)->head = NULL;
		}
		(*vector)->tail = NULL;			
		(*vector)->helper = NULL;
		free(*vector);
		*vector = NULL;
	}

}

//
void	resize_vector(t_vect **initial, t_vect *new)
{
	size_t			i;
	size_t			j;
	unsigned char	*n;
	unsigned char	*init;

	i = 0;
	j = *(size_t *)(*initial)->size;
	n = (unsigned char *)new->head;
	init = (unsigned char *)(*initial)->head;
	while (i < j)
	{
		n[i] = init[i];
		i++;
	}
	free_vector(initial);
	*initial = new;
}

//
void	init_vector(t_vect **vector, void *esize, void *newsize)
{
	size_t			len;
	size_t			index;
	unsigned char	*initializer;

	index = 0;
	len = *(size_t *)esize * *(size_t *)newsize;
	(*vector)->size = malloc(sizeof(void *));
	if (!(*vector)->size)
		return (free_vector(vector));
	*(size_t *)(*vector)->size = len;
	(*vector)->head = malloc(len);	
	if (!(*vector)->head)
		return (free_vector(vector));
	initializer = (unsigned char *)(*vector)->head;
	while (index < len)
	{
		initializer[index] = 0;
		index++;
	}
	(*vector)->head = (void *)initializer;
	(*vector)->tail = (*vector)->head + (len - 1);
}

//
void	helper(void **ptr, void *elem_size, void *new_size)
{
	t_vect	*vector;
	t_vect	**initial;


	initial = (t_vect **)ptr;
	vector = (t_vect *)malloc(sizeof(t_vect));	
	if (!vector)
		return ;
	vector->size = NULL;
	vector->head = NULL;
	vector->tail = NULL;
	init_vector(&vector, elem_size, new_size);
	if (*initial)
		resize_vector(initial, vector);
	else
		*ptr = vector;
}

t_vect	*create_vector(void (*func)(void **, void *, void *))
{
	t_vect	*new;

	new = malloc(sizeof(t_vect));
	if (!new)
		return (NULL);
	new->size = NULL;
	new->head = NULL;
	new->tail = NULL;
	new->helper = func;
	return (new);
}

//
int main(int argc, char **argv)
{
	size_t	size;
	size_t	elen;
	char	*text;
	t_vect	*vector;

	vector = NULL;
	if (argc > 2)
	{
		text = argv[1];
		for (int i = 2; argv[i]; i++)
		{
			elen = sizeof(char);
			size = (size_t)atoi(argv[i]);
			helper((void *)&vector, (void *)&elen, (void *)&size);
	//		vector->helper((void **)&vector, (void *)&elen, (void *)&size);
            size_t copy_size = strlen(text) < *(size_t *)vector->size ? strlen(text) : *(size_t *)vector->size;
            memcpy((char *)vector->head, text, copy_size);

		//	memcpy((char *)vector->head, text, *(size_t *)vector->size);
			vector->head ? printf("%s\n", (char *)vector->head) : printf("NO shit\n");	
			vector->size ? printf("%ld\n", *(size_t *)vector->size) : printf("NO shit\n");	
			vector->tail ? printf("%s\n", (char *)vector->tail) : printf("NO shit\n");	
		
		}
		free_vector(&vector);
	}
	return 0;
}
