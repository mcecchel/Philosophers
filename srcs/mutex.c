/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:36:09 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/22 15:42:29 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_mutex(t_data *table)
{
	// TODO: allocare array mutex forchette
	// Inizializzare mutex per ogni forchetta
	// Inizializzare mutex print e end
	// Gestire errori di allocazione
	int	i;

	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->philos_nbr);
	if (!table->fork_mutex)
		return (1);
	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->end_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	destroy_mutex(t_data *table)
{
	// TODO: distruggere tutti i mutex
	// Liberare memoria allocata
	// NB: ordine inverso rispetto all'inizializzazione
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->end_mutex);
	free(table->philo);
	free(table->fork_mutex);
}

// Legge variabili condivise in modo sicuro
// Previene race conditions
// Garantisce coerenza dei dati tra thread
// Sincronizza l'accesso alle risorse
int int_safe_read(pthread_mutex_t *mutex, int *value)
{
	int	copy;
	
	pthread_mutex_lock(mutex);
	copy = *value;
	pthread_mutex_unlock(mutex);
	return (copy);
}

// Come sopra, ma per unsigned long
unsigned long	ulong_safe_read(pthread_mutex_t *mutex, unsigned long *value)
{
	unsigned long	copy;
	
	pthread_mutex_lock(mutex);
	copy = *value;
	pthread_mutex_unlock(mutex);
	return (copy);
}