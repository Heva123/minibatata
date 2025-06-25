NAME = minishell

SRC_DIR = src
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

RM = rm -rf

SRCS = \
        minishell.c \
        parsing/parsing.c \
        parsing/pipe.c \
        parsing/redirections.c \
        parsing/quotes.c \
        parsing/tokonizer.c \
        execution/execution.c \
        execution/path.c \
        execution/pipe.c \
        execution/redirections.c \
        execution/heredoc.c \
        builtins/echo.c \
        builtins/cd.c \
        builtins/pwd.c \
        builtins/export.c \
        builtins/unset.c \
        builtins/env.c \
        builtins/exit.c \
        builtins/utils.c \
		signals/signals.c \
        utils/ft_split.c \
        utils/ft_strjoin.c \
        utils/ft_strncmp.c \
        utils/ft_strchr.c \
        utils/ft_strlen.c \
        utils/ft_strdup.c \
        utils/ft_strtrim.c \
        utils/ft_strrchr.c \
        utils/ft_free.c \
        utils/ft_strndup.c \
        utils/ft_memcpy.c \
        utils/ft_putstr_fd.c \
		utils/ft_isdigit.c \
		utils/ft_atoi.c \
		utils/ft_isalnum.c \
		utils/ft_strcmp.c


SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
