/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aesthetic.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:55:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/28 16:38:43 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_AESTHETIC_H
# define PHILO_AESTHETIC_H

# ifdef USE_COLOR
#  define COLOR_RESET    "\033[0m"
#  define COLOR_INFO     "\033[36m"   /* Cyan */
#  define COLOR_SUCCESS  "\033[32m"   /* Verde */
#  define COLOR_WARNING  "\033[33m"   /* Giallo */
#  define COLOR_ERROR    "\033[31m"   /* Rosso */
# else
#  define COLOR_RESET    ""
#  define COLOR_INFO     ""
#  define COLOR_SUCCESS  ""
#  define COLOR_WARNING  ""
#  define COLOR_ERROR    ""
# endif

# ifdef EMOJI_ON
#  define SLEEP "is sleeping 💤"
#  define THINK "is thinking 💭"
#  define FORK "has taken a fork 🍴"
#  define EAT "is eating 🍝"
#  define DEAD "died 🪦"
# else
#  define SLEEP "is sleeping"
#  define THINK "is thinking"
#  define FORK "has taken a fork"
#  define EAT "is eating"
#  define DEAD "died"
# endif

#endif
