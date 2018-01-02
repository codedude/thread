/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:10:28 by vparis            #+#    #+#             */
/*   Updated: 2018/01/02 16:26:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
		pack.f = &algo_fun;
		pack.data = data + (i * (n * size));
		pack.len = size;
		pack.size = i < tp->size - 1 ? n : n + size % tp->size;
		tp_queue_add(&(tp->queue), (void *)&pack, sizeof(pack));
	}
	tp_wait_for_queue(tp);
	return (SUCCESS);
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

int		algo_fun(t_algo *data)
{
	int	i;

	(void)data;
	i = 0;
	while (i < 1000000000)
		i++;
	return (5);
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
