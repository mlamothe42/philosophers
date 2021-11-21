/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:30:45 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 23:46:51 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>

# include <stdlib.h>

# include <unistd.h>

# include <pthread.h>

# include <sys/time.h>

# include <time.h>

typedef struct s_infos
{
	int				nb_ph;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_eat_max;
	struct timeval	start_time;
}				t_infos;

typedef struct s_philo
{
	pthread_t			id;
	int					num;
	int					nb_eat;
	int					*oneded;
	struct timeval		last_eat;
	pthread_mutex_t		*talk;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	t_infos				*infos;
}				t_philo;

int				ft_init(int argc, char **argv, t_infos *infos);

int				ft_atoi(const char *str);

pthread_mutex_t	**ft_init_forks(t_infos *infos);

t_philo			*ft_init_ph(t_infos *infos, pthread_mutex_t **forks);

int				free_ndestroy(t_infos infos, pthread_mutex_t **forks,
					t_philo *philos, int ret);

long int		diff_time_ms(struct timeval start, struct timeval end);

int				do_wait(long int ms, t_philo *philo);

int				too_late(t_philo *philo);

void			*ft_philo_work(void *ph);

void			*ft_controller(void *phs);

int				ft_say(t_philo *philo, char *str);

int				too_late(t_philo *philo);

int				eat(t_philo *philo);

int				ft_all_eat(t_philo *philos);

int				create_phs(t_infos *infos, t_philo *philos);

int				isoneded(t_philo *philo);

void			ft_write(int time, int num, char *str);

char			*ft_itoa(int n);

#endif