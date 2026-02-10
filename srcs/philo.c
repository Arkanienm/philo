/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:05:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/10 15:23:47 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	int	dead_val;

	pthread_mutex_lock(&philo->data->dead_mutex);
	dead_val = philo->data->flag_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (dead_val);
}

int	ft_usleep_secure(int time, t_philo *philo)
{
	int	i;
	int	end;

	i = get_time_in_ms();
	end = i + time;
	while (i < end)
	{
		i = get_time_in_ms();
		if (check_death(philo))
			return (0);
		usleep(500);
	}
	return (1);
}

void	thread_management(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&philo[i].handle, NULL, routine, &philo[i]);
		i++;
	}
	monitor(data, philo);
	i = 0;
	while (i < data->num_philo)
		pthread_join(philo[i++].handle, NULL);
	i = 0;
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&philo[i].lock_time_eat);
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	free(philo);
}

int	ft_error(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (0);
	}
	if (!parsing(argv, data))
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	if (!ft_error(&data, argc, argv))
		return (0);
	if (!init_var(&data, &philo))
	{
		printf("Error\n");
		if (data.fork)
			free(data.fork);
		if (philo)
			free(philo);
		return (0);
	}
	data.start_time = get_time_in_ms();
	while (i < data.num_philo)
	{
		philo[i].last_time_eat = data.start_time;
		i++;
	}
	thread_management(&data, philo);
	return (0);
}
