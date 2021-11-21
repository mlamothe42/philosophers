/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:43:10 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 13:48:55 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_is_nums(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
	}
	return (0);
}

int	ft_init(int argc, char **argv, t_infos *infos)
{
	if (argc != 5 && argc != 6)
		return (printf("Error\nUsage : philosophers [number of philosophers] "\
		"[time to die] [time to eat] [time to sleep] (optional) "\
		"[number of time philosophers must eat]\n"));
	if (ft_is_nums(argc, argv))
		return (printf
			("Error\nYou must only use positives numbers as options\n"));
	infos->nb_ph = ft_atoi(argv[1]);
	infos->ttd = ft_atoi(argv[2]);
	infos->tte = ft_atoi(argv[3]);
	infos->tts = ft_atoi(argv[4]);
	infos->nb_eat_max = 0;
	if (argc == 6)
		infos->nb_eat_max = ft_atoi(argv[5]);
	return (0);
}

pthread_mutex_t	**ft_init_forks(t_infos *infos)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = malloc(infos->nb_ph * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < infos->nb_ph)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (NULL);
		pthread_mutex_init(forks[i], NULL);
	}
	return (forks);
}

int	ft_init_ptrs_ph(t_infos *infos, t_philo *philos)
{
	pthread_mutex_t	*talk;
	int				*oneded;
	int				i;

	talk = malloc(sizeof(pthread_mutex_t));
	if (!talk)
		return (1);
	oneded = malloc(sizeof(int));
	if (!oneded)
		return (1);
	i = -1;
	*oneded = 0;
	while (++i < infos->nb_ph)
	{
		pthread_mutex_init(talk, NULL);
		philos[i].talk = talk;
		philos[i].oneded = oneded;
	}
	return (0);
}

t_philo	*ft_init_ph(t_infos *infos, pthread_mutex_t **forks)
{
	int				i;
	t_philo			*philos;

	i = -1;
	philos = malloc(infos->nb_ph * sizeof (t_philo));
	if (!philos)
		return (NULL);
	while (++i < infos->nb_ph)
	{
		philos[i].nb_eat = 0;
		philos[i].num = i + 1;
		philos[i].infos = infos;
		philos[i].fork_l = forks[i];
		if (i != infos->nb_ph - 1)
			philos[i].fork_r = forks[i + 1];
		else
			philos[i].fork_r = forks[0];
	}
	if (ft_init_ptrs_ph(infos, philos))
		return (NULL);
	return (philos);
}
