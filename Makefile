F_NONE			= \033[37;0m
F_BOLD			= \033[1m
F_GREEN			= \033[32m
F_CYAN			= \033[36m


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC			= @gcc
CFLAGS		= -Wall -Wextra -Werror -g -fPIC
LIGHTFLAGS	= -Wall -Wextra -Werror -g -Wno-free-nonheap-object

NAME		= libft_malloc_$(HOSTTYPE).so
TEST		= mallocTest

SRCS		= src/malloc.c src/realloc.c src/free.c \
				src/utils.c src/block.c src/print.c \
				src/show_alloc_mem.c src/zones.c

SRCS_TEST	= main.c
INCLUDES	= inc/malloc.h

OBJ			= $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJ) $(INCLUDES)
	@$(CC) -shared -o $(NAME) $(OBJ)
	ln -s $(NAME) libft_malloc.so
	@echo "$(F_GREEN)$(F_BOLD)$(NAME) library is compiled.$(F_NONE)"

test:
	@$(CC) $(LIGHTFLAGS) $(SRCS_TEST) -L. -lft_malloc -o $(TEST)
	@echo "$(F_GREEN)$(F_BOLD)$(TEST) is ready.$(F_NONE)"

clean:
	@rm -rf $(OBJ) 
	@echo "$(F_CYAN)$(F_BOLD).o files successfully deleted.$(F_NONE)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf libft_malloc.so
	@rm -rf $(TEST)
	@echo "$(F_CYAN)$(F_BOLD)$(NAME) library successfully deleted.$(F_NONE)"

re: fclean all

.PHONY: all clean fclean re test