/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:10:28 by vparis            #+#    #+#             */
/*   Updated: 2018/01/04 12:52:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_tpool.h"
#include "algo.h"

int		algo_start(t_tpool *tp, int **data, size_t size)
{
	size_t		n;
	int			i;
	t_algo		pack;

	n = size / tp->size;
	i = 0;
	while (i < tp->size)
	{
		pack.data = data + (i * (n * size));
		pack.len = n;
		pack.size = i < tp->size - 1 ? n : n + size % tp->size;
		tp_add_task(tp, &algo_fun, (void *)&pack, sizeof(pack));
		i++;
	}
	tp_wait_for_queue(tp);
	printf("All jobs are done\n");
	return (SUCCESS);
}

int		algo_fun(void *data)
{
	size_t	i;
	t_algo	*algo;

	algo = (t_algo *)data;
	i = 0;
	while (i < 1000000 * algo->len)
		i++;
	return (5);
}

int		**algo_init(size_t size)
{
	int		**tmp;
	size_t	i;

	if (size < 1 || size > 1000000)
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
