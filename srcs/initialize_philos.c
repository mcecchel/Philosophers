/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:47:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/28 16:13:08 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Configura dati di ogni singolo filosofo
void	single_philo_init(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		table->philo[i] = (t_philo){0};
		table->philo[i].last_meal = 0;
		table->philo[i].meals_eaten = 0;
		pthread_mutex_init(&table->philo[i].status, NULL);
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philos_nbr;
		i++;
	}
}

int	philo_create(t_data *table)
{
	int				i;
	unsigned long	start_time;

	start_time = get_time();
	table->is_started = start_time;
	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_lock(&table->philo[i].status);
		table->philo[i].last_meal = start_time;
		pthread_mutex_unlock(&table->philo[i].status);
		if (pthread_create(&table->philo[i].philo, NULL, &cycle,
				&table->philo[i]) != 0)
		{
			printf("Errore: creazione thread filosofo %d fallita\n",
				table->philo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

// Attende completamento di tutti i thread
int	philo_join(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_join(table->philo[i].philo, NULL) != 0)
		{
			printf("Errore: join thread filosofo %d fallito\n",
				table->philo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

// Sequenza di inizializzazione
int	philo_init(t_data *table)
{
	table->philo = malloc(sizeof(t_philo) * table->philos_nbr);
	if (!table->philo)
	{
		printf("Errore: allocazione memoria filosofi fallita\n");
		return (1);
	}
	if (initialize_mutex(table) != 0)
	{
		free(table->philo);
		return (1);
	}
	single_philo_init(table);
	if (philo_create(table) != 0)
	{
		destroy_mutex(table);
		return (1);
	}
	monitoring(table);
	if (philo_join(table) != 0)
	{
		destroy_mutex(table);
		return (1);
	}
	destroy_mutex(table);
	return (0);
}
