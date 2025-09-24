CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror #-g3 -pthread

SRC = main.c ft_atol.c init.c \
	  utils.c monitor.c set_get.c \
	  start_sim.c synchro.c \

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) philo.h
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) built successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c philo.h | $(OBJ_DIR)
	@echo "$(BLUE)🛠️  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(RED)🧹 Cleaning object files...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✅ Object files cleaned!$(RESET)"; \
	else \
		echo "$(YELLOW)ℹ️  No object files to clean$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)🧹 Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✅ $(NAME) removed!$(RESET)"; \
	else \
		echo "$(YELLOW)ℹ️  $(NAME) not found$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re