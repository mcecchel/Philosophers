/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:56:39 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/22 15:45:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Stampa i valori della struttura data per debug
void print_data(t_data *data)
{
	printf("📊 Dati parsati:\n");
	printf("   Numero filosofi: %d\n", data->philos_nbr);
	printf("   Time to die: %d ms\n", data->time_to_die);
	printf("   Time to eat: %d ms\n", data->time_to_eat);
	printf("   Time to sleep: %d ms\n", data->time_to_sleep);
	printf("   Numero pasti: %d ", data->meals_nbr);
	if (data->meals_nbr == -1)
		printf("(illimitato)");
	printf("\n\n");
}

// Test con parametri validi
void test_valid_cases(void)
{
	printf("🧪 === TEST CASI VALIDI ===\n\n");
	
	t_data data;
	
	// Test 1: Parametri base (senza meals)
	printf("Test 1: ./philo 4 800 200 200\n");
	char *av1[] = {"./philo", "4", "800", "200", "200", NULL};
	if (parse_arguments(5, av1, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
	
	// Test 2: Con numero di pasti
	printf("Test 2: ./philo 5 1000 300 300 7\n");
	char *av2[] = {"./philo", "5", "1000", "300", "300", "7", NULL};
	if (parse_arguments(6, av2, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
	
	// Test 3: Limite massimo filosofi
	printf("Test 3: ./philo 200 800 200 200\n");
	char *av3[] = {"./philo", "200", "800", "200", "200", NULL};
	if (parse_arguments(5, av3, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
	
	// Test 4: Con segno +
	printf("Test 4: ./philo +4 +800 +200 +200 +5\n");
	char *av4[] = {"./philo", "+4", "+800", "+200", "+200", "+5", NULL};
	if (parse_arguments(6, av4, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
}

// Test con parametri invalidi
void test_invalid_cases(void)
{
	printf("🚫 === TEST CASI INVALIDI ===\n\n");
	
	t_data data;
	
	// Test 1: Troppi filosofi
	printf("Test 1: ./philo 201 800 200 200 (troppi filosofi)\n");
	char *av1[] = {"./philo", "201", "800", "200", "200", NULL};
	if (parse_arguments(5, av1, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 2: Zero filosofi
	printf("Test 2: ./philo 0 800 200 200 (zero filosofi)\n");
	char *av2[] = {"./philo", "0", "800", "200", "200", NULL};
	if (parse_arguments(5, av2, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 3: Tempo negativo
	printf("Test 3: ./philo 4 -800 200 200 (tempo negativo)\n");
	char *av3[] = {"./philo", "4", "-800", "200", "200", NULL};
	if (parse_arguments(5, av3, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 4: Tempo zero
	printf("Test 4: ./philo 4 800 0 200 (tempo zero)\n");
	char *av4[] = {"./philo", "4", "800", "0", "200", NULL};
	if (parse_arguments(5, av4, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 5: Caratteri non numerici
	printf("Test 5: ./philo 4 800 20a 200 (carattere non numerico)\n");
	char *av5[] = {"./philo", "4", "800", "20a", "200", NULL};
	if (parse_arguments(5, av5, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 6: Pochi argomenti
	printf("Test 6: ./philo 4 800 200 (pochi argomenti)\n");
	char *av6[] = {"./philo", "4", "800", "200", NULL};
	if (parse_arguments(4, av6, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 7: Troppi argomenti
	printf("Test 7: ./philo 4 800 200 200 5 extra (troppi argomenti)\n");
	char *av7[] = {"./philo", "4", "800", "200", "200", "5", "extra", NULL};
	if (parse_arguments(7, av7, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
	
	// Test 8: Stringa vuota
	printf("Test 8: ./philo \"\" 800 200 200 (stringa vuota)\n");
	char *av8[] = {"./philo", "", "800", "200", "200", NULL};
	if (parse_arguments(5, av8, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
}

// Test edge cases
void test_edge_cases(void)
{
	printf("🎯 === TEST EDGE CASES ===\n\n");
	
	t_data data;
	
	// Test 1: Un solo filosofo
	printf("Test 1: ./philo 1 800 200 200 (un solo filosofo)\n");
	char *av1[] = {"./philo", "1", "800", "200", "200", NULL};
	if (parse_arguments(5, av1, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
	
	// Test 2: Tempi minimi
	printf("Test 2: ./philo 4 1 1 1 (tempi minimi)\n");
	char *av2[] = {"./philo", "4", "1", "1", "1", NULL};
	if (parse_arguments(5, av2, &data) == 0)
	{
		printf("✅ SUCCESSO\n");
		print_data(&data);
	}
	else
		printf("❌ FALLITO\n\n");
	
	// Test 3: Solo segno +
	printf("Test 3: ./philo + 800 200 200 (solo segno +)\n");
	char *av3[] = {"./philo", "+", "800", "200", "200", NULL};
	if (parse_arguments(5, av3, &data) != 0)
		printf("✅ CORRETTAMENTE RIFIUTATO\n\n");
	else
		printf("❌ DOVEVA ESSERE RIFIUTATO\n\n");
}

int main(void)
{
	printf("🧪 === TEST COMPLETO DI ARG_PARSING ===\n\n");
	
	test_valid_cases();
	test_invalid_cases();
	test_edge_cases();
	
	printf("🎉 Test completati!\n");	
	return (0);
}