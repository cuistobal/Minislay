#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct vector
{
	void	*size;
	void	*head;
	void	*tail;
	void	(* helper)(void *, void *, void *);
}	t_vect;


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
	free((*initial)->head);
	(*initial)->head = NULL;
	free(*initial);
	*initial = new;
}

void	init_vector(t_vect *vector, void *esize, void *newsize)
{
	size_t			len;
	size_t			index;
	unsigned char	*initializer;

	index = 0;
	len = *(size_t *)esize * *(size_t *)newsize;
	vector->size = (void *)len;
	vector->head = malloc(len);	
	if (!vector->head)
		return free(vector);
	initializer = (unsigned char *)vector->head;
	while (index < len)
	{
		initializer[index] = 0;
		index++;
	}
	vector->tail = vector->head + (len - 1);
}

void	helper(void **ptr, void *elem_size, void *new_size)
{

	size_t	esize;
	size_t	newsize;
	t_vect	*vector;
	t_vect	*initial;


	initial = *(t_vect **)ptr;
	esize = *(size_t *)elem_size;
	newsize = *(size_t *)new_size;
	vector = (t_vect *)malloc(sizeof(t_vect));	
	if (!vector)
		return ;
	init_vector(vector, elem_size, new_size);
	if (initial)
		resize_vector(&initial, vector);
	else
		*ptr = vector;
}

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
			size = atoi(argv[i]);
			helper((void **)&vector, (void *)&elen, (void *)&size);
			memcpy(vector->head, text, *(size_t *)vector->size);	
			printf("%s\n", (char *)vector->head);
		}
	}
	return 0;
}
