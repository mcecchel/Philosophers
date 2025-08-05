/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_colors.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:55:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/05 19:55:15 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_COLORS_H
# define PHILOSOPHERS_COLORS_H

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

#endif