DEF_COLOR = \033[0;39m
RED = \033[0;91m
YELLOW = \033[0;93m
GREEN = \033[0;92m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
PURPLE= \033[38;2;255;105;180m
RESET= \033[0m

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

INC = include/pipex.h
SRCS = pipex.c \

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a
LIBFTPRINTF = ./libft/ft_printf/libftprintf.a

NAME = pipex

all : $(NAME) $(LIBFT) $(LIBFTPRINTF)

$(LIBFT) :
	@make -sC libft

$(NAME) : $(OBJS) $(INC) $(LIBFT) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFTPRINTF)
	@echo "$(GREEN)$(NAME) created$(RESET)"

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@make -sC libft clean
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@make -sC libft fclean
	@echo "$(RED)$(NAME) deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re