/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:39:51 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/21 16:54:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	partial_mutex_cleanup(t_data *table, int fork_index)
{
	int	i;

	i = 0;
	while (i < fork_index)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		i++;
	}
	free(table->fork_mutex);
	table->fork_mutex = NULL;
}

void	all_fork_mutex_cleanup(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		i++;
	}
	free(table->fork_mutex);
	table->fork_mutex = NULL;
}