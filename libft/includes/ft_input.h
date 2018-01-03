/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:13:38 by valentin          #+#    #+#             */
/*   Updated: 2017/12/24 19:15:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUT_H
# define FT_INPUT_H

# include "ft_type.h"
# include "ft_list.h"

# define BUFF_GNL			(1024)

typedef	struct		s_fd_l {
	struct s_fd_l	*next;
	struct s_fd_l	*previous;
	t_list			*data;
	ssize_t			pos;
	int				fd;
}					t_fd_list;

int					ft_gnl(int const fd, char **line);

#endif
