/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:00:43 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/23 18:07:16 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>

// ========== UTILITIES PER I TEST ==========

// Mock del timer
unsigned long	get_current_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Setup base per creare una struttura di test
t_data	*create_test_environment(int num_philos, int die_time, int eat_time, int sleep_time, int meal_limit)
{
	t_data	*env;
	int		i;
	
	env = calloc(1, sizeof(t_data));
	
	// Configurazione base
	env->philos_nbr = num_philos;
	env->time_to_die = die_time;
	env->time_to_eat = eat_time;
	env->time_to_sleep = sleep_time;
	env->meals_nbr = meal_limit;
	env->is_ended = 0;
	env->count_meals = (meal_limit > 0) ? 1 : 0;
	env->is_started = get_current_time();
	
	// Alloca e inizializza array
	//    env->table = env; // Self-reference se necessario
	env->philo = calloc(num_philos, sizeof(t_philo));
	env->fork_mutex = calloc(num_philos, sizeof(pthread_mutex_t));
	
	// Inizializza mutex globali
	pthread_mutex_init(&env->print_mutex, NULL);
	pthread_mutex_init(&env->end_mutex, NULL);
	
	// Setup filosofi e forchette
	for (i = 0; i < num_philos; i++)
	{
		pthread_mutex_init(&env->fork_mutex[i], NULL);
		pthread_mutex_init(&env->philo[i].status, NULL);
		
		env->philo[i].id = i + 1;
		env->philo[i].table = env;
		env->philo[i].last_meal = get_current_time();
		env->philo[i].meals_eaten = 0;
		
		// Assegnazione forchette (circolare)
		env->philo[i].right_fork = i;
		env->philo[i].left_fork = (i + 1) % num_philos;
	}
	
	return (env);
}

void	cleanup_test_environment(t_data *env)
{
	int	i;
	
	if (!env)
		return;
		
	for (i = 0; i < env->philos_nbr; i++)
	{
		pthread_mutex_destroy(&env->fork_mutex[i]);
		pthread_mutex_destroy(&env->philo[i].status);
	}
	
	pthread_mutex_destroy(&env->print_mutex);
	pthread_mutex_destroy(&env->end_mutex);
	
	free(env->philo);
	free(env->fork_mutex);
	free(env);
}

// Helper per catturare output
int	capture_output_lines(void (*test_func)(t_philo*), t_philo *philo)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		line_count = 0;
	char	buffer[1024];
	
	pipe(pipe_fd);
	pid = fork();
	
	if (pid == 0)
	{
		// Child: redirect stdout e esegui test
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		
		test_func(philo);
		exit(0);
	}
	else
	{
		// Parent: leggi output
		close(pipe_fd[1]);
		while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0)
		{
			for (int i = 0; buffer[i]; i++)
				if (buffer[i] == '\n')
					line_count++;
		}
		close(pipe_fd[0]);
		wait(NULL);
	}
	
	return (line_count);
}

// ========== TEST SPECIFICI ==========

// Test 1: Verifica che print_status produca output
void	test_print_status_output(void)
{
	printf("🖨️  === TEST PRINT STATUS OUTPUT ===\n");
	
	t_data	*env = create_test_environment(3, 800, 200, 200, -1);
	t_philo	*test_philo = &env->philo[0];
	
	printf("Test: Stampa messaggi di stato diversi\n");
	
	// Test ogni tipo di messaggio
	printf("THINKING: ");
	print_status(test_philo, THINK);
	
	printf("FORK TAKEN: ");
	print_status(test_philo, FORK);
	
	printf("EATING: ");
	print_status(test_philo, EAT);
	
	printf("SLEEPING: ");
	print_status(test_philo, SLEEP);
	
	printf("DEAD: ");
	print_status(test_philo, DEAD);
	
	printf("✅ Test stampa completato (controlla manualmente l'output)\n\n");
	cleanup_test_environment(env);
}

