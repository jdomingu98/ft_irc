NAME	= ircserv
BOT = bot
CXX		= c++
FLAGS	= -Wall -Werror -Wextra -std=c++98
RM 		= rm -rf

PORT	?= 6667
PASS	?= 1111

# =================================================================================

INCLUDES_PATH		= includes
INCLUDES_SUBDIRS	= commands parser exceptions irc_bot
INCLUDES_DIRS		= $(INCLUDES_PATH) $(addprefix $(INCLUDES_PATH)/, $(INCLUDES_SUBDIRS))

HEADERS				= $(addprefix -I , $(INCLUDES_DIRS))

# =================================================================================

SRC_DIR		= src
CMD_DIR		= $(SRC_DIR)/commands/
PARSER_DIR	= $(SRC_DIR)/parser/
BOT_DIR		  = $(SRC_DIR)/irc_bot
BOT_MSG_DIR	  = $(BOT_DIR)/message/
BOT_RESP_DIR  = $(BOT_DIR)/response/


CMD_PREFIXS		= A User Nick Pass Quit PrivateMessage Join Part Invite Mode Kick Topic Notice
CMD_FILES		= $(addsuffix Command, $(CMD_PREFIXS))
CMD_SRCS		= $(addprefix $(CMD_DIR), $(CMD_FILES))

PARSER_PREFIXS	= Command User Pass Nick Quit PrivateMessage Join Part Invite Mode Kick Topic Notice
PARSER_FILES	= $(addsuffix Parser, $(PARSER_PREFIXS))
PARSER_SRCS		= $(addprefix $(PARSER_DIR), $(PARSER_FILES))

FILES 			= main Server User Channel Utils Logger Responses

SRCS_PATHS	= $(addprefix $(SRC_DIR)/, $(FILES)) $(CMD_SRCS) $(PARSER_SRCS)
SRCS			  = $(addsuffix .cpp, $(SRCS_PATHS))

# =================================================================================

# Bonus part (file transfer)
BPREFIXS		  = Who Down Up
BCMD_FILES		= $(addsuffix Command, $(BPREFIXS))
BCMD_SRCS 		= $(addprefix $(CMD_DIR), $(BCMD_FILES))

BPARSER_FILES	= $(addsuffix Parser, $(BPREFIXS))
BPARSER_SRCS	= $(addprefix $(PARSER_DIR), $(BPARSER_FILES))

BSRCS_PATHS		= $(BCMD_SRCS) $(BPARSER_SRCS) 
BSRCS			= $(addsuffix .cpp, $(BSRCS_PATHS))

OBJS			= $(SRCS:.cpp=.o)
BOBJS			= $(BSRCS:.cpp=.o)

# =================================================================================

# Bonus part (bot)
BOT_MSG_PREFIXS	= Message SenderEntity
BOT_MSG_FILES	  = $(addsuffix .cpp, $(addprefix $(BOT_MSG_DIR), $(BOT_MSG_PREFIXS)))

BOT_RESP_PREFIXS	= ResponseBuilder
BOT_RESP_FILES		= $(addsuffix .cpp, $(addprefix $(BOT_RESP_DIR), $(BOT_RESP_PREFIXS)))

BOT_FILES = GlaskBot IRCClient bot
BOT_SRCS	= $(BOT_MSG_FILES) $(BOT_RESP_FILES) $(addsuffix .cpp, $(addprefix $(BOT_DIR)/, $(BOT_FILES)))

#BOT_SRCS	= src/irc_bot/GlaskBot.cpp src/irc_bot/IRCClient.cpp src/irc_bot/bot.cpp\
			  src/irc_bot/message/Message.cpp src/irc_bot/message/SenderEntity.cpp\
			  src/irc_bot/response/ResponseBuilder.cpp
BOT_OBJS	= $(BOT_SRCS:.cpp=.o)

# =================================================================================

all:		$(NAME)

%.o:		%.cpp
	$(CXX) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CXX) $(FLAGS) $(HEADERS) $(SRCS) -o $(NAME)

clean: 		bot_clean
	$(RM) $(OBJS) $(BOBJS) files

fclean:		clean bot_fclean
	$(RM) $(NAME)

re: 		fclean all

e:			re
	clear
	./$(NAME) $(PORT) $(PASS)

a:			$(NAME)
	clear
	./$(NAME) $(PORT) $(PASS)

bonus: 	$(OBJS) $(BOBJS) $(BOT)
	$(CXX) $(FLAGS) -D BONUS $(HEADERS) $(SRCS) $(BSRCS) -o $(NAME)
	$(RM) files
	mkdir files

be: 		bre
	clear
	./$(NAME) $(PORT) $(PASS)

ba:			bonus
	clear
	./$(NAME) $(PORT) $(PASS)

bre:		fclean bonus $(BOT)

# Bonus rules (bot)

$(BOT): $(BOT_OBJS)
	$(CXX) $(FLAGS) $(HEADERS) $(BOT_OBJS) -o $(BOT)

bot_clean:
	$(RM) $(BOT_OBJS)

bot_fclean: bot_clean
	$(RM) $(BOT)

.PHONY: a all ba be bre bonus clean e fclean re bot_clean bot_fclean