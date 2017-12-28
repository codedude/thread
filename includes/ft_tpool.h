/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:54:21 by valentin          #+#    #+#             */
/*   Updated: 2017/12/28 17:51:43 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TPOOL_H
# define FT_TPOOL_H

# include <pthread.h>

# define TP_MIN_THREADS	1
# define TP_MAX_THREADS	64
# define TP_READY		0
# define TP_BUSY		1
# define TP_ON_EXEC		0
# define TP_ON_START	1

typedef struct		s_thread {
	pthread_t		thread;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	void			*retval;
	int				state;
	void			(*f)(void *data);
	void			*data;
}					t_thread;

typedef struct		s_tpool {
	int				size;
	int				flag;
	t_thread		*threads;
}					t_tpool;

/*
** tp_pool.c
*/

t_tpool				*tp_create(int n, int flag);
void				tp_destroy(t_tpool **tp);
int					tp_add_task(t_tpool *tp, int(*f)(void *data), void *data);
int					tp_wait_for_queue(t_tpool **tp);

/*
** tp_thread.c
*/

void				*tp_thread_start(void *param);
int					tp_getnbr_proc(void);

#endif
