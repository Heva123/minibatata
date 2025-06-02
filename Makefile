NAME = minishell

SRC_DIR = src
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
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
		utils/ft_split.c \
		utils/ft_strjoin.c \
		utils/ft_strncmp.c \
		utils/ft_strchr.c \
		utils/ft_strlen.c \
		utils/ft_strdup.c \
		utils/ft_strtrim.c \
		utils/ft_strrchr.c\
		utils/ft_free.c


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
