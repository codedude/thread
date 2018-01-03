/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:11:16 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:26:24 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Semi-Secure and optimize memccpy
** Check bad pointer and bad size
** TODO : check overlapping
*/

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char const		*src_t;
	char			*dest_t;
	char			t;

	if (n < 1)
		return (NULL);
	dest_t = (char *)dest;
	src_t = (char const *)src;
	t = (char)c;
	while (--n != 0 && t != *src_t)
		*dest_t++ = *src_t++;
	*dest_t++ = *src_t;
	if (t != *src_t)
		return (NULL);
	return (dest_t);
}
