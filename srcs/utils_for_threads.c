/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:15:24 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 23:50:08 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_say(t_philo *philo, char *str)
{
	struct timeval	tim;

	gettimeofday(&tim, NULL);
	if (!(isoneded(philo)))
	{
		pthread_mutex_lock(philo->talk);
		ft_write(diff_time_ms(philo->infos->start_time, tim), philo->num, str);
		pthread_mutex_unlock(philo->talk);
	}
	else
		return (1);
	return (0);
}

int isoneded(t_philo *philo)
{
	pthread_mutex_lock(philo->talk);
	if (*philo->oneded)
	{
		pthread_mutex_unlock(philo->talk);
		return (1);
	}
	pthread_mutex_unlock(philo->talk);
	return (0);
}

int	create_phs(t_infos *infos, t_philo *philos)
{
	int			i;

	i = -1;
	gettimeofday(&infos->start_time, NULL);
	while (++i < infos->nb_ph)
	{
		philos[i].last_eat = infos->start_time;
		if (pthread_create(&(philos[i].id), \
			NULL, &ft_philo_work, &(philos[i])))
			return (printf("Error with pthread_create\n"));
	}
	return (0);
}

int	too_late(t_philo *philo)
{
	struct timeval	tim;

	gettimeofday(&tim, NULL);
	if (diff_time_ms(philo->last_eat, tim) > philo->infos->ttd)
	{
		pthread_mutex_lock(philo->talk);
		*(philo->oneded) = 1;
		ft_write(diff_time_ms(philo->infos->start_time, tim), philo->num, " died\n");
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->talk);
		return (1);
	}
	return (0);
}

int	ft_all_eat(t_philo *philos)
{
	int	i;

	if (philos[0].infos->nb_eat_max <= 0)
		return (0);
	i = -1;
	while (++i < philos[0].infos->nb_ph)
	{
		if (philos[i].nb_eat < philos[0].infos->nb_eat_max)
			return (0);
	}
	return (1);
}
