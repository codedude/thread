/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:36:45 by vparis            #+#    #+#             */
/*   Updated: 2018/01/02 16:27:15 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_list.h"
#include "ft_tpool.h"

int				tp_wait_for_queue(t_tpool **tp)
{

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
		tmp = tmp->next;
		ft_lstshift(&((*queue)->head), &ft_lstdel_raw);
		(*queue)->size -= 1;
		(*queue)->head = tmp;
		if (tmp->next == NULL)
			(*queue)->tail = NULL;
		data = tmp->content;
	}
	else
		data = NULL;
	return (data);
}

int				tp_queue_add(t_tp_queue **queue, void *data, size_t size)
{
	t_list	*tmp;

	tmp = ft_lstnew(data, size);
	if (tmp == NULL)
		return (ERROR);
	if ((*queue)->tail == NULL)
		ft_lstadd(&((*queue)->tail), tmp);
	else
		ft_lstadd(&((*queue)->tail->next), tmp);
	(*queue)->size += 1;
	return (SUCCESS);
}

void				tp_queue_del(t_tp_queue **queue)
{
	ft_lstdel(&((*queue)->head), &ft_lstdel_raw);
	free(*queue);
	*queue = NULL;
}
