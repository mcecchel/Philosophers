/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/27 16:53:42 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Prende le forchette in base al tipo di filosofo (pari/dispari)
static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		print_status(philo, FORK);
		if (philo->table->philos_nbr == 1)
		{
			pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
			return (1);
		}
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
	}
	print_status(philo, FORK);
	return (0);
}

// Filosofi pari: prima destra, poi sinistra
// Filosofi dispari: prima sinistra, poi destra
void	eating(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return ;
	print_status(philo, EAT);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->status);
	philo->last_meal = get_time() - philo->table->is_started;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->status);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left_fork]);
}

// Stampa messaggi di stato in modo thread-safe
void	print_status(t_philo *philo, char *message)
{
	unsigned long	timestamp;

	timestamp = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	if (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0
		|| ft_strcmp(message, DEAD) == 0)
	{
		printf("%s", COLOR_INFO);
		printf("%lu ", timestamp - philo->table->is_started);
		printf("%s", COLOR_SUCCESS);
		printf("[%d] ", philo->id);
		printf("%s", COLOR_RESET);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, THINK);
}
