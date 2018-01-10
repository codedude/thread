/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:11:03 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 00:11:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "libft.h"
# include "ft_tpool.h"

typedef struct	s_algo {
	int			**data;
	size_t		start;
	size_t		len;
	size_t		size;
}				t_algo;

int				**algo_init(size_t size);
void			algo_free(int **data, size_t size);
int				algo_start(t_tpool *tp, int **data, size_t size, int tasks);
int				algo_fun_init(void *data);
int				algo_fun_do(void *data);

#endif
