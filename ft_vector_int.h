#ifndef FT_VECTOR_INT_H
#define FT_VECTOR_INT_H

#include <stdio.h>
#include <stdlib.h>

typedef int		value_type;

typedef	struct	s_vector_value_type
{
	value_type		*beign;
	value_type		*end;
	value_type		*end_cap;

	//function
	void	(*clear)(struct s_vector_value_type*);
	void	(*destructor)(struct s_vector_value_type*);
	int		(*capacity)(struct s_vector_value_type*);
	int		(*size)(struct s_vector_value_type*);
	void	(*push_back)(struct s_vector_value_type*, const value_type);

}				t_vector_value_type;

void	vector_value_type_clear(t_vector_value_type *v);
void	vector_value_type_destructor(t_vector_value_type *v);
int		vector_value_type_capacity(t_vector_value_type *v);
int		vector_value_type_size(t_vector_value_type *v);
void	vector_value_type_push_back(struct s_vector_value_type*, const value_type x);

void	vector_value_type_constructor(t_vector_value_type *v)
{
	int		n = 10;

	v->beign = malloc(sizeof(value_type) * n);
	if (v->beign == NULL)
	{
		printf("Error: ft_vector: malloc failed\n");
		exit(0);
	}
	v->end = v->beign;
	v->end_cap = v->beign + n;
	//function
	v->clear = vector_value_type_clear;
	v->destructor = vector_value_type_destructor;
	v->capacity = vector_value_type_capacity;
	v->size = vector_value_type_size;
	v->push_back = vector_value_type_push_back;
}

void	vector_value_type_destructor(t_vector_value_type *v)
{
	free(v->beign);
}

void	vector_value_type_clear(t_vector_value_type *v)
{
	v->end = v->beign;
}

int		vector_value_type_capacity(t_vector_value_type *v)
{
	return v->end_cap - v->beign;
}

int		vector_value_type_size(t_vector_value_type *v)
{
	return v->end - v->beign;
}

void	vector_value_type_reserve(t_vector_value_type *v, int n)
{
	if (n > vector_value_type_capacity(v))
	{
		value_type *head;
		value_type *save;
		value_type *dest = malloc(sizeof(value_type) * n);

		save = dest;
		head = v->beign;
		while (head != v->end)
		{
			*dest++ = *head++; 
		}
		free(v->beign);
		v->beign = save;
		v->end = dest;
		v->end_cap = save + n;
	}
}

void	vector_value_type_push_back(t_vector_value_type *v, const value_type x)
{
	if (v->end_cap == 0)
		vector_value_type_reserve(v, 1);
	if (v->end == v->end_cap)
		vector_value_type_reserve(v, vector_value_type_capacity(v) * 2);
	*(v->end) = x;
	v->end++;
}




#endif

/*
void	ft_main()
{
	t_vector_value_type	t_vec;
	t_vector_value_type	*vec = &t_vec;

	vector_value_type_constructor(vec);

	printf("cap %d\n", vec->capacity(vec));

	for (int i = 0; i < 100; i++)
		vec->push_back(vec, i);

	value_type *b = vec->beign;
	value_type *e = vec->end;

	while (b != e)
	{
		printf("v %d\n", *b);
		b++;
	}

	vec->destructor(vec);
}

int		main()
{
	ft_main();
	//system("leaks a.out");
}*/
