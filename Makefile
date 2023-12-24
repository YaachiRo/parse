
NAME = check

SRCS =	get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		tools.c \
		parse.c \
		whitesplit.c \
		camera_light.c \
		get_type.c

RM = rm -rf

CC = cc

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra  -fsanitize=address -g3

LDFLAGS = -Llibft -lft

all: libft ${NAME}

${NAME}: ${OBJS}
	${CC} $(CFLAGS) ${OBJS} ${LDFLAGS} -o ${NAME}

clean:
	@$(MAKE) clean -C libft
	${RM} ${OBJS}

fclean: clean
	@$(MAKE) fclean -C libft
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean all re libft

libft:
	@$(MAKE) -C libft