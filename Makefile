NAME		= ircserv
CPP_FLAGS	= -Wall -Werror -Wextra -std=c++98
SRCS		= main.cpp
OBJS		= $(SRCS:.cpp=.o)

class	   ?= class
UPPER		= $(shell echo $(class) | tr '[:lower:]' '[:upper:]')
FST_UP		= $(shell echo "$(class)" | awk '{print toupper(substr($$0, 1, 1)) tolower(substr($$0, 2))}')

all:	$(NAME)

create_hpp:
	@rm -f $(FST_UP).hpp
	@echo "#ifndef $(UPPER)_HPP" > $(FST_UP).hpp
	@echo "# define $(UPPER)_HPP" >> $(FST_UP).hpp
	@echo >> $(FST_UP).hpp
	@echo "# include <iostream>" >> $(FST_UP).hpp
	@echo "# include <string>" >> $(FST_UP).hpp
	@echo >> $(FST_UP).hpp
	@echo "class $(FST_UP)" >> $(FST_UP).hpp
	@echo "{" >> $(FST_UP).hpp
	@echo "	private:" >> $(FST_UP).hpp
	@echo "		$(FST_UP)();" >> $(FST_UP).hpp
	@echo "	public:" >> $(FST_UP).hpp
	@echo "		~$(FST_UP)();" >> $(FST_UP).hpp
	@echo "		$(FST_UP)($(FST_UP) const &o);" >> $(FST_UP).hpp
	@echo "		$(FST_UP) &operator=($(FST_UP) const &o);" >> $(FST_UP).hpp
	@echo "};" >> $(FST_UP).hpp
	@echo >> $(FST_UP).hpp
	@echo "#endif" >> $(FST_UP).hpp

create_cpp:
	@rm -f $(FST_UP).cpp
	@echo "#include \"$(FST_UP).hpp\"" >> $(FST_UP).cpp
	@echo >> $(FST_UP).cpp
	@echo "$(FST_UP)::$(FST_UP)() {}" >> $(FST_UP).cpp
	@echo >> $(FST_UP).cpp
	@echo "$(FST_UP)::~$(FST_UP)() {}" >> $(FST_UP).cpp
	@echo >> $(FST_UP).cpp
	@echo "$(FST_UP)::$(FST_UP)($(FST_UP) const &o)" >> $(FST_UP).cpp
	@echo "{" >> $(FST_UP).cpp
	@echo "	*this = o;" >> $(FST_UP).cpp
	@echo "}" >> $(FST_UP).cpp
	@echo >> $(FST_UP).cpp
	@echo "$(FST_UP) &$(FST_UP)::operator=($(FST_UP) const &o)" >> $(FST_UP).cpp
	@echo "{" >> $(FST_UP).cpp
	@echo "	//attributeClass = o.attributeClass;">> $(FST_UP).cpp
	@echo "	return *this;" >> $(FST_UP).cpp
	@echo "}" >> $(FST_UP).cpp
	@echo >> $(FST_UP).cpp

create: create_hpp create_cpp

%.o:	%.cpp
	c++ $(CPP_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	c++ $(CPP_FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: 	fclean all

e:		re
	./$(NAME)
	make fclean

.PHONY: all clean fclean re create create_hpp create_cpp e