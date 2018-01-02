/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:15:22 by valentin          #+#    #+#             */
/*   Updated: 2018/01/01 13:49:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ft_tpool.h"
#include "libft.h"

static int	start(int nb_threads, int flag)
{
	t_tpool	*tp;

	if ((tp = tp_create(nb_threads, flag)) == NULL)
		return (ERROR);
	printf("Thread pool created\n");
	sleep(1);
	tp_destroy(&tp);
	printf("Thread pool destroyed\n");
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	int	nb_threads;
	int	flag;

	if (argc == 3)
	{
		nb_threads = ft_atoi(argv[1]);
		flag = ft_atoi(argv[2]);
		if (nb_threads < TP_MIN_THREADS || nb_threads > TP_MAX_THREADS
			|| flag < 0 || flag > 1)
		{
			printf("thread : %d <= NB_THREAD <= %d, 0 <= FLAG <= 1\n",
				TP_MIN_THREADS, TP_MAX_THREADS);
			return (ERROR);
		}
		printf("Number of procs available : %d\n", th_getnbr_proc());
		printf("Start application with %d threads, ON_START=%d mode\n\n"
			, nb_threads, flag);
		if (start(nb_threads, flag) == ERROR)
			return (ERROR);
	}
	else
		printf("thread : ./thread NB_THREADS FLAG\n");
	return (SUCCESS);
}
