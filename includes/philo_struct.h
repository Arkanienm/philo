/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:09:25 by amurtas           #+#    #+#             */
/*   Updated: 2026/02/07 17:34:38 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				flag_dead;
	long			start_time;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_time_eat;
	int				eat_count;
	pthread_mutex_t	lock_time_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		handle;
	t_data			*data;
}	t_philo;

#endif