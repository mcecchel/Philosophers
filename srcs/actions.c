/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:38 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/23 16:37:44 by mcecchel         ###   ########.fr       */
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
}

void	sleeping(t_philo *philo)
{
	// TODO: stampa "sleeping" e dormi per time_to_sleep
}

void	thinking(t_philo *philo)
{
	// TODO: stampa "thinking" (no sleep - ottimizzazione)
}

// Ciclo di azioni principale di ogni thread-filosofo
void *cycle(t_philo *philo)
{
	// TODO: implementa strategia anti-deadlock:
	//   - Filosofi pari aspettano 1ms prima di iniziare
	//   - Loop fino a fine simulazione o completamento pasti
	//   - Sequence: mangiare -> dormire -> pensare
	//   - Gestisci caso filosofo solitario
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (int_safe_read(&philo->table->end_mutex, &philo->table->is_ended) == 0)
	{
		// eat
	}
}
