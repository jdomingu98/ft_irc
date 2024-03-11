NAME		= ircserv
CPP_FLAGS	= -Wall -Werror -Wextra -std=c++98 -I includes
SRCS		= src/main.cpp \
					src/utils.cpp \
					src/Server.cpp \
					src/CommandParser.cpp \
					src/commands/UserCommand.cpp \
					src/parser/UserParser.cpp
OBJS		= $(SRCS:.cpp=.o)

port		?= 6666
pass		?= 1234

all:		$(NAME)

%.o:		%.cpp
	c++ $(CPP_FLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	c++ $(CPP_FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -f $(NAME)

re: 	fclean all

e:			re 
	./$(NAME) $(port) $(pass)
	make fclean

.PHONY: all clean fclean re e
