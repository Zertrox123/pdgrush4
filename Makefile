##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my makefile
##

SRC = src/main.cpp \
      src/Displays/Ncurses.cpp \
      src/Displays/Sfml.cpp
OBJ = $(SRC:.cpp=.o)
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system -lncurses -I./src
NAME = myGKrellm
CC = clang++

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
