/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 16:36:37 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Acquisisce forchette e mangia
// Filosofi pari: prima destra, poi sinistra
// Filosofi dispari: prima sinistra, poi destra
// -> rompe la dipendenza circolare
void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		print_status(philo, FORK);
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
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		print_status(philo, FORK);
	}
	print_status(philo, EAT);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->status);
	philo->last_meal = get_time() - philo->table->is_started;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->status);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left_fork]);
}

// Stampa messaggi di stato in modo thread-safe
// TODO: stampa thread-safe:
//   - Lock mutex print
//   - Controlla se simulazione è finita (tranne per "died")
//   - Stampa: timestamp_relativo ID_filosofo azione
//   - Usa colori per leggibilità
//   - Unlock mutex print
void	print_status(t_philo *philo, char *message)
{
	unsigned long	timestamp;

	timestamp = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	if (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0
		|| ft_strcmp(message, DEAD) == 0)
	{
		printf("%s", COLOR_INFO);
		printf("%lu ", timestamp - philo->table->is_started);
		printf("%s", COLOR_SUCCESS);
		printf("%d ", philo->id);
		printf("%s", COLOR_RESET);
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

// TODO: implementa strategia anti-deadlock:
//   - Filosofi pari aspettano 1ms prima di iniziare
//   - Loop fino a fine simulazione o completamento pasti
//   - Sequence: mangiare -> dormire -> pensare
//   - Gestisci caso filosofo solitario
void	*cycle(void *arg)
{
	t_philo	*philo;
	int		current_meals;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	if (philo->table->philos_nbr == 1)
		return (eating(philo), NULL);
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
		ft_usleep(1);
	}
	return (NULL);
}
