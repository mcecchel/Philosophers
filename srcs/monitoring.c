/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:29:55 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/28 14:28:13 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// Monitoraggio per morte e completamento azioni

// Conta filosofi che hanno raggiunto nbr_meals
bool	has_eaten_enough(t_data *table)
{
	int	i;
	int	satisfied_philosophers;
	int	current_meals;

	i = 0;
	satisfied_philosophers = 0;
	while (i < table->philos_nbr)
	{
		current_meals = int_safe_read(&table->philo[i].status,
				&table->philo[i].meals_eaten);
		if (current_meals >= table->meals_nbr)
		{
			satisfied_philosophers++;
			if (satisfied_philosophers == table->philos_nbr)
			{
				pthread_mutex_lock(&table->end_mutex);
				table->is_ended = 1;
				pthread_mutex_unlock(&table->end_mutex);
				return (true);
			}
		}
		i++;
	}
	return (false);
}

// Calcola tempo dall'ultimo pasto:
	// Se > time_to_die -> morte
bool	is_dead(t_philo *philo)
{
	unsigned long	current_time_relative;
	unsigned long	last_meal_time;
	long int		death_gap;

	current_time_relative = get_time() - philo->table->is_started;
	last_meal_time = ulong_safe_read(&philo->status, &philo->last_meal);
	death_gap = current_time_relative - last_meal_time;
	if (death_gap > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->is_ended = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		print_status(philo, DEAD);
		return (true);
	}
	return (false);
}

// Loop principale di monitoring (eseguito nel thread main)
// Controlla se tutti hanno mangiato abbastanza (se count_meals attivo)
// Controlla ogni filosofo per morte
// Se morte o completamento -> termina
int	monitoring(t_data *table)
{
	int	i;

	while (int_safe_read(&table->end_mutex, &table->is_ended) == 0)
	{
		i = 0;
		if (table->count_meals && has_eaten_enough(table))
			return (1);
		while (i < table->philos_nbr)
		{
			if (is_dead(&table->philo[i]))
				return (1);
			i++;
		}
		usleep(100);
	}
	return (0);
}
