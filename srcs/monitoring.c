/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:29:55 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/25 14:08:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// Thread di monitoraggio per morte e completamento azioni

bool has_eaten_enough(t_data *table)
{
	// TODO: conta filosofi che hanno raggiunto nbr_meals:
	// - Se tutti hanno mangiato abbastanza -> fine simulazione
	// - Setta flag is_ended
	// - Usa accessi thread-safe per personal_meals
	int	i;
	int	current_meals;
	int	philo_has_eaten;

	i = 0;
	philo_has_eaten = 0;
	// Conta filosofi che hanno raggiunto il numero richiesto di pasti
	while (i < table->philos_nbr)
	{
		current_meals = int_safe_read(&table->philo[i].status, &table->philo[i].meals_eaten);
		if (current_meals >= table->meals_nbr)
		{
			philo_has_eaten++;
			// Se tutti hanno mangiato abbastanza -> fine simulazione
			if (philo_has_eaten == table->philos_nbr)
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

bool is_dead(t_philo *philo)
{
// TODO: calcola tempo dall'ultimo pasto:
	// 1. Tempo corrente - start_time = tempo_simulazione
	// 2. tempo_simulazione - last_meal = tempo_senza_mangiare
	// 3. Se > time_to_die -> morte!
	// 4. Setta flag is_ended e stampa morte
	// 5. Usa accessi thread-safe per last_meal
	long int		death_gap;// differenza tra tempo corrente e ultimo pasto
	long int		current_time;
	unsigned long	last_meal_time;

	current_time = get_time() - philo->table->is_started;
	last_meal_time = ulong_safe_read(&philo->status, &philo->last_meal);
	death_gap = current_time - (last_meal_time - philo->table->is_started);
	// Se il tempo senza mangiare supera il limite -> morte!
	if (death_gap > philo->table->time_to_die)
	{
		// Setta flag is_ended in modo thread-safe
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->is_ended = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		// Stampa avviso di morte
		print_status(philo, DEAD);
		return (true);
	}
	return (false);
}

int	monitoring(t_data *table)
{
// TODO: loop fino a fine simulazione:
	// 1. Controlla se tutti hanno mangiato abbastanza (se count_meals attivo)
	// 2. Controlla ogni filosofo per morte
	// 3. Se morte o completamento -> termina
	// 4. Piccola pausa per evitare busy waiting
	int	i;

	while (int_safe_read(&table->end_mutex, &table->is_ended) == 0)
	{
		// Se si conta il numero di pasti, verifica se tutti hanno mangiato abbastanza
		if (table->count_meals && has_eaten_enough(table))
			return (1);
		// Controlla ogni filosofo per morte
		i = 0;
		while (i < table->philos_nbr)
		{
			if (is_dead(&table->philo[i]))
				return (1);
			i++;
		}
		usleep(1000);
	}
	return (0);
}
