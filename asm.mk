# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/08 14:08:10 by mmanhack          #+#    #+#              #
#    Updated: 2020/07/08 14:08:15 by mmanhack         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = asm

CFLAGS = -Wall -Werror -Wextra -g

HEAD_INC = ./includes/asm
HEADERS = $(HEAD_INC)/asm.h $(HEAD_INC)/op.h

SRC_DIR = ./src/asm
SRC_LIST = asm.c op.c \
	lexer.c lexer_parse.c \
	output.c output_code.c output_utils.c \
	parser.c parser_args.c parser_tokens.c \
	utils.c utils_2.c utils_3.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_LIST))

OBJ_DIR = ./obj
OBJ_DIR_ASM = ./obj/asm
OBJ_LIST = $(SRC_LIST:%.c=%.o)
OBJ = $(addprefix $(OBJ_DIR_ASM)/, $(OBJ_LIST))

LIB_DIR = ./libft
LIB_HEAD = $(LIB_DIR)/includes
LIBFT = $(LIB_DIR)/libft.a

.PHONY: all clean fclean re FORCE

all: $(OBJ_DIR) $(OBJ_DIR_ASM) $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I$(HEAD_INC) -I$(LIB_HEAD) -L$(LIB_DIR) -lft

$(OBJ): $(OBJ_DIR_ASM)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(HEAD_INC) -I$(LIB_HEAD)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_ASM): $(OBJ_DIR)
	mkdir -p $(OBJ_DIR_ASM)

FORCE: ;

$(LIBFT): FORCE
	make -C libft

clean:
	-rm -f $(OBJ)
	-rm -rf $(OBJ_DIR_ASM)
	make -C $(LIB_DIR) clean

fclean: clean

	-rm -f $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
