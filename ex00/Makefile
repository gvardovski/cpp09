CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g
NAME = btc
SRC =  main.cpp \
	BitcoinExchange.cpp 
OBJ = $(SRC:.cpp=.o)
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJ)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re