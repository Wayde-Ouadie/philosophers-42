SRC = philo.c philo_utils.c
SRC_BNS = philo_bonus.c philo_bonus_utils.c
OBJ = ${SRC:.c=.o}
OBJ_BNS = ${SRC_BNS:.c=.o}
NAME = philo
NAME_BNS = philo_bonus
CC = cc
RM = rm -f
FLAG = -Wall -Wextra -Werror

all: ${NAME}

mandatory/%.o: mandatory/%.c mandatory/philo.h
	@${CC} ${FLAG} -c $< -o $@

bonus/%.o: bonus/%.c bonus/philo_bonus.h
	@${CC} ${FLAG} -c $< -o $@

${NAME}: ${OBJ}
	@${CC} ${FLAG} $^ -o ${NAME}

bonus: ${OBJ_BNS}
	@${CC} ${FLAG} ${OBJ_BNS} -o ${NAME_BNS}

clean:
	@${RM} ${OBJ} ${OBJ_BNS}

fclean: clean
	@${RM} ${NAME} ${NAME_BNS}

re: fclean all