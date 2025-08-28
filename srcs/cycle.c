/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:39:23 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/28 14:30:12 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*single_philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->fork_mutex[0]);
	print_status(philo, FORK);
	while (int_safe_read(&philo->table->end_mutex,
			&philo->table->is_ended) == 0)
	{
		ft_usleep(100);
	}
	pthread_mutex_unlock(&philo->table->fork_mutex[0]);
	return (NULL);
}

// Loop fino a fine simulazione o completamento pasti
void	*cycle(void *arg)
{
	t_philo	*philo;
	int		current_meals;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->table->philos_nbr == 1)
		return (single_philo_cycle(arg));
	while (int_safe_read(&philo->table->end_mutex,
			&philo->table->is_ended) == 0)
	{
		eating(philo);
		if (philo->table->count_meals)
		{
			current_meals = int_safe_read(&philo->status, &philo->meals_eaten);
			if (current_meals >= philo->table->meals_nbr)
				break ;
		}
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}