// Test 2: Verifica timing delle azioni
void	test_action_timing(void)
{
	printf("⏱️  === TEST TIMING AZIONI ===\n");
	
	t_data	*env = create_test_environment(4, 800, 100, 150, -1);
	t_philo	*test_philo = &env->philo[0];
	
	// Test sleeping timing
	printf("Test sleeping (dovrebbe durare ~150ms):\n");
	unsigned long start = get_current_time();
	sleeping(test_philo);
	unsigned long sleep_duration = get_current_time() - start;
	printf("Durata sleep: %lu ms\n", sleep_duration);
	
	if (sleep_duration >= 140 && sleep_duration <= 200)
		printf("✅ Timing sleep corretto\n");
	else
		printf("❌ Timing sleep errato (atteso ~150ms)\n");
	
	// Test eating timing (più complesso per i mutex)
	printf("\nTest eating timing (dovrebbe durare ~100ms):\n");
	start = get_current_time();
	eating(test_philo);
	unsigned long eat_duration = get_current_time() - start;
	printf("Durata eating: %lu ms\n", eat_duration);
	
	if (eat_duration >= 90 && eat_duration <= 150)
		printf("✅ Timing eating corretto\n");
	else
		printf("❌ Timing eating errato (atteso ~100ms)\n");
	
	printf("\n");
	cleanup_test_environment(env);
}

// Test 3: Verifica acquisizione e rilascio forchette
void	test_fork_management(void)
{
	printf("🍴 === TEST GESTIONE FORCHETTE ===\n");
	
	t_data	*env = create_test_environment(3, 800, 50, 50, -1);
	
	// Test con filosofo normale
	printf("Test acquisizione forchette filosofo normale:\n");
	t_philo *philo1 = &env->philo[0];
	
	// Verifica che le forchette siano libere inizialmente
	int fork1_locked = pthread_mutex_trylock(&env->fork_mutex[philo1->right_fork]);
	int fork2_locked = pthread_mutex_trylock(&env->fork_mutex[philo1->left_fork]);
	
	if (fork1_locked == 0 && fork2_locked == 0)
	{
		printf("✅ Forchette inizialmente libere\n");
		pthread_mutex_unlock(&env->fork_mutex[philo1->right_fork]);
		pthread_mutex_unlock(&env->fork_mutex[philo1->left_fork]);
		
		// Test eating
		eating(philo1);
		
		// Verifica che le forchette siano di nuovo libere
		fork1_locked = pthread_mutex_trylock(&env->fork_mutex[philo1->right_fork]);
		fork2_locked = pthread_mutex_trylock(&env->fork_mutex[philo1->left_fork]);
		
		if (fork1_locked == 0 && fork2_locked == 0)
		{
			printf("✅ Forchette rilasciate correttamente dopo eating\n");
			pthread_mutex_unlock(&env->fork_mutex[philo1->right_fork]);
			pthread_mutex_unlock(&env->fork_mutex[philo1->left_fork]);
		}
		else
			printf("❌ Forchette non rilasciate correttamente\n");
	}
	else
		printf("❌ Problema inizializzazione forchette\n");
	
	printf("\n");
	cleanup_test_environment(env);
}

// Test 4: Caso speciale filosofo singolo
void	test_single_philosopher(void)
{
	printf("👤 === TEST FILOSOFO SINGOLO ===\n");
	
	t_data	*env = create_test_environment(1, 800, 100, 100, -1);
	t_philo	*solo_philo = &env->philo[0];
	
	printf("Test eating con un solo filosofo:\n");
	
	int initial_meals = solo_philo->meals_eaten;
	unsigned long start = get_current_time();
	
	eating(solo_philo);
	
	unsigned long duration = get_current_time() - start;
	int final_meals = solo_philo->meals_eaten;
	
	printf("Durata: %lu ms\n", duration);
	printf("Pasti iniziali: %d, finali: %d\n", initial_meals, final_meals);
	
	// Il filosofo singolo non dovrebbe riuscire a mangiare (non può prendere 2 forchette)
	if (duration < 50 && final_meals == initial_meals)
		printf("✅ Filosofo singolo gestito correttamente (non mangia)\n");
	else
		printf("❌ Gestione filosofo singolo errata\n");
	
	// Test che il ciclo si interrompa
	printf("\nTest ciclo filosofo singolo (dovrebbe terminare rapidamente):\n");
	start = get_current_time();
	cycle(solo_philo);
	duration = get_current_time() - start;
	
	if (duration < 100)
		printf("✅ Ciclo filosofo singolo termina correttamente\n");
	else
		printf("❌ Ciclo filosofo singolo non termina rapidamente\n");
	
	printf("\n");
	cleanup_test_environment(env);
}

