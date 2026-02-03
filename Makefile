# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 16:11:17 by fgarnier          #+#    #+#              #
#    Updated: 2026/02/03 20:06:13 by ldesboui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- 🎨 COLORS & EMOJIS ---
BOLD      = \033[1m
BLACK     = \033[30;1m
RED       = \033[31;1m
GREEN     = \033[32;1m
YELLOW    = \033[33;1m
BLUE      = \033[34;1m
MAGENTA   = \033[35;1m
CYAN      = \033[36;1m
WHITE     = \033[37;1m
RESET     = \033[0m

# --- 🐢 VARS ---
NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g3

LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a

OBJ_DIR         = obj
SRC_DIR         = src

# --- 📂 SOURCES ---
SRCS_FILES      = minishell.c \
				  minishell_utils.c \
				  utils.c \
                  cmd_loop.c \
                  parser/parse.c \
                  parser/redirect.c \
                  parser/redirect_utils.c \
                  parser/args.c \
                  parser/args_utils.c \
                  parser/var_path.c \
                  parser/quote.c \
                  parser/expand.c \
                  parser/space.c \
				  parser/syntax.c \
                  path/path.c \
                  ctrl/new_prompt.c \
                  builtsin/ft_echo.c \
                  builtsin/ft_pwd.c \
                  builtsin/ft_env.c \
                  builtsin/ft_exit.c \
                  builtsin/ft_export.c \
                  builtsin/ft_unset.c \
				  free/ft_free_tab.c \
				  parser/expand_utils.c

SRCS            = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS            = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- 🚀 RULES ---

all: header $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)🔗 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "$(GREEN)✨ Minishell is ready! 🐚$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)Compiling: $(WHITE)%s$(RESET)\n" $(notdir $<)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@echo "$(MAGENTA)📦 Building Libft...$(RESET)"
	@make -sC $(LIBFT_DIR) bonus

# --- 🧹 CLEANING ---

clean:
	@echo "$(RED)🗑️  Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)🔥 Removing executables...$(RESET)"
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean

re: fclean all

# --- 🖼️  HEADER ---
header:
	@echo "$(CYAN)  __  __ _       _     _          _ _ $(RESET)"
	@echo "$(CYAN) |  \/  (_)     (_)   | |        | | |$(RESET)"
	@echo "$(CYAN) | \  / |_ _ __  _ ___| |__   ___| | |$(RESET)"
	@echo "$(CYAN) | |\/| | | '_ \| / __| '_ \ / _ \ | |$(RESET)"
	@echo "$(CYAN) | |  | | | | | | \__ \ | | |  __/ | |$(RESET)"
	@echo "$(CYAN) |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|$(RESET)"
	@echo "$(BOLD)      ... loading the turtle shell ...     $(RESET)"
	@echo ""

.PHONY: all clean fclean re header
