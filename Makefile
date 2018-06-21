# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pribault <pribault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 17:51:26 by pribault          #+#    #+#              #
#    Updated: 2018/06/21 17:07:18 by pribault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	avm
FLAGS =	-Wall -Wextra -std=c++11
CC =	clang++

SRC_DIR =	src
OBJ_DIR =	.obj
INC_DIR =	include

SRC =	avm.cpp OperandFactory.cpp
OBJ =	$(sort $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC)))
INC =	avm.hpp IOperand.hpp OperandFactory.hpp Operand.hpp
DEP =	$(sort $(patsubst %.hpp, $(INC_DIR)/%.hpp, $(INC)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP) | $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -I $(INC_DIR) -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
