##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my makefile
##

SRC = src/main.cpp \
      src/Displays/Ncurses.cpp 
OBJ = $(SRC:.cpp=.o)
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -lncurses
NAME = myGKrellm
CC = clang++

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
