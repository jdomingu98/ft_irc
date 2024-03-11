NAME		= ircserv
CXX			= c++
CPP_FLAGS	= -Wall -Werror -Wextra -std=c++98

# =================================================================================

INCLUDES_PATH	= includes
CMD_PATH		= $(INCLUDES_PATH)/commands
PARSER_PATH		= $(INCLUDES_PATH)/parser
EXCEPTIONS_PATH	= $(INCLUDES_PATH)/exceptions

HEADERS			= -I $(INCLUDES_PATH) \
					-I $(CMD_PATH) \
					-I $(PARSER_PATH) \
					-I $(EXCEPTIONS_PATH)

# =================================================================================

SRC_DIR		= src
CMD_DIR		= $(SRC_DIR)/commands/
PARSER_DIR	= $(SRC_DIR)/parser/


CMD_FILES		= UserCommand.cpp PassCommand.cpp
CMD_SRCS		= $(addprefix $(CMD_DIR), $(CMD_FILES))

PARSER_FILES	= CommandParser.cpp UserParser.cpp PassParser.cpp
PARSER_SRCS		= $(addprefix $(PARSER_DIR), $(PARSER_FILES))

FILES 			= Server.cpp main.cpp utils.cpp User.cpp
SRCS			= $(addprefix $(SRC_DIR)/, $(FILES)) $(CMD_SRCS) $(PARSER_SRCS)

OBJS			= $(SRCS:.cpp=.o)

# =================================================================================

PORT	?= 6666
PASS	?= 1234

all:		$(NAME)

%.o:		%.cpp
	$(CXX) $(CPP_FLAGS) $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CXX) $(CPP_FLAGS) $(HEADERS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -f $(NAME)

re: 	fclean all

e:			re 
	./$(NAME) $(PORT) $(PASS)
	make fclean

.PHONY: all clean fclean re e
