/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:12:18 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/05 19:53:00 by mcecchel         ###   ########.fr       */
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

/*
Cosa deve "sapere" ogni filosofo?
-Chi è (la sua identità)
-Quando ha mangiato l'ultima volta (per calcolare se sta morendo)
-Quanti pasti ha fatto (per la condizione di stop opzionale)
-Quali forchette può usare (le sue risorse)
-Come accedere alle regole del gioco (dati condivisi)

Cosa deve "fare" ogni filosofo?
-Eseguire il ciclo: pensa → mangia → dorme → ripeti
-Controllare se sta morendo
-Comunicare le sue azioni (stampe)
-Rispettare la sincronizzazione

argomenti da passare da riga di comando:
./philosophers [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: total_meals]
*/

typedef struct s_philosopher t_philosopher;// X forward declaration
typedef struct	s_data
{
	int				philos_nbr;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				total_meals;
	unsigned long	start_time;
	t_philosopher	*philosopher;
	// === RISORSE CONDIVISE ===
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}				t_data;

typedef struct s_philosopher
{
	// IDENTITÀ
	int				id;// Numero del filosofo

	// STATO VITALE
	unsigned long	last_meal;// Ultimo pasto in millisecondi
	int				meals_eaten;// Contatore pasti consumati

	// RISORSE
	int				left_fork;// ID della forchetta sx
	int				right_fork;// ID della forchetta dx

	// RISORSE CONDIVISE
	t_data	*data;// Puntatore ai dati condivisi

	// THREAD MANAGEMENT
	pthread_t		philosopher;// Thread handler
}				t_philosopher;

#endif