/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:58:18 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/10/08 19:20:31 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *_main, long long start, char *str)
{
	printf("%llu : %d : %s", ft_gettime() - start, _main ->p_index + 1, str);
}

int	arg_cheack(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if ((ft_atoi(av[i]) <= 0))
			return (0);
		i++;
	}
	return (i);
}

int	simulate(t_main *_main)
{
	static int	end = 0;
	int			i;

	i = 0;
	while (_main ->philo[0].philo_cnt > i)
	{
		if (_main ->philo[i].eat_cnt < 0)
			end++;
		i++;
	}
	if ((_main ->philo[0].philo_cnt < end) && _main ->philo[0].sim == 1)
		return (0);
	return (1);
}

int	is_dead(t_main *_main, long long start)
{
	int	i;

	i = 0;
	while (i < _main ->philo->philo_cnt)
	{
		if (ft_gettime() - _main ->philo[i].last_eat >= _main ->philo[i].tt_die)
		{
			print_msg(&(_main ->philo[i]), start, "Philo is died\n");
			return (0);
		}
		i++;
	}
	return (1);
}
