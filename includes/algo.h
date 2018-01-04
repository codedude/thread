/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:11:03 by vparis            #+#    #+#             */
/*   Updated: 2018/01/04 12:55:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "libft.h"
# include "ft_tpool.h"

typedef struct	s_algo {
	int			**data;
	size_t		size;
	size_t		len;
}				t_algo;

int		**algo_init(size_t size);
void	algo_free(int **data, size_t size);

int		algo_start(t_tpool *tp, int **data, size_t size);
int		algo_fun(void *data);

#endif
