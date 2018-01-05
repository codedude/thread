/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/01/05 14:04:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <sys/sysctl.h>
#else
# include <sys/sysinfo.h>
#endif

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_tpool.h"

static int	get_thread_id(t_tpool *tp, pthread_t id)
{
	int	i;

	i = 0;
	while (i < tp->size)
	{
		if (tp->threads[i].thread == id)
			return (i);
		i++;
	}
	return (0);
}

void		*th_fun_start(void *param)
{
	t_tpool		*tp;
	t_thread	*th;

	tp = (t_tpool *)param;
	th = &(tp->threads[get_thread_id(tp, pthread_self())]);
	while (1)
	{
		pthread_mutex_lock(&(th->mutex));
		while (th->state == TH_READY)
			pthread_cond_wait(&(th->cond), &(th->mutex));
		pthread_mutex_unlock(&(th->mutex));
		pthread_mutex_lock(&(tp->mutex));
		tp->working_threads += 1;
		pthread_mutex_unlock(&(tp->mutex));
		if (th->data->f != NULL)
			(*th->data->f)(th->data->param);
		pthread_mutex_lock(&(th->mutex));
		th->state = TH_READY;
		pthread_mutex_unlock(&(th->mutex));
		pthread_mutex_lock(&(tp->mutex));
		tp->working_threads -= 1;
		if (tp->working_threads == 0)
			pthread_cond_signal(&(tp->cond));
		pthread_mutex_unlock(&(tp->mutex));
	}
	return (param);
}

int			th_start(t_tpool *tp, int i, void *(*f)(void *))
{
	if (pthread_create(&(tp->threads[i].thread), NULL, f, tp) != 0)
		return (ERROR);
	return (SUCCESS);
}

#ifdef __APPLE__

int			th_getnbr_proc(void)
{
	int		mib[2];
	int		maxproc;
	size_t	len;

	mib[0] = CTL_HW;
	mib[1] = HW_NCPU;
	len = sizeof(maxproc);
	sysctl(mib, 2, &maxproc, &len, NULL, 0);
	return (maxproc);
}

#elif __linux

int			th_getnbr_proc(void)
{
	return (get_nprocs());
}

#endif
