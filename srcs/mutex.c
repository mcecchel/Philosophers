/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:29:15 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/21 16:55:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Inizializza mutex
int init_all_mutex(t_data *table)
{
	// TODO: alloca array mutex forchette
	// Inizializza mutex per ogni forchetta
	// Inizializza mutex print e end
	// Gestisci errori di allocazione
	int	i;

	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->philos_nbr);
	if (!table->fork_mutex)
	{
		printf("Error: Failed to allocate memory for fork mutexes\n");
		return (1);
	}
	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL) != 0)
		{
			printf("Error: Failed to initialize fork mutex %d\n", i);
			partial_mutex_cleanup(table, i);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		printf("Error: Failed to initialize print mutex\n");
		all_fork_mutex_cleanup(table);
		return (1);
	}
	if (pthread_mutex_init(&table->end_mutex, NULL) != 0)
	{
		printf("Error: Failed to initialize end mutex\n");
		pthread_mutex_destroy(&table->print_mutex);
		all_fork_mutex_cleanup(table);
		return (1);
	}
	return (0);
}
