/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_rw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:13:09 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/26 16:14:58 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Legge variabili condivise in modo sicuro
// Previene race conditions
// Garantisce coerenza dei dati tra thread
// Sincronizza l'accesso alle risorse
int	int_safe_read(pthread_mutex_t *mutex, int *value)
{
	int	copy;

	pthread_mutex_lock(mutex);
	copy = *value;
	pthread_mutex_unlock(mutex);
	return (copy);
}

// Come sopra, ma per unsigned long
unsigned long	ulong_safe_read(pthread_mutex_t *mutex, unsigned long *value)
{
	unsigned long	copy;

	pthread_mutex_lock(mutex);
	copy = *value;
	pthread_mutex_unlock(mutex);
	return (copy);
}

void	int_safe_write(pthread_mutex_t *mutex, int *value, int copy)
{
	pthread_mutex_lock(mutex);
	*value = copy;
	pthread_mutex_unlock(mutex);
}

void	ulong_safe_write(pthread_mutex_t *mutex, unsigned long *value,
			unsigned long copy)
{
	pthread_mutex_lock(mutex);
	*value = copy;
	pthread_mutex_unlock(mutex);
}
