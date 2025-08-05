/* ************************************************************************** */
/*                                                                            */
/*                         Gestione colori flessibile                         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_COLORS_H
# define PHILOSOPHERS_COLORS_H

/* -------------------------------------------------------------------------- */
/* Come si usa: inserire o rimuovere flag -DUSE_COLOR in Makefile             */
/* -------------------------------------------------------------------------- */

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