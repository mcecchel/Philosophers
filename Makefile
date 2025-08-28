NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread -pedantic -I./includes
RM = rm -f

ifeq ($(USE_COLOR),1)
	CFLAGS += -DUSE_COLOR
	RED         := ${shell tput setaf 1}
	BLUE        := ${shell tput setaf 4}
	NO_COLOR    := ${shell tput sgr0}
	BOLD        := ${shell tput bold}
else
	RED         :=
	BLUE        :=
	NO_COLOR    :=
	BOLD        :=
endif

ifeq ($(EMOJI_ON),1)
	CFLAGS += -DEMOJI_ON
endif

SRC =	srcs/main.c \
		srcs/utils.c \
		srcs/time.c \
		srcs/mutex.c \
		srcs/safe_rw.c \
		srcs/parsing.c \
		srcs/initialize_philos.c \
		srcs/actions.c \
		srcs/cycle.c \
		srcs/monitoring.c

all: $(NAME)

$(NAME): $(SRC)
	@echo "${BOLD}🚀...Creando ${RED}$(NAME)${NO_COLOR}"
	$(CC) $(CFLAGS) -o $@ $(SRC)
	${MAKE} temple

clean:

fclean: clean
	$(RM) $(NAME)
	@echo "${BOLD}🧹...Cleaning ${RED}$(NAME)${NO_COLOR}"

re: fclean all

.PHONY: all clean fclean re
.SILENT:

temple:
	@echo '                                    '
	@echo '⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⢤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⡤⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣤⣤⠀⠀⠀⠀⢠⣤⠀⠀⠀⠀⣤⡄⠀⠀⠀⠀⣤⣤⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⠀⠛⠛⠀⠀⠀⠀⠘⠛⠀⠀⠀⠀⠛⠃⠀⠀⠀⠀⠛⠛⠀⠀⠀⠀⠀'
	@echo '⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀'
	@echo '⠀⠀⢰⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⡆⠀⠀'
	@echo '⠀⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀'
	@echo '                                    '