/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:59:07 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/10/08 19:19:13 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_main *_main, int i)
{
	int	g;

	g = i + 1;
	if (i == _main->philo->philo_cnt)
		g = 0;
	_main->philo[i].left_fork = &(_main->fork_mutex[i]);
	_main->philo[i].right_fork = &(_main->fork_mutex[g]);
}

void	fill_philo(t_philo *_philo, t_main *_main, int id)
{
	long long					start;

	start = ft_gettime();
	_main->philo[id].last_eat = start;
	_main->philo[id].philo_cnt = _philo->philo_cnt;
	_main->philo[id].tt_die = _philo->tt_die;
	_main->philo[id].tt_eat = _philo->tt_eat;
	_main->philo[id].tt_sleep = _philo->tt_sleep;
	_main->philo[id].eat_cnt = _philo->eat_cnt;
	_main->philo[id].p_index = id;
	_main->philo[id].sim = _philo->sim;
	forks(_main, id);
}

t_philo	*philo_init(char **av)
{
	t_philo			*filled;
	int				i;

	i = arg_cheack(av);
	if (ft_atoi(av[1]) >= 201)
		return (NULL);
	filled = malloc(sizeof(t_philo) * 1);
	if (!filled)
		return (NULL);
	if (!i)
		return (NULL);
	filled->philo_cnt = ft_atoi(av[1]);
	filled->tt_die = ft_atoi(av[2]);
	filled->tt_eat = ft_atoi(av[3]);
	filled->tt_sleep = ft_atoi(av[4]);
	filled->eat_cnt = -1;
	filled ->sim = 0;
	if (i == 6)
	{
		filled->eat_cnt = ft_atoi(av[5]);
		filled->sim = 1;
	}
	return (filled);
}

t_main	*create_thread(t_main *_main, t_philo *_philo)
{
	static int			can_start = 0;
	int					i;
	pthread_t			*tid;

	i = 0;
	_main->philo = malloc(sizeof(t_philo) * _philo->philo_cnt);
	_main->fork_mutex = malloc(sizeof(pthread_mutex_t) * _philo->philo_cnt);
	tid = malloc(sizeof(pthread_t) * _philo->philo_cnt);
	while (i < _philo->philo_cnt)
		pthread_mutex_init(&(_main->fork_mutex[i++]), NULL);
	i = -1;
	while (++i < _philo->philo_cnt)
	{
		fill_philo(_philo, _main, i);
		_main->philo[i].can_start = &can_start;
		if (pthread_create(tid + i, NULL, &routine, &(_main->philo[i])) != 0)
			return (0);
	}
	can_start = 1;
	i = 0;
	while (i < _philo->philo_cnt)
		if (pthread_detach(tid[i++]) != 0)
			return (0);
	free(tid);
	return (_main);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_main			*ft_main;
	long long		start;

	if (ac < 5 || ac > 6)
		return (0);
	ft_main = malloc(sizeof(t_main) * 1);
	philo = philo_init(av);
	if (!philo)
		return (0);
	ft_main = create_thread(ft_main, philo);
	start = ft_gettime();
	while (1)
	{
		if (!is_dead(ft_main, start) || !simulate(ft_main))
			return (0);
	}
	return (0);
}
