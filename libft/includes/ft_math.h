/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:05:21 by valentin          #+#    #+#             */
/*   Updated: 2018/01/02 11:34:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "ft_type.h"

# define ZERO_INT	(0)
# define ZERO_FLOAT	(0.0)
# ifndef M_PI
#  define M_PI		(3.141592653589793)
# endif

t_u32				ft_abs(t_i32 n);
t_i32				ft_min(t_i32 a, t_i32 b);
t_i32				ft_max(t_i32 a, t_i32 b);
t_i32				ft_min3(t_i32 a, t_i32 b, t_i32 c);
t_i32				ft_max3(t_i32 a, t_i32 b, t_i32 c);
t_u32				ft_factorial(t_u32 n);
t_u32				ft_fibonacci(t_u32 n);
t_i32				ft_power(t_i32 n, t_i32 power);
t_u32				ft_sqrt(t_u32 n);
int					ft_isprime(t_u32 n);
t_u32				ft_find_next_prime(t_u32 n);

#endif
