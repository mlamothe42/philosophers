/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:12:09 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 23:40:14 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	if (ft_say(philo,  " has taken a fork\n"))
		return (unlock_forks(philo));
	pthread_mutex_lock(philo->fork_r);
	if (ft_say(philo, " has taken a fork\n"))
		return (unlock_forks(philo));
	gettimeofday(&philo->last_eat, NULL);
	if (ft_say(philo, " is eating\n"))
		return (unlock_forks(philo));
	if (do_wait(philo->infos->tte, philo))
		return (unlock_forks(philo));
	++(philo->nb_eat);
	unlock_forks(philo);
	return (0);
}

int	select_eat(t_philo *philo)
{
	if (philo->num % 2)
	{
		if (eat(philo))
			return (1);
	}
	else
	{
		if (diff_time_ms(philo->infos->start_time, philo->last_eat) < \
			philo->infos->tte / 5)
			if (do_wait(philo->infos->tte / 5, philo))
				return (1);
		if (eat(philo))
			return (1);
	}
	return (0);
}

void	*ft_philo_work(void *ph)
{
	t_philo			*philo;

	philo = ph;
	if (select_eat(philo))
		return (NULL);
	while (1)
	{
		if (ft_say(philo, " is sleeping\n"))
			return (NULL);
		if (do_wait(philo->infos->tts, philo))
			return (NULL);
		if (ft_say(philo, " is thinking\n"))
			return (NULL);
		if (eat(philo))
			return (NULL);
	}
	return (NULL);
}

void	*ft_controller(void *phs)
{
	t_philo	*philos;
	int		i;
	int		j;

	philos = phs;
	if (create_phs(philos[0].infos, philos))
		return (NULL);
	while (1)
	{
		if (ft_all_eat(philos))
			return (NULL);
		i = -1;
		while (++i < philos[0].infos->nb_ph)
		{
			if (too_late(&(philos[i])))
			{
				j = -1;
				while (++j < philos[0].infos->nb_ph)
					pthread_join(philos[j].id, NULL);
				return (NULL);
			}
		}
		usleep(5000);
	}
	return (philos);
}
