# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/20 09:55:11 by amatshiy          #+#    #+#              #
#    Updated: 2018/08/20 10:00:01 by amatshiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = loader.o

CMP = clang++ -c

SRC = image_loader.cpp

all:
	$(CMP) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all