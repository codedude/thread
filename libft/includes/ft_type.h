/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:08:37 by valentin          #+#    #+#             */
/*   Updated: 2018/01/02 11:53:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_H
# define FT_TYPE_H

/*
** Own defines of stdlibs
*/

# if !defined(SUCCESS) && !defined(ERROR)
#  define SUCCESS			(0)
#  define ERROR				(-1)
# endif

# ifndef NULL
#  define NULL				((void *)0)
# endif

# define STDIN				STDIN_FILENO
# define STDOUT				STDOUT_FILENO
# define STDERR				STDERR_FILENO

# define NULL_STR			"(null)"

/*
** Common charsets, and some usefull constants
*/

# define CHARSET_DIGIT		"0123456789"
# define CHARSET_LALPHA		"abcdefghijklmnopqrstuvwxyz"
# define CHARSET_UALPHA		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define CHARSET_SPACE		" \t\n\v\r\f"
# define CHARSET_BASE_2		"01"
# define CHARSET_BASE_8		"01234567"
# define CHARSET_BASE_10	"0123456789"
# define CHARSET_BASE_16L	"0123456789abcdef"
# define CHARSET_BASE_16U	"0123456789ABCDEF"
# define CHARSET_BASE_16	"0123456789abcdefABCDEF"
# if !defined(INT_MIN) && !defined(INT_MAX)
#  define INT_MIN			(-INT_MAX -1)
#  define INT_MAX			(+2147483647)
# endif
# if !defined(INT64_MIN) && !defined(INT64_MAX)
#  define INT64_MIN			(-INT64_MAX -1L)
#  define INT64_MAX			(+9223372036854775807L)
# endif

/*
** Own types
*/

typedef void				t_void;
typedef char				t_i8;
typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef short				t_i16;
typedef int					t_i32;
typedef unsigned int		t_u32;
typedef long int			t_i64;
typedef unsigned long int	t_u64;
typedef float				t_f32;
typedef double				t_f64;
typedef enum				e_bool
{
	False, True
}							t_bool;

#endif
