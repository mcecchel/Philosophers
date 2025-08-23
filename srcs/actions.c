/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/23 18:19:57 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Acquisisce forchette e mangia
void	eating(t_philo *philo)
{
	// TODO: strategia acquisizione forchette:
	//   1. Lock forchetta destra
	//   2. Stampa "taken fork"
	//   3. Gestisci caso singolo filosofo (return)
	//   4. Lock forchetta sinistra  
	//   5. Stampa "taken fork" e "eating"
	//   6. Sleep per time_to_eat
	//   7. Aggiorna last_meal e personal_meals (thread-safe!)
	//   8. Rilascia entrambe le forchette
	pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
	print_status(philo, FORK);
	// Gestisco caso singolo filosofo (NB: non può prendere la seconda forchetta)
	if (philo->table->philos_nbr == 1)
	{
		pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
	print_status(philo, FORK);
	print_status(philo, EAT);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->status);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->status);
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

// Ciclo di azioni principale di ogni thread-filosofo
void *cycle(t_philo *philo)
{
	// TODO: implementa strategia anti-deadlock:
	//   - Filosofi pari aspettano 1ms prima di iniziare
	//   - Loop fino a fine simulazione o completamento pasti
	//   - Sequence: mangiare -> dormire -> pensare
	//   - Gestisci caso filosofo solitario
	int	current_meals;
	
	 if (philo->id % 2 == 0)
		ft_usleep(1);
	if (philo->table->philos_nbr == 1)
	{
		eating(philo);
		return (NULL);
	}
	while (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0)
	{
		eating(philo);
		// Controllo se ha completato i pasti richiesti
		pthread_mutex_lock(&philo->status);
		current_meals = philo->meals_eaten;
		pthread_mutex_unlock(&philo->status);

		if (current_meals >= philo->table->meals_nbr && philo->table->count_meals)
			break;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
