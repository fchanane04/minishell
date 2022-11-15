NAME = minishell

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

CC = gcc

RM = rm -rf

SRC = \
		lexer/lexer.c\
		lexer/lexer_utils.c\
		lexer/token.c\
		lexer/handle_quotes.c\
		check.c\
		main.c\
		syntax_error.c\
		print.c\
		split_cmds.c\
		last_parsing.c\
		heredoc.c\
		libft.c\
		checks.c\
		builtins/cd.c\
		builtins/echo.c\
		builtins/pwd.c\
		builtins/env.c\
		builtins/unset.c\
		builtins/export.c\
		builtins/builtins.c\
		env_management.c\
		

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