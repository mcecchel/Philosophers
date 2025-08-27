/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:12:18 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/27 16:55:14 by mcecchel         ###   ########.fr       */
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
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 💭"
# define FORK "has taken a fork 🍴"
# define EAT "is eating 🍝"
# define DEAD "died 🪦"

typedef struct s_philo	t_philo;

// Struttura principale
typedef struct s_data
{
	int				philos_nbr;				// Numero filosofi
	int				time_to_eat;			// Tempo per mangiare
	int				time_to_sleep;			// Tempo per dormire
	int				time_to_die;			// Tempo massimo senza mangiare
	int				meals_nbr;				// Numero pasti richiesti
	unsigned long	is_started;				// Tempo di inizio simulazione
	int				is_ended;				// Flag di fine simulazione
	bool			count_meals;			// Flag se contare i pasti
	struct s_philo	*philo;					// Array filosofi
	// === RISORSE CONDIVISE ===
	pthread_mutex_t	*fork_mutex;			// Array mutex forchette
	pthread_mutex_t	print_mutex;			// Mutex per stampe
	pthread_mutex_t	end_mutex;				// Mutex per flag fine
}	t_data;

// Struttura singolo filosofo
struct s_philo
{
	int				id;						// Numero del filosofo
	int				left_fork;				// Indice forchetta sx
	int				right_fork;				// Indice forchetta dx
	int				meals_eaten;			// Contatore pasti consumati
	unsigned long	last_meal;				// Timestamp ultimo pasto consumato
	pthread_t		philo;					// Thread del filosofo
	pthread_mutex_t	status;					// Mutex per dati personali
	t_data			*table;					// Puntatore ai dati condivisi
};

// ═════════════════════════════════════════════════════════════════════════════
// ═══                            UTILITY FUNCTIONS                           ══
// ═════════════════════════════════════════════════════════════════════════════

// === UTILS (utils.c) ===
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(const char *str);
bool				syntax_checker(char *str);

// === TIME (time.c) ===
unsigned long		get_time(void);
void				ft_usleep(unsigned long ms);

// ═════════════════════════════════════════════════════════════════════════════
// ═══                       THREAD SAFETY & SYNCHRONIZATION                 ═══
// ═════════════════════════════════════════════════════════════════════════════

// === MUTEX MANAGEMENT (mutex.c) ===
int					initialize_mutex(t_data *table);
void				destroy_mutex(t_data *table);

// === THREAD-SAFE READ/WRITE (safe_rw.c) ===
int					int_safe_read(pthread_mutex_t *mutex, int *value);
unsigned long		ulong_safe_read(pthread_mutex_t *mutex,
						unsigned long *value);
void				int_safe_write(pthread_mutex_t *mutex, int *value,
						int copy);
void				ulong_safe_write(pthread_mutex_t *mutex,
						unsigned long *value, unsigned long copy);

// ═════════════════════════════════════════════════════════════════════════════
// ═══                         CORE SIMULATION LOGIC                         ═══
// ═════════════════════════════════════════════════════════════════════════════

// === ARGUMENT PARSING (parsing.c) ===
int					validate_philosophers(int n, t_data *data);
int					validate_times(int i, int n, t_data *data);
int					validate_and_assign(int i, int n, t_data *data);
int					parse_arguments(int ac, char **av, t_data *data);

// === INITIALIZATION (initialize_philos.c) ===
void				single_philo_init(t_data *table);
int					philo_create(t_data *table);
int					philo_join(t_data *table);
int					philo_init(t_data *table);

// === PHILOSOPHER ACTIONS (actions.c) ===
void				print_status(t_philo *philo, char *message);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);

// === PHILOSOPHER LIFECYCLE (cycle.c) ===
void				*single_philo_cycle(void *arg);
void				*cycle(void *arg);

// === SIMULATION MONITORING (monitoring.c) ===
bool				has_eaten_enough(t_data *table);
bool				is_dead(t_philo *philo);
int					monitoring(t_data *table);

#endif
