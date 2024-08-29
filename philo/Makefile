NAME := philo

SRCS := main.c init.c utils.c print_utils.c clean_up.c simulation.c \
thread_activities.c get.c set.c
  
CFLAGS := -Wall -Wextra -Werror

CC := cc

OBS := $(SRCS:.c=.o)

COLOR_RESET = \033[0m
COLOR_GREEN = \033[1;92m
COLOR_BLUE = \033[1;96m 

MAKEFLAGS += --no-print-directory

define print_colored
	@echo "$(COLOR_GREEN)$(1)$(COLOR_BLUE)$(2)$(COLOR_RESET)$(3)"
endef

.SILENT:

all: $(NAME)

$(NAME): $(OBS)
	$(CC) $(OBS) -o $@
	$(call print_colored, "[SUCCESS]", "./$(NAME)", "Ready")


clean:
	rm -rf $(OBS)

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re