// Test 5: Conteggio pasti
void	test_meal_counting(void)
{
	printf("🍽️  === TEST CONTEGGIO PASTI ===\n");
	
	t_data	*env = create_test_environment(2, 800, 30, 30, 3);
	t_philo	*philo = &env->philo[0];
	
	printf("Test conteggio pasti (limite: 3):\n");
	printf("Pasti iniziali: %d\n", philo->meals_eaten);
	
	// Simula alcuni cicli di eating
	for (int i = 0; i < 5; i++)
	{
		eating(philo);
		printf("Dopo eating %d: %d pasti\n", i + 1, philo->meals_eaten);
		
		if (philo->meals_eaten >= env->meals_nbr && env->count_meals)
		{
			printf("Limite pasti raggiunto, dovrebbe fermarsi\n");
			break;
		}
	}
	
	if (philo->meals_eaten >= 3)
		printf("✅ Conteggio pasti funziona\n");
	else
		printf("❌ Conteggio pasti non corretto\n");
	
	printf("\n");
	cleanup_test_environment(env);
}

// Test 6: Thread safety (simulazione concorrenza)
void	test_thread_safety(void)
{
	printf("🔒 === TEST THREAD SAFETY ===\n");
	
	t_data	*env = create_test_environment(4, 1000, 50, 50, -1);
	pthread_t	threads[4];
	
	printf("Test con 4 filosofi concorrenti per 300ms:\n");
	
	// Avvia threads
	for (int i = 0; i < 4; i++)
		pthread_create(&threads[i], NULL, (void*(*)(void*))cycle, &env->philo[i]);
	
	// Lascia girare
	usleep(300000); // 300ms
	
	// Termina simulazione
	pthread_mutex_lock(&env->end_mutex);
	env->is_ended = 1;
	pthread_mutex_unlock(&env->end_mutex);
	
	// Aspetta terminazione
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);
	
	printf("Risultati dopo 300ms:\n");
	int total_meals = 0;
	for (int i = 0; i < 4; i++)
	{
		printf("Filosofo %d: %d pasti\n", i + 1, env->philo[i].meals_eaten);
		total_meals += env->philo[i].meals_eaten;
	}
	
	if (total_meals > 0)
		printf("✅ Almeno qualche filosofo è riuscito a mangiare\n");
	else
		printf("❌ Nessun filosofo è riuscito a mangiare (possibile deadlock)\n");
	
	printf("\n");
	cleanup_test_environment(env);
}

// Test 7: Gestione terminazione
void	test_termination_handling(void)
{
	printf("🛑 === TEST GESTIONE TERMINAZIONE ===\n");
	
	t_data	*env = create_test_environment(2, 800, 50, 50, -1);
	t_philo	*philo = &env->philo[0];
	
	printf("Test stampa durante simulazione attiva:\n");
	print_status(philo, THINK);
	
	printf("Test stampa dopo terminazione simulazione:\n");
	pthread_mutex_lock(&env->end_mutex);
	env->is_ended = 1;
	pthread_mutex_unlock(&env->end_mutex);
	
	// Dovrebbe non stampare (eccetto DEAD)
	printf("(Non dovrebbe stampare nulla): ");
	print_status(philo, THINK);
	
	printf("\nTest stampa DEAD dopo terminazione (dovrebbe stampare): ");
	print_status(philo, DEAD);
	
	printf("✅ Test terminazione completato\n\n");
	cleanup_test_environment(env);
}

// ========== MAIN TEST RUNNER ==========

int	main(void)
{
	printf("🧪 === SUITE COMPLETA DI TEST PER ACTIONS.C ===\n\n");
	
	test_print_status_output();
	test_action_timing();
	test_fork_management();
	test_single_philosopher();
	test_meal_counting();
	test_thread_safety();
	test_termination_handling();
	
	printf("🎉 === TUTTI I TEST COMPLETATI ===\n");
	printf("💡 Controlla manualmente l'output per verificare che tutto funzioni come atteso.\n");
	printf("🔍 Presta particolare attenzione a:\n");
	printf("   - Timing delle azioni\n");
	printf("   - Acquisizione/rilascio forchette\n");
	printf("   - Gestione del caso filosofo singolo\n");
	printf("   - Thread safety con più filosofi\n");
	
	return (0);
}