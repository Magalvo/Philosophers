# Pretty colors
include include/pretty_colors_ANSI

# Project files

AUX = aux1.c cleaning.c ft_atoi.c init_aux.c carousel_aux.c
INIT = init_factory.c validation.c philo_born.c
CAROUSEL = carousel.c actions.c monitor.c

SRC_DIR = ./source/
AUX_DIR = $(SRC_DIR)aux/
INIT_DIR = $(SRC_DIR)init/
CAROUSEL_DIR = $(SRC_DIR)carousel/

SRC =	$(SRC_DIR)philosophers.c \
		$(addprefix $(AUX_DIR), $(AUX)) \
		$(addprefix $(INIT_DIR), $(INIT)) \
		$(addprefix $(CAROUSEL_DIR), $(CAROUSEL)) \


OBJ_DIR = ./object/
INC_DIR = -I ./include/



OBJECTS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Build settings
#
NAME = philo
CFLAGS = -pthread -Wall -Wextra -Werror -O3
debug: CFLAGS += -g3 -fPIE
MAKEFLAGS += --no-print-directory
.SILENT:  clean fclean debug $(OBJECTS) $(NAME)
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(YELLOW)** linking objects **	"$(NAME)"$(RST)\n"
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(GREEN_B)philosophers created $(RST)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(CYAN_I)** compiling **\t\t"$@"$(RST)\n"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

debug: fclean $(NAME)
	@printf "$(GREEN_B)** philosophers DEBUG created ** $(RST)\n"

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJ_DIR)
	@printf "$(RED)[All philosophers objects deleted]    $(RST)\n"

fclean: clean
	$(RM) $(NAME)
	@printf "$(RED)[philosophers deleted]    $(RST)\n"

re: fclean all
