CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
COMMANDS	= Command Invite Join Kick Mode Nick Pass Privmsg Topic User Ping
SRC			= Server main Channel Client Message MessageHandler Reply Resource Bot $(addprefix Command/, $(COMMANDS))
SRCS		= $(addprefix ./Source/, $(addsuffix .cpp, $(SRC)))
OBJS_DIR	= ./Object/
OBJS		= $(SRCS:.cpp=.o)
OBJS_O		= $(addprefix $(OBJS_DIR), $(OBJS))
INCS		= -I./Include -I./Include/Command
NAME		= ircserv

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $^

$(OBJS): %.o : %.cpp
#	mkdir -p $(OBJS_DIR)/Source/Command
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

clean	:
	$(RM) -r $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY	: all clean fclean re