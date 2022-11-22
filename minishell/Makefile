NAME = minishell

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

CC = gcc

RM = rm -rf

SRC = \
		lexer/lexer.c\
		lexer/lexer_utils.c\
		lexer/token.c\
		lexer/handle_quotes.c\
		lexer/add_herdoc.c\
		lexer/expand.c\
		parser/check.c\
		lexer/expand_utils.c\
		lexer/ft_itoa.c\
		lexer/split_expand.c\
		lexer/ft_split.c\
		main.c\
		parser/syntax_error.c\
		parser/print.c\
		parser/split_cmds.c\
		parser/parsing.c\
		parser/parsing_utils.c\
		parser/libft_functions.c\
		parser/ft_free.c\
		# env_management.c\
		# heredoc.c\
		# libft.c\
		# checks.c\
		# builtins/cd.c\
		# builtins/echo.c\
		# builtins/pwd.c\
		# builtins/env.c\
		# builtins/unset.c\
		# builtins/export.c\
		# builtins/builtins.c\
		

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
clean :
		@$(RM) $(OBJ)
fclean :
		@$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY : all clean fclean