/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:01:46 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 16:12:08 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_philosophers(int n, t_data *data)
{
	if (n > 200 || n == 0)
		return (1);
	data->philos_nbr = n;
	return (0);
}

int	validate_times(int i, int n, t_data *data)
{
	if (n <= 0)
		return (1);
	if (i == 2)
		data->time_to_die = n;
	else if (i == 3)
		data->time_to_eat = n;
	else if (i == 4)
		data->time_to_sleep = n;
	else if (i == 5)
		data->meals_nbr = n;
	return (0);
}

int	validate_and_assign(int i, int n, t_data *data)
{
	if (i == 1)
		return (validate_philosophers(n, data));
	else
		return (validate_times(i, n, data));
}

// Parsing e validazione argomenti di input
int	parse_arguments(int ac, char **av, t_data *data)
{
	int	i;
	int	n;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!syntax_checker(av[i]))
		{
			printf("Errore: argomento '%s' non valido\n", av[i]);
			return (1);
		}
		n = ft_atoi(av[i]);
		if (validate_and_assign(i, n, data))
			return (1);
		i++;
	}
	if (ac == 5)
		data->meals_nbr = -1;
	return (0);
}
