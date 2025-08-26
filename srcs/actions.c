/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 15:49:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Acquisisce forchette e mangia
void	eating(t_philo *philo)
{
	// Filosofi pari: prima destra, poi sinistra
	// Filosofi dispari: prima sinistra, poi destra
	// -> rompe la dipendenza circolare
	if (philo->id % 2 == 0)
	{
		// Filosofi pari: prima right_fork, poi left_fork
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		print_status(philo, FORK);
		// Gestisco caso singolo filosofo
		if (philo->table->philos_nbr == 1)
		{
			pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
			return ;
		}
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		print_status(philo, FORK);
	}
	else
	{
		// Filosofi dispari: prima left_fork, poi right_fork  
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		print_status(philo, FORK);
	}
	// Mangia
	print_status(philo, EAT);
	ft_usleep(philo->table->time_to_eat);
	//Aggiorna last_meal con timestamp ATTUALE
	pthread_mutex_lock(&philo->status);
	philo->last_meal = get_time() - philo->table->is_started; // Timestamp relativo
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->status);
	// Rilascia forchette (ordine non critico per il rilascio)
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left_fork]);
}

// Stampa messaggi di stato in modo thread-safe
void	print_status(t_philo *philo, char *message)
{
	// TODO: stampa thread-safe:
	//   - Lock mutex print
	//   - Controlla se simulazione è finita (tranne per "died")
	//   - Stampa: timestamp_relativo ID_filosofo azione
	//   - Usa colori per leggibilità
	//   - Unlock mutex print
	unsigned long	timestamp;
	
	timestamp = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	// Stampa solo se simulazione non è finita (eccetto per messaggi di morte)
	if (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0 || ft_strcmp(message, DEAD) == 0)
	{
		// Stampa con colori: timestamp relativo, ID filosofo, azione
		printf("%s", COLOR_INFO);// Cyan per timestamp
		printf("%lu ", timestamp - philo->table->is_started);
		printf("%s", COLOR_SUCCESS);// Verde per ID
		printf("%d ", philo->id);
		printf("%s", COLOR_RESET);// Reset colori
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

void *cycle(void *arg)
{
	// TODO: implementa strategia anti-deadlock:
	//   - Filosofi pari aspettano 1ms prima di iniziare
	//   - Loop fino a fine simulazione o completamento pasti
	//   - Sequence: mangiare -> dormire -> pensare
	//   - Gestisci caso filosofo solitario
	t_philo	*philo;
	int		current_meals;
	
	philo = (t_philo *)arg;
	// Evita che tutti i filosofi inizino contemporaneamente
	if (philo->id % 2 == 0)
		ft_usleep(50); // Filosofi pari aspettano 50ms
	// Caso filosofo singolo
	if (philo->table->philos_nbr == 1)
	{
		eating(philo); // Tenta di mangiare (fallirà)
		return (NULL);
	}
	// Ciclo principale
	while (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0)
	{
		eating(philo);
		// Controlla se ha raggiunto il limite pasti (se attivo)
		if (philo->table->count_meals)
		{
			current_meals = int_safe_read(&philo->status, &philo->meals_eaten);
			if (current_meals >= philo->table->meals_nbr)
				break;
		}
		sleeping(philo);
		thinking(philo);
		ft_usleep(1);
	}
	return (NULL);
}
