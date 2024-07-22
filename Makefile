# Pretty colors
include include/pretty_colors_ANSI

# Project files
#
SRC =	philosophers.c
SRC_DIR = ./source/
OBJ_DIR = ./object/
INC_DIR = -I ./include/
OBJECTS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Build settings
#
NAME = philosophers
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
	mkdir -p $(OBJ_DIR)
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