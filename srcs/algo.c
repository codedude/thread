/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:10:28 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 00:25:23 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_tpool.h"
#include "algo.h"

int		algo_start(t_tpool *tp, int **data, size_t size, int tasks)
{
	size_t		n;
	int			i;
	t_algo		pack[128];

	n = size / tasks;
	i = 0;
	while (i < tasks)
	{
		pack[i].data = data;
		pack[i].size = size;
		pack[i].start = i * n;
		pack[i].len = i < tasks - 1 ? n : n + size % tasks;
		tp_add_task(tp, &algo_fun_init, (void *)&pack[i]);
		i++;
	}
	if (tp_wait_for_queue(tp) == ERROR)
		return (ERROR);
	i = 0;
	while (i < tasks)
	{
		tp_add_task(tp, &algo_fun_do, (void *)&pack[i]);
		i++;
	}
	return (tp_wait_for_queue(tp));
}

int		algo_fun_do(void *data)
{
	size_t	i;
	size_t	j;
	size_t	end;
	t_algo	*algo;

	algo = (t_algo *)data;
	i = algo->start;
	end = i + algo->len;
	while (i < end)
	{
		j = 0;
		while (j < algo->size)
		{
			algo->data[i][j] /= 2;
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int		algo_fun_init(void *data)
{
	size_t	i;
	size_t	end;
	t_algo	*algo;

	algo = (t_algo *)data;
	i = algo->start;
	end = i + algo->len;
	while (i < end)
	{
		ft_memset((void *)algo->data[i], 42, algo->size * sizeof(int));
		i++;
	}
	return (SUCCESS);
}

int		**algo_init(size_t size)
{
	int		**tmp;
	size_t	i;

	if (size < 1 || size > 50000)
		return (NULL);
	if ((tmp = (int **)malloc(size * sizeof(int *))) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if ((tmp[i] = (int *)malloc(size * sizeof(int))) == NULL)
		{
			free(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

void	algo_free(int **data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(data[i]);
		i++;
	}
	free(data);
}
