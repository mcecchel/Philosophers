/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:57:03 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/21 16:19:00 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

bool	syntax_checker(char *str)
{
	// TODO: implementa validazione
	// Controlla che contenga solo cifre
	// Gestisci il caso del segno '+' iniziale
	// Rifiuta numeri negativi
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (i != 0 || str[i] == '-')
				return (false);
			else
				i++;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		else
			i++;
	}
	return (true);
}