/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:05:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/09 18:36:40 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*taking_forks(t_philo	*philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	return (NULL);
}

void	*ft_life(t_philo	*philo)
{
	while (!check_death(philo))
	{
		taking_forks(philo);
		pthread_mutex_lock(&philo->lock_time_eat);
		philo->last_time_eat = get_time_in_ms();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->lock_time_eat);
		print_message(philo, "is eating");
		ft_usleep_secure(philo->data->time_to_eat, philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_message(philo, "is sleeping");
		ft_usleep_secure(philo->data->time_to_sleep, philo);
		print_message(philo, "is thinking");
		usleep(2000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		ft_usleep_secure(philo->data->time_to_die, philo);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	ft_life(philo);
	return (NULL);
}
