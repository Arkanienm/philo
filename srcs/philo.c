/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:05:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/06 02:13:04 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_syntax(argv[i]))
			return (0);
		if (ft_atol(argv[i]) < -2147483648 || ft_atol(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	data->num_philo = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	data->times_must_eat = -1;
	if (argv[5])
		data->times_must_eat = (int)ft_atol(argv[5]);
	if (data->num_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	init_var(t_data	*data, t_philo	**philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!*philo)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->fork)
		return (0);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].last_time_eat = 0;
		(*philo)[i].eat_count = 0;
		pthread_mutex_init(&(*philo)[i].lock_time_eat, NULL);
		(*philo)[i].left_fork = &data->fork[i];
		(*philo)[i].right_fork = &data->fork[(i + 1) % data->num_philo];
		i++;
	}
}

long	get_time_in_ms(void)
{
	struct	timeval tv;
	long	time_ms;
	
	time_ms = 0;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->flag_dead)
		printf("%ld %d %s\n", (get_time_in_ms() - philo->data->start_time, str), philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	check_death(void)
{
	
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (!philo->data->flag_dead)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		philo->last_time_eat = get_time_in_ms();
		print_message(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_message(philo, "is thinking");
		usleep(philo->data->time_to_sleep * 1000);
		print_message(philo, "is thinking");
	}
}
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (0);
	if (!parsing(argv, &data))
		return (0);
	if (!init_var(&data, &philo))
		return (0);
	return (0);
}
