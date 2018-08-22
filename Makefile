# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/23 09:51:26 by jngoma            #+#    #+#              #
#    Updated: 2018/08/22 08:08:15 by amatshiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_3_NAME = glfw_tut

CMP = clang++

SRC = main.cpp Image_Loader/loader.o Shader.cpp

FLAGS = -Wall -Werror -Wextra -std=c++11 

HEADER = -I ~/.brew/include

GLEW_HEADER = -I ~/.brew/Cellar/glew/2.1.0/include

GLEW_LIB = -L ~/.brew/Cellar/glew/2.1.0/lib

GLEW_FLAGS = -DGLEW_STATIC -lGLEW

LIB = -L ~/.brew/lib

LD_FLAG = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo

all:
	$(MAKE) -C Image_Loader/
	$(CPP) $(SRC) $(HEADER) $(GLEW_HEADER) \
	$(FLAGS)

test:
	$(MAKE) -C Image_Loader/
	clang++ $(SRC) -o $(LIB_3_NAME) -lglfw3 -I ~/.brew/include -L ~/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -I include glad.o -Wall -Werror -Wextra

clean:
	rm -rf $(LIB_3_NAME)

fclean: clean
	$(MAKE) fclean -C Image_Loader/

re: fclean all
