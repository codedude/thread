/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2017/12/28 17:53:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "ft_tpool.h"

void	*tp_thread_start(void *param)
{
	t_thread	*th;

	th = (t_thread *)param;
	printf("Thread %lu ready\n", th->thread);
	pthread_mutex_lock(&(th->mutex));
	if (pthread_cond_wait(&(th->cond), &(th->mutex)) != 0)
		return (param);
	th->state = TP_BUSY;
	pthread_mutex_lock(&(th->mutex));
	printf("Thread %lu busy\n", th->thread);
	if (th->f != NULL)
		(*th->f)(th->data);
	printf("Thread %lu done\n", th->thread);
	return (param);
}

int		tp_getnbr_proc(void)
{
	return (get_nprocs());
}
