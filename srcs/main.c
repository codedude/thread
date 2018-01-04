/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:15:22 by valentin          #+#    #+#             */
/*   Updated: 2018/01/04 12:46:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ft_tpool.h"
#include "libft.h"
#include "algo.h"

static int	start(int nb_threads, int flag, size_t size)
{
	t_tpool	*tp;
	int		**data;

	if ((data = algo_init(size)) == NULL)
		return (ERROR);
	if ((tp = tp_create(nb_threads, flag)) == NULL)
	{
		algo_free(data, size);
		return (ERROR);
	}
	printf("Thread pool created\n");
	if (algo_start(tp, data, size) == ERROR)
		printf("Error while running algo_start\n");
	tp_destroy(&tp);
	printf("Thread pool destroyed\n");
	algo_free(data, size);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	int		nb_threads;
	int		flag;
	size_t	size;

	if (argc == 4)
	{
		nb_threads = ft_atoi(argv[1]);
		flag = ft_atoi(argv[2]);
		size = (size_t)ft_atoi(argv[3]);
		if (nb_threads < TP_MIN_THREADS || nb_threads > TP_MAX_THREADS
			|| flag < 0 || flag > 1 || size < 1 || size > 1000000)
		{
			printf("thread : %d <= NB_THREAD <= %d, 0 <= FLAG <= 1"
				"1 <= SIZE <= 1 000 000\n", TP_MIN_THREADS, TP_MAX_THREADS);
			return (ERROR);
		}
		printf("Number of procs available : %d\n", th_getnbr_proc());
		printf("Start application with %d threads, ON_START=%d mode\n\n"
			, nb_threads, flag);
		if (start(nb_threads, flag, size) == ERROR)
			return (ERROR);
	}
	else
		printf("thread : ./thread NB_THREADS FLAG SIZE\n");
	return (SUCCESS);
}
