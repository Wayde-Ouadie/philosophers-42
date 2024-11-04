SRC = philo/philo.c philo/utils.c
OBJ = ${SRC:.c=.o}
NAME = philo
CC = cc
RM = rm -f
FLAG = -Wall -Wextra -Werror #-fsanitize=address

all: ${NAME}

%.o:%.c philo.h
	@${CC} ${FLAG} -c $<

${NAME}: ${OBJ}
	@${CC} ${FLAG} $^ -o ${NAME}

clean:
	@${RM} ${OBJ} ${OBJ_BNS}

fclean: clean
	@${RM} ${NAME} ${NAME_BNS}

re: fclean all