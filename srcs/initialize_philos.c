/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:47:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/22 17:38:05 by mcecchel         ###   ########.fr       */
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
		// Inizializza la struttura del filosofo
		table->philo[i] = (t_philo){0};
		// Inizializza il mutex di stato del filosofo
		pthread_mutex_init(&table->philo[i].status, NULL);
		// Assegna il riferimento alla struttura dati principale
		table->philo[i].table = table;
		// Assegna l'ID del filosofo (da 1 a n)
		table->philo[i].id = i + 1;
		// Assegna le forchette (logica circolare)
		if (i == 0)// Primo filosofo (caso speciale)
		{
			table->philo[i].left_fork = i;// Forchetta sinistra
			table->philo[i].right_fork = table->philos_nbr - 1;// Forchetta destra (ultima)
		}
		else// Altri filosofi
		{
			table->philo[i].left_fork = i;// Forchetta sinistra
			table->philo[i].right_fork = i - 1;// Forchetta destra
		}
		i++;
	}
}

// Crea e avvia tutti i thread filosofi
int	philo_create(t_data *table)
{
	// Salva timestamp inizio simulazione
	// Crea thread per ogni filosofo con pthread_create()
	// Passa routine come funzione thread
	// Gestisci errori di creazione
	int	i;

	table->is_started = get_time();
	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_create(&table->philo[i].philo, NULL, (void *)routine, &table->philo[i]) != 0)//da fare funzione routine
		{
			printf("Errore: creazione thread filosofo %d fallita\n", table->philo[i].id);
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
			printf("Errore: join thread filosofo %d fallito\n", table->philo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_init(t_data *table)
{
    // TODO: sequenza inizializzazione:
    //   1. Alloca array filosofi
    //   2. Inizializza mutex con mutex_init()
    //   3. Configura ogni filosofo con philo_set()
    //   4. Crea threads con philo_create()
    //   5. Avvia monitoring
    //   6. Attendi completion con philo_join()
	table->philo = malloc(sizeof(t_philo) * table->philos_nbr);
	if (!table->philo)
	{
		printf("Errore: allocazione memoria filosofi fallita\n");
		return (1);
	}
	initialize_mutex(table);
	single_philo_init(table);
	philo_create(table);
	// Monitoraggio (da implementare)
	philo_join(table);
	return (0);
}