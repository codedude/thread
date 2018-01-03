/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:36:45 by vparis            #+#    #+#             */
/*   Updated: 2018/01/03 18:03:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_list.h"
#include "ft_tpool.h"

int				tp_wait_for_queue(t_tpool **tp)
{
	int			i;
	t_tp_data	*tp_data;

	i = 0;
	while ((tp_data = (t_tp_data *)tp_queue_shift(&(*tp)->queue)) != NULL)
	{
		if ((*tp)->flag == TP_ON_EXEC)
		{
			if (th_start(&((*tp)->threads[i]), &th_fun_start) == ERROR)
				return (ERROR);
		}
		(*tp)->threads[i].f = tp_data->f;
		(*tp)->threads[i].data = tp_data->data;
		th_signal(&((*tp)->threads[i]));
		i++;
	}
	i = 0;
	while (i < (*tp)->size)
	{
		if ((*tp)->threads[i].state == TP_READY)
			i++;
	}
	return (SUCCESS);
}

t_tp_queue		*tp_queue_new(void)
{
	t_tp_queue	*tmp;

	tmp = (t_tp_queue *)malloc(sizeof(t_tp_queue));
	if (tmp == NULL)
		return (NULL);
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	return (tmp);
}

void			*tp_queue_shift(t_tp_queue **queue)
{
	void	*data;
	t_list	*tmp;

	tmp = (*queue)->head;
	if (tmp != NULL)
	{
		data = tmp->content;
		tmp = tmp->next;
		ft_lstdelone(&((*queue)->head), NULL);
		(*queue)->size -= 1;
		(*queue)->head = tmp;
		if (tmp == NULL)
			(*queue)->tail = NULL;
	}
	else
		data = NULL;
	return (data);
}

int				tp_queue_add(t_tp_queue **queue, int (*f)(void *),
							void *data, size_t size)
{
	t_list		*tmp;
	t_tp_data	tp_data;

	if ((tp_data.data = malloc(size)) == NULL)
		return (ERROR);
	ft_memcpy((void *)tp_data.data, data, size);
	tp_data.f = f;
	tmp = ft_lstnew(&tp_data, sizeof(t_tp_data));
	if (tmp == NULL)
		return (ERROR);
	if ((*queue)->tail == NULL)
	{
		ft_lstadd(&((*queue)->tail), tmp);
		(*queue)->head = (*queue)->tail;
	}
	else
	{
		ft_lstadd(&((*queue)->tail->next), tmp);
		(*queue)->tail = tmp;
	}
	(*queue)->size += 1;
	return (SUCCESS);
}

void			tp_queue_del(t_tp_queue **queue)
{
	ft_lstdel(&((*queue)->head), &ft_lstdel_raw);
	free(*queue);
	*queue = NULL;
}
