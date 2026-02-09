/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:05:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/09 18:39:10 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	routine_check(t_philo *philo, t_data *data, int i)
{
	int	elapsed_time;
	pthread_mutex_lock(&philo[i].lock_time_eat);
	elapsed_time = get_time_in_ms() - philo[i].last_time_eat;
	if (elapsed_time > data->time_to_die)
	{
		pthread_mutex_unlock(&philo[i].lock_time_eat);
		print_message(&philo[i], "died");
		pthread_mutex_lock(&data->dead_mutex);
		data->flag_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].lock_time_eat);
	return (0);
}

int	eating_manage(t_data *data, int finished_eating)
{
	if (data->times_must_eat != -1 && data->num_philo == finished_eating)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->flag_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (0);
	}
	return (1);
}

void	monitor(t_data *data, t_philo *philo)
{
	int	i;
	int	finished_eating;

	while (1)
	{
		i = 0;
		finished_eating = 0;
		while (i < data->num_philo)
		{
			if (routine_check(philo, data, i) == 1)
				return ;
			if (data->times_must_eat != -1)
			{
				pthread_mutex_lock(&philo[i].lock_time_eat);
				if (philo[i].eat_count >= data->times_must_eat)
					finished_eating++;
				pthread_mutex_unlock(&philo[i].lock_time_eat);
				i++;
			}
		}
		if (eating_manage(data, finished_eating) == 0)
			return ;
		usleep(1000);
	}
}
