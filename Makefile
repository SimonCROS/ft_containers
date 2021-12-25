# Properties

NAME				:= ft_containers
STL_NAME			:= stl_containers
FT_OUT				:= out_ft.diff
STL_OUT				:= out_stl.diff

# Commands

override CPPC		:= clang++
override CPPFLAGS	:= -Wall -Wextra -Werror -std=c++98
override RM			:= rm -rf

# Sources

override SRCS		:=							\
				main.cpp						\

override HEADERS	:=							\
				type_traits.hpp					\
				iterator.hpp					\
				vector.hpp						\
				stack.hpp						\
				map.hpp							\

# Rules

all:		$(NAME) $(STL_NAME)

$(NAME):	$(SRCS)
			$(CPPC) $(CPPFLAGS) -o $@ $(SRCS)

$(STL_NAME):	$(SRCS)
			$(CPPC) $(CPPFLAGS) -o $@ $(SRCS) -DSTL_CONTAINERS

clean:
			$(RM) $(FT_OUT) $(STL_OUT)

fclean:		clean
			$(RM) $(NAME) $(STL_NAME)

re:			fclean all

test:		all
			./$(NAME) > $(FT_OUT)
			./$(STL_NAME) > $(STL_OUT)

.PHONY:		all clean fclean re test
