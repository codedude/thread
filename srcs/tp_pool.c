/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_pool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/01/03 16:55:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "libft.h"
#include "ft_tpool.h"

static int	tp_start_all(t_tpool *tp, int flag)
{
	int		i;

	i = 0;
	while (i < tp->size)
	{
		pthread_mutex_init(&(tp->threads[i].mutex), NULL);
		pthread_cond_init(&(tp->threads[i].cond), NULL);
		if (flag == TP_ON_START)
		{
			if (th_start(&(tp->threads[i]), &th_fun_start) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

t_tpool	*tp_create(int nb_threads, int flag)
{
	t_tpool	*tmp;

	if (nb_threads < TP_MIN_THREADS || nb_threads > TP_MAX_THREADS
		|| flag < 0 || flag > 1)
		return (NULL);
	if ((tmp = (t_tpool *)malloc(sizeof(t_tpool))) == NULL)
		return (NULL);
	tmp->size = nb_threads;
	tmp->flag = flag;
	tmp->threads = (t_thread *)ft_memalloc(sizeof(t_thread) * nb_threads);
	if (tmp->threads == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if ((tmp->queue = tp_queue_new()) == NULL)
	{
		free(tmp->threads);
		free(tmp);
		return (NULL);
	}
	if (tp_start_all(tmp, flag) == ERROR)
		tp_destroy(&tmp);
	return (tmp);
}

void	tp_destroy(t_tpool **tp)
{
	int			i;
	t_tpool		*tp_t;
	t_thread	*th_t;

	i = 0;
	tp_t = *tp;
	while (i < tp_t->size)
	{
		th_t = &(tp_t->threads[i]);
		pthread_cancel(th_t->thread);
		pthread_mutex_destroy(&(th_t->mutex));
		pthread_cond_destroy(&(th_t->cond));
		i++;
	}
	free(tp_t->threads);
	tp_queue_del(&(tp_t->queue));
	ft_bzero((void *)tp_t->threads, sizeof(t_thread) * tp_t->size);
	free(tp_t);
	*tp = NULL;
}

