/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:12:18 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/21 16:19:29 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "philosophers_colors.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

// Messaggi di stato
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define DEAD "died\n"

typedef struct s_philo t_philo;// X forward declaration

// Struttura principale
typedef struct	s_data
{
	int				philos_nbr;// Numero filosofi
	int				time_to_eat;// Tempo per mangiare
	int				time_to_sleep;// Tempo per dormire
	int				time_to_die;// Tempo massimo senza mangiare
	int				meals_nbr;// Numero pasti richiesti
	unsigned long	is_started;// Tempo di inizio simulazione
	int				is_ended;// Flag di fine simulazione
	bool			count_meals;// Flag se contare i pasti
	struct s_philo	*philo;// Array filosofi
	// === RISORSE CONDIVISE ===
	pthread_mutex_t	*fork_mutex;// Array mutex forchette
	pthread_mutex_t	print_mutex;// Mutex per stampe
	pthread_mutex_t	end_mutex;// Mutex per flag fine
}	t_data;

// Struttura singolo filosofo
struct s_philo
{
	int				id;// Numero del filosofo
	int				left_fork;// Indice forchetta sx
	int				right_fork;// Indice forchetta dx
	int				meals_eaten;// Contatore pasti consumati
	unsigned long	last_meal;// Timestamp ultimo pasto consumato
	pthread_t		philo;// Thread del filosofo
	pthread_mutex_t	status;// Mutex per dati personali
	t_data			*table;// Puntatore ai dati condivisi

};

#endif