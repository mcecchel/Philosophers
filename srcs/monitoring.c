/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:29:55 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 15:47:48 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// Thread di monitoraggio per morte e completamento azioni

bool	has_eaten_enough(t_data *table)
{
	// TODO: conta filosofi che hanno raggiunto nbr_meals:
	// - Se tutti hanno mangiato abbastanza -> fine simulazione
	// - Setta flag is_ended
	// - Usa accessi thread-safe per personal_meals
	int i;
	int satisfied_philosophers;
	int current_meals;
	
	i = 0;
	satisfied_philosophers = 0;
	
	// Conta filosofi che hanno raggiunto il numero richiesto di pasti
	while (i < table->philos_nbr)
	{
		// Usa accesso thread-safe per leggere meals_eaten
		current_meals = int_safe_read(&table->philo[i].status, 
									 &table->philo[i].meals_eaten);
		
		if (current_meals >= table->meals_nbr)
		{
			satisfied_philosophers++;
			
			// Se tutti hanno mangiato abbastanza -> fine simulazione
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

bool	is_dead(t_philo *philo)
{
// TODO: calcola tempo dall'ultimo pasto:
	// 1. Tempo corrente - start_time = tempo_simulazione
	// 2. tempo_simulazione - last_meal = tempo_senza_mangiare
	// 3. Se > time_to_die -> morte!
	// 4. Setta flag is_ended e stampa morte
	// 5. Usa accessi thread-safe per last_meal
	unsigned long	current_time_relative;
	unsigned long	last_meal_time;
	long int		death_gap;
	
	// Ottieni tempo corrente relativo all'inizio simulazione
	current_time_relative = get_time() - philo->table->is_started;
	// Leggi last_meal in modo thread-safe
	last_meal_time = ulong_safe_read(&philo->status, &philo->last_meal);
	// Calcola correttamente il death_gap (tempo trascorso dall'ultimo pasto)
	death_gap = current_time_relative - last_meal_time;
	// Verifica se è morto
	if (death_gap >= philo->table->time_to_die)
	{
		// Setta flag di fine simulazione
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->is_ended = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		// Stampa morte
		print_status(philo, DEAD);
		return (true);
	}
	return (false);
}

// Loop principale di monitoring (eseguito nel thread main)
int	monitoring(t_data *table)
{
	// TODO: loop fino a fine simulazione:
	// 1. Controlla se tutti hanno mangiato abbastanza (se count_meals attivo)
	// 2. Controlla ogni filosofo per morte
	// 3. Se morte o completamento -> termina
	// 4. Piccola pausa per evitare busy waiting
	int i;
	
	while (int_safe_read(&table->end_mutex, &table->is_ended) == 0)
	{
		i = 0;
		
		// 1. Controlla se tutti hanno mangiato abbastanza (se count_meals attivo)
		if (table->count_meals && has_eaten_enough(table))
			return (1);
		
		// 2. Controlla ogni filosofo per morte
		while (i < table->philos_nbr)
		{
			if (is_dead(&table->philo[i]))
				return (1);
			i++;
		}
		
		// 4. Piccola pausa per evitare busy waiting
		usleep(1000); // 1ms di pausa
	}
	return (0);
}
