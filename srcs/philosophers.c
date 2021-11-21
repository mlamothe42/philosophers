/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:38:47 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 13:56:14 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_infos			infos;
	pthread_mutex_t	**forks;
	t_philo			*philos;
	pthread_t		id;

	if (ft_init(argc, argv, &infos))
		return (1);
	forks = ft_init_forks(&infos);
	if (!forks)
		return (1);
	philos = ft_init_ph(&infos, forks);
	if (!philos)
		return (free_ndestroy(infos, forks, philos, 1));
	if (pthread_create(&id, NULL, &ft_controller, philos))
	{
		printf("Error creating controller\n");
		return (free_ndestroy(infos, forks, philos, 1));
	}
	if (pthread_join(id, NULL))
	{
		printf("Error in pthread_join of controller\n");
		return (free_ndestroy(infos, forks, philos, 1));
	}
	return (free_ndestroy(infos, forks, philos, 0));
}
