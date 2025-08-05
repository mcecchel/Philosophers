NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread -pedantic -I./include
SRCDIR = src
RM = rm -f

# Inserire USE_COLOR=1 durante la compilazione per attivare i colori
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

SRC_S = main.c \
	init.c \
	routine.c \
	mutex.c \
	utils.c \
	time.c \
	monitor.c \

SRC = $(addprefix $(SRCDIR)/,$(SRC_S))

all: $(NAME)

$(NAME): $(SRC)
	@echo "${BOLD}🚀 Creando ${RED}$(NAME)${NO_COLOR}"
	$(CC) $(CFLAGS) -o $@ $(SRC)
	${MAKE} temple

clean:

fclean: clean
	$(RM) $(NAME)
	@echo "${BOLD}Cleaning -> ${RED}$(NAME)${NO_COLOR}"

re: fclean all

.PHONY: all clean fclean re
.SILENT:

temple:
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
