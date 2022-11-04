/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:49:44 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/10/08 19:49:46 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_philo {
	int				philo_cnt;
	int				tt_eat;
	int				tt_sleep;
	int				tt_die;
	int				eat_cnt;
	int				p_index;
	int				sim;
	int				*can_start;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_mutex;
}					t_philo;

typedef struct t_main {
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			*philo;
}					t_main;

void		print_msg(t_philo *_main, long long start, char *str);
void		eat(t_philo *data, long long start);
void		ft_usleep(long long time);
long		ft_atoi(const char *str);
void		*routine(void *arg);
long long	ft_gettime(void);
int			arg_cheack(char **av);
int			is_dead(t_main *_main, long long start);
int			simulate(t_main *_main);

#endif 
