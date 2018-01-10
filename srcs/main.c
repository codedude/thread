/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:15:22 by valentin          #+#    #+#             */
/*   Updated: 2018/01/11 00:17:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ft_tpool.h"
#include "libft.h"
#include "algo.h"

static int	start(int nb_threads, int flag, size_t size, int tasks)
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
	if (algo_start(tp, data, size, tasks) == ERROR)
		printf("Error while running algo_start\n");
	tp_destroy(&tp);
	algo_free(data, size);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	int		nb_threads;
	int		flag;
	int		tasks;
	size_t	size;

	if (argc == 5)
	{
		nb_threads = ft_atoi(argv[1]);
		flag = ft_atoi(argv[2]);
		tasks = ft_atoi(argv[3]);
		size = (size_t)ft_atoi(argv[4]);
		if (start(nb_threads, flag, size, tasks) == ERROR)
			return (ERROR);
	}
	else
		printf("thread : ./thread NB_THREADS ON TASKS SIZE\n");
	return (SUCCESS);
}
