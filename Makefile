NAME	= ircserv
CXX		= c++
FLAGS	= -Wall -Werror -Wextra -std=c++98 #-g
RM 		= rm -rf

PORT	?= 6666
PASS	?= 1234

# =================================================================================

INCLUDES_PATH		= includes
INCLUDES_SUBDIRS	= commands parser exceptions
INCLUDES_DIRS		= $(INCLUDES_PATH) $(addprefix $(INCLUDES_PATH)/, $(INCLUDES_SUBDIRS))

HEADERS				= $(addprefix -I, $(INCLUDES_DIRS))

# =================================================================================

SRC_DIR		= src
CMD_DIR		= $(SRC_DIR)/commands/
PARSER_DIR	= $(SRC_DIR)/parser/

CMD_PREFIXS		= User Nick Pass Quit PrivateMessage Join Part Invite Kick
CMD_FILES		= $(addsuffix Command, $(CMD_PREFIXS))
CMD_SRCS		= $(addprefix $(CMD_DIR), $(CMD_FILES))

PARSER_PREFIXS	= Command User Pass Nick Quit PrivateMessage Join Part Invite Kick
PARSER_FILES	= $(addsuffix Parser, $(PARSER_PREFIXS))
PARSER_SRCS		= $(addprefix $(PARSER_DIR), $(PARSER_FILES))

FILES 			= main Server User Channel libsUtils Logger

SRCS_PATHS		= $(addprefix $(SRC_DIR)/, $(FILES)) $(CMD_SRCS) $(PARSER_SRCS)
SRCS			= $(addsuffix .cpp, $(SRCS_PATHS))

OBJS			= $(SRCS:.cpp=.o)

# =================================================================================

all:		$(NAME)

%.o:		%.cpp
	$(CXX) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CXX) $(FLAGS) $(HEADERS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)
#	$(RM) $(NAME).dSYM

re: 		fclean all

e:			re
	clear
	./$(NAME) $(PORT) $(PASS)
	make fclean

.PHONY: all clean fclean re e
