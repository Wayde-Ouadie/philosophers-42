SRC = philo.c parsing_args.c routine.c end.c
OBJ = ${SRC:.c=.o}
NAME = philo
CC = cc
RM = rm -f
FLAG = -Wall -Wextra -Werror # -fsanitize=thread -g # -g -fsanitize=address

all: ${NAME}

%.o:%.c philo.h
	@${CC} ${FLAG} -c $<

${NAME}: ${OBJ}
	@${CC} ${FLAG} $^ -o ${NAME}

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all