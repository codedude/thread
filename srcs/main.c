/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:15:22 by valentin          #+#    #+#             */
/*   Updated: 2018/01/05 10:20:40 by vparis           ###   ########.fr       */
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

	if (argc == 5)
	{
		nb_threads = ft_atoi(argv[1]);
		flag = (ft_atoi(argv[2]) << 4) | ft_atoi(argv[3]);
		size = (size_t)ft_atoi(argv[4]);
		if (start(nb_threads, flag, size) == ERROR)
			return (ERROR);
	}
	else
		printf("thread : ./thread NB_THREADS MODE ON SIZE\n");
	return (SUCCESS);
}
