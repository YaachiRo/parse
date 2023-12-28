
NAME = check

SRCS =	tools.c \
		parse.c \
		whitesplit.c \
		camera_light.c \
		get_type.c		\
		objects.c 		\

RM = rm -rf

CC = cc

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

LDFLAGS = -Llibft -lft -lm

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