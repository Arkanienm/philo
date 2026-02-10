/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:09:24 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/10 15:38:18 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i >= 11)
		return (0);
	return (1);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			time_ms;

	time_ms = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (!philo->data->flag_dead)
	{
		printf("%ld %d %s\n", (get_time_in_ms() - philo->data->start_time),
			philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
