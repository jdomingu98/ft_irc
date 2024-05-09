NAME	= ircserv
CXX		= c++
FLAGS	= -Wall -Werror -Wextra -std=c++98
RM 		= rm -rf

PORT	?= 6667
PASS	?= 1111

# =================================================================================

INCLUDES_PATH		= includes
INCLUDES_SUBDIRS	= commands parser exceptions
INCLUDES_DIRS		= $(INCLUDES_PATH) $(addprefix $(INCLUDES_PATH)/, $(INCLUDES_SUBDIRS))

HEADERS				= $(addprefix -I , $(INCLUDES_DIRS))

# =================================================================================

SRC_DIR		= src
CMD_DIR		= $(SRC_DIR)/commands/
PARSER_DIR	= $(SRC_DIR)/parser/

CMD_PREFIXS		= A User Nick Pass Quit PrivateMessage Join Part Invite Mode Kick Topic Notice Who Down Up
CMD_FILES		= $(addsuffix Command, $(CMD_PREFIXS))
CMD_SRCS		= $(addprefix $(CMD_DIR), $(CMD_FILES))

PARSER_PREFIXS	= Command User Pass Nick Quit PrivateMessage Join Part Invite Mode Kick Topic Notice Who Down Up
PARSER_FILES	= $(addsuffix Parser, $(PARSER_PREFIXS))
PARSER_SRCS		= $(addprefix $(PARSER_DIR), $(PARSER_FILES))

FILES 			= main Server User Channel Utils Logger Responses

SRCS_PATHS		= $(addprefix $(SRC_DIR)/, $(FILES)) $(CMD_SRCS) $(PARSER_SRCS)
SRCS			= $(addsuffix .cpp, $(SRCS_PATHS))

OBJS			= $(SRCS:.cpp=.o)

# =================================================================================

all:		$(NAME)

%.o:		%.cpp
	$(CXX) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
	$(RM) files
	mkdir files
	$(CXX) $(FLAGS) $(HEADERS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) files

fclean:		clean
	$(RM) $(NAME)

re: 		fclean all

e:			re
	clear
	./$(NAME) $(PORT) $(PASS)

a:			$(NAME)
	clear
	./$(NAME) $(PORT) $(PASS)



BOT_SRCS	= src/irc_bot/GlaskBot.cpp src/irc_bot/IRCClient.cpp src/irc_bot/bot.cpp\
			  src/irc_bot/message/Message.cpp src/irc_bot/message/SenderEntity.cpp\
			  src/irc_bot/response/ResponseBuilder.cpp
BOT_OBJS	= $(BOT_SRCS:.cpp=.o)

bot: $(BOT_OBJS)
	$(CXX) $(FLAGS) $(HEADERS) $(BOT_OBJS) -o bot

clean_bot:
	$(RM) $(BOT_OBJS)

re_bot: clean_bot bot

.PHONY: all clean fclean re e a clean_bot re_bot
