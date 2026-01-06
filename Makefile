# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 16:11:17 by fgarnier          #+#    #+#              #
#    Updated: 2026/01/06 19:19:47 by ldesboui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g

LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a

GNL_DIR   		= gnl
GNL       		= $(GNL_DIR)/get_next_line.a

OBJ_DIR         = obj
SRC_DIR         = src
SRCS            = minishell.c
OBJS            = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME):$(GNL) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) -L$(LIBFT_DIR) $(FT_PRINTF) $(GNL) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(GNL):
	make -C $(GNL_DIR)	

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(GNL_DIR) clean
	

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
