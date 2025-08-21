/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:19:12 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/21 16:57:35 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Ottiene timestamp corrente in millisecondi
unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("gettimeofday error\n");
		return (1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Gestione sleep in millisecondi
void	ft_usleep(unsigned long ms)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
	{
		usleep(100); // Sleep breve per evitare busy waiting
	}
}