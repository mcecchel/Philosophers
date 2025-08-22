/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:57:03 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/22 14:34:10 by mcecchel         ###   ########.fr       */
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
	if (str[i] == '+')
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
	int	i;

	i = 0;
	// Controlla stringa vuota
	if (str[0] == '\0')
		return (false);
	// Gestisci il caso del segno '+' iniziale
	if (str[0] == '+')
		i++;
	// Rifiuta numeri negativi
	if (str[0] == '-')
		return (false);
	// Controlla che ci sia almeno una cifra dopo il '+'
	if (str[i] == '\0')
		return (false);
	// Controlla che contenga solo cifre
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
