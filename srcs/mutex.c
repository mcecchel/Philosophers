/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:36:09 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 16:13:53 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// TODO: allocare array mutex forchette
// Inizializzare mutex per ogni forchetta
// Inizializzare mutex print e end
// Gestire errori di allocazione
int	initialize_mutex(t_data *table)
{
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

// TODO: distruggere tutti i mutex
// Liberare memoria allocata
// NB: ordine inverso rispetto all'inizializzazione
void	destroy_mutex(t_data *table)
{
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
