/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:47:11 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 23:47:56 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	rez;

	rez = 0;
	i = 0;
	minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		++i;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		rez = rez * 10 + (str[i] - 48);
		++i;
	}
	return (rez * minus);
}

int	free_ndestroy(t_infos infos, pthread_mutex_t **forks,
		t_philo *philos, int ret)
{
	int	i;

	i = -1;
	if (forks)
	{	
		while (++i < infos.nb_ph)
		{
			pthread_mutex_destroy(forks[i]);
			if (forks[i])
				free(forks[i]);
		}
	}
	free(forks);
	if (philos)
	{
		pthread_mutex_destroy(philos[0].talk);
		free(philos[0].talk);
		if (philos[0].oneded)
			free(philos[0].oneded);
		free(philos);
	}
	return (ret);
}

long int	diff_time_ms(struct timeval start, struct timeval end)
{
	return (((end.tv_sec * 1000 - start.tv_sec * 1000)) + \
		((end.tv_usec / 1000 - start.tv_usec / 1000)));
}

long int	get_time(void)
{
	struct timeval tim;

	gettimeofday(&tim, NULL);
	return (tim.tv_sec * 1000 + tim.tv_usec / 1000);
}

int	do_wait(long int ms, t_philo *philo)
{
	long int tim;

	tim = get_time();
	while (get_time() - tim < ms)
	{
		usleep(1000);
		if (isoneded(philo))
			return (1);
	}
	if (isoneded(philo))
		return (1);
	return (0);
}
