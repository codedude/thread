/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/01/03 17:57:47 by vparis           ###   ########.fr       */
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

int		th_signal(t_thread *th)
{
	pthread_mutex_lock(&(th->mutex));
	th->state = TP_BUSY;
	if (pthread_cond_signal(&(th->cond)) != 0)
		return (ERROR);
	pthread_mutex_unlock(&(th->mutex));
	return (SUCCESS);
}

void	*th_fun_start(void *param)
{
	t_thread	*th;

	th = (t_thread *)param;
	printf("Thread %lu ready\n", (t_u64)th->thread);
	pthread_mutex_lock(&(th->mutex));
	while (th->state == TP_READY)
		if (pthread_cond_wait(&(th->cond), &(th->mutex)) != 0)
			return (param);
	pthread_mutex_unlock(&(th->mutex));
	printf("Thread %lu busy\n", (t_u64)th->thread);
	if (th->f != NULL)
		(*th->f)(th->data);
	printf("Thread %lu done\n", (t_u64)th->thread);
	pthread_mutex_lock(&(th->mutex));
	th->state = TP_READY;
	pthread_mutex_unlock(&(th->mutex));
	return (param);
}

int		th_start(t_thread *th, void *(*f)(void *))
{
	if (pthread_create(&(th->thread), NULL, f, th) != 0)
		return (ERROR);
	return (SUCCESS);
}

#ifdef __APPLE__

int		th_getnbr_proc(void)
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

int		th_getnbr_proc(void)
{
	return (get_nprocs());
}

#endif
