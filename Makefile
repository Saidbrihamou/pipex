SRCS	= Mandatory/main.c Mandatory/ft_strlen.c Mandatory/ft_putstr_fd.c Mandatory/ft_split.c Mandatory/get_path_cmd.c \
		  Mandatory/ft_memcpy.c Mandatory/ft_strdup.c  Mandatory/ft_strjoin.c Mandatory/ft_strlcpy.c \
		  Mandatory/first_prooses.c Mandatory/last_prooses.c Mandatory/ft_strncmp.c

SRCS_bonus	= bonus/main_bonus.c bonus/ft_strlen_bonus.c bonus/ft_putstr_fd_bonus.c bonus/ft_split_bonus.c bonus/get_path_cmd_bonus.c \
		 	 bonus/ft_memcpy_bonus.c bonus/ft_strdup_bonus.c  bonus/ft_strjoin_bonus.c bonus/ft_strlcpy_bonus.c \
		 	 bonus/first_prooses_bonus.c bonus/last_prooses_bonus.c bonus/ft_strncmp_bonus.c bonus/multiple_pipes_bonus.c \
			 bonus/Here_document_bonus.c bonus/get_next_line_utils.c bonus/get_next_line.c bonus/here_doc_util_bonus.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS  = ${SRCS_bonus:.c=.o}
NAME		= pipex
FLAGE		= -Wall -Wextra -Werror

all: ${NAME}

${NAME} : ${OBJS}
		cc ${FLAGE} ${OBJS} -o ${NAME}
bonus : ${OBJS_BONUS} bonus/pipex_bonus.H
		cc ${FLAGE} ${OBJS_BONUS} -o ${NAME}


Mandatory/%.o:Mandatory/%.c Mandatory/pipex.h
		cc -c ${FLAGE} $< -o $@
bonus/%.o:bonus/%.c bonus/pipex_bonus.h
		cc -c ${FLAGE} $< -o $@
clean:
	rm -rf ${OBJS} ${OBJS_BONUS}

fclean: clean
		rm -rf ${NAME}
re: fclean all


