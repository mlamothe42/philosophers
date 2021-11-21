/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:45:14 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/21 23:47:09 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
    	++i;
	return (i);
}

void    ft_putnb_fd(int fd, int nb)
{
	long	nbtmp;

	nbtmp = nb;
	if (nbtmp < 0)
    {
        nbtmp = nbtmp * -1;
	    write(fd, "-", 1);
	}
	if (nbtmp >= 10)
	{
		ft_putnb_fd(fd, nbtmp / 10);
		ft_putnb_fd(fd, nbtmp % 10);
	}
	else
	{
		nbtmp = 48 + nbtmp;
		write(fd, &nbtmp, 1);
	}
}

void	ft_write(int time, int num, char *str)
{
	ft_putnb_fd(1, time);
	write(1, " ", 1);
	ft_putnb_fd(1, num);
	write(1, str, ft_strlen(str));
}