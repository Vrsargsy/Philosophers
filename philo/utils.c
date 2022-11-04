/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:43:30 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/10/08 19:43:32 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *data, long long start)
{
	print_msg(data, start, "Philo is Eating\n");
	data->eat_cnt--;
	data->last_eat = ft_gettime();
	ft_usleep(data->tt_eat - 1);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
}

void	*routine(void *arg)
{
	long long	start;
	t_philo		*data;

	data = (t_philo *)arg;
	while (*(data->can_start) == 0)
		;
	start = ft_gettime();
	if (data->p_index % 2 == 1)
		ft_usleep(data ->tt_eat - 1);
	data ->last_eat = ft_gettime();
	while (1)
	{	
		pthread_mutex_lock(data->right_fork);
		print_msg(data, start, "philo has take a right fork\n");
		if (data->philo_cnt == 1)
			ft_usleep(data ->tt_die + 2);
		pthread_mutex_lock(data->left_fork);
		print_msg(data, start, "philo has take a left fork\n");
		eat(data, start);
		print_msg(data, start, "Philo is Sleeping\n");
		ft_usleep(data->tt_sleep - 1);
		print_msg(data, start, "Philo is Thinking\n");
	}
}

long	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	if (*str == '0')
		return (0);
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return (n * sign);
}

long long	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	long long	start;

	start = ft_gettime();
	while (ft_gettime() - start <= time)
		usleep(100);
}
