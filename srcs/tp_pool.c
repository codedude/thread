/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_pool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/01/04 13:27:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "libft.h"
#include "ft_tpool.h"

int				tp_wait_for_queue(t_tpool *tp)
{
	int			i;
	t_tp_data	*tp_data;

	i = 0;
	while ((tp_data = (t_tp_data *)tp_queue_shift(tp->queue)) != NULL)
	{
		if (tp->flag == TP_ON_EXEC)
		{
			if (th_start(&(tp->threads[i]), &th_fun_start) == ERROR)
				return (ERROR);
		}
		tp->threads[i].f = tp_data->f;
		tp->threads[i].data = tp_data->data;
		th_signal(&(tp->threads[i]));
		i++;
	}
	i = 0;
	while (i < tp->size)
	{
		if (tp->threads[i].state == TP_READY)
			i++;
	}
	return (SUCCESS);
}

int			tp_add_task(t_tpool *tp, int (*f)(void *), void *data,
						size_t size)
{
	t_tp_data	tp_data;

	if ((tp_data.data = malloc(size)) == NULL)
		return (ERROR);
	ft_memcpy((void *)tp_data.data, data, size);
	tp_data.f = f;
	if (tp_queue_add(tp->queue, (void *)&tp_data, sizeof(t_tp_data))
		== ERROR)
		return (ERROR);
	return (SUCCESS);
}

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
	if (nb_threads == 0)
		nb_threads = th_getnbr_proc();
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
		tp_destroy(&tmp);
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

