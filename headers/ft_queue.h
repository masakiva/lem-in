#ifndef FT_QUEUE_H
#define FT_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_q_node
{
	struct s_q_node	*next;
	struct s_q_node	*prev;
	void			*content;
}				t_q_node;

typedef struct	s_queue
{
	t_q_node	*head;
	t_q_node	*tail;
	int			size;
}				t_queue;

t_q_node	*ft_q_node_new(void *content);

void	ft_q_node_add_last(t_q_node *tail, t_q_node *node);

void	queue_constructor(t_queue *q);

void	queue_destructor(t_queue *q);

int		queue_empty(t_queue *q);

int		queue_size(t_queue *q);

void	*queue_front(t_queue *q);

void	*queue_back(t_queue *q);

void	queue_push(t_queue *q, void *content);

void	queue_pop(t_queue *q);

#endif

/*
 * #include "ft_queue.h"
#include <stdio.h>

void	main2()
{
	t_queue q_tmp;
	t_queue *q = &q_tmp;

	queue_constructor(q);
	queue_push(q, (void *)3);
	queue_push(q, (void *)4);
	queue_push(q, (void *)5);
	queue_push(q, (void *)6);
	printf("size %d\n", queue_size(q));

	while (queue_size(q) != 0)
	{
		int num = (int)queue_front(q);
		queue_pop(q);
		printf("front %d\n", num);

	}

	//queue_destructor(q);
}

int		main()
{
	main2();
	system("leaks a.out");
}*/

