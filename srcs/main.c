/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:44:52 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/27 16:36:35 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Inizializza la struttura dati con valori di default
static void	init_table_defaults(t_data *table)
{
	table->philos_nbr = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_die = 0;
	table->meals_nbr = -1;
	table->is_started = 0;
	table->is_ended = 0;
	table->count_meals = false;
	table->philo = NULL;
	table->fork_mutex = NULL;
}

// Stampa messaggio di errore per argomenti invalidi
static void	print_usage(void)
{
	printf("❌ %sErrore: Argomenti invalidi%s\n", COLOR_ERROR, COLOR_RESET);
	printf("\n%sUso corretto:%s\n", COLOR_INFO, COLOR_RESET);
	printf("  %s./philosophers <number_of_philosophers> <time_to_die> "
		"<time_to_eat> <time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]%s\n\n",
		COLOR_SUCCESS, COLOR_RESET);
	printf("%sParametri:%s\n", COLOR_INFO, COLOR_RESET);
	printf("  • number_of_philosophers: 1-200\n");
	printf("  • time_to_die: tempo in ms (> 0)\n");
	printf("  • time_to_eat: tempo in ms (> 0)\n");
	printf("  • time_to_sleep: tempo in ms (> 0)\n");
	printf("  • [number_of_times_each_philosopher_must_eat]: "
		"opzionale, > 0\n\n");
	printf("%sEsempi:%s\n", COLOR_WARNING, COLOR_RESET);
	printf("  ./philosophers 4 800 200 200\n");
	printf("  ./philosophers 5 800 200 200 3\n");
}

int	main(int ac, char **av)
{
	t_data	table;

	init_table_defaults(&table);
	if (ac < 5 || ac > 6)
	{
		print_usage();
		return (1);
	}
	if (parse_arguments(ac, av, &table) != 0)
	{
		print_usage();
		return (1);
	}
	if (ac == 6)
		table.count_meals = true;
	printf("%s🚀 Avvio simulazione con %d filosofi...%s\n",
		COLOR_SUCCESS, table.philos_nbr, COLOR_RESET);
	if (philo_init(&table) != 0)
	{
		printf("%s❌ Errore durante l'inizializzazione%s\n",
			COLOR_ERROR, COLOR_RESET);
		return (1);
	}
	printf("%s✅ Simulazione completata%s\n", COLOR_SUCCESS, COLOR_RESET);
	return (0);
}
