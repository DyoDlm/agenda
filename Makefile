SRC = srcs/what.cpp
NAME = look
CC = c++ -Wall -Wextra -Werror

all:
	$(CC) $(SRC) -o $(NAME)

clean: $(NAME)
	rm $(NAME)

re: $(NAME)
	clean
	all
