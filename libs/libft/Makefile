# Colors
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
RED     = \033[1;31m
NC      = \033[0m

NAME = libft.a
CCFLAGS = -Wall -Wextra -Werror
CC = cc
INCLUDE = -I srcs/includes
AR = ar -rcs
RM = rm -f

OBJDIR = objs

PART1 = srcs/part1/ft_isalpha.c \
		srcs/part1/ft_isdigit.c \
		srcs/part1/ft_isalnum.c \
		srcs/part1/ft_isascii.c \
		srcs/part1/ft_isprint.c \
		srcs/part1/ft_strlen.c \
		srcs/part1/ft_memset.c \
		srcs/part1/ft_bzero.c \
		srcs/part1/ft_memcpy.c \
		srcs/part1/ft_memmove.c \
		srcs/part1/ft_strlcpy.c \
		srcs/part1/ft_strlcat.c \
		srcs/part1/ft_toupper.c \
		srcs/part1/ft_tolower.c \
		srcs/part1/ft_strchr.c \
		srcs/part1/ft_strrchr.c \
		srcs/part1/ft_strncmp.c \
		srcs/part1/ft_memchr.c \
		srcs/part1/ft_memcmp.c \
		srcs/part1/ft_strnstr.c \
		srcs/part1/ft_atoi.c \
		srcs/part1/ft_strdup.c \
		srcs/part1/ft_calloc.c

PART2 = srcs/part2/ft_substr.c \
		srcs/part2/ft_strjoin.c \
		srcs/part2/ft_strtrim.c \
		srcs/part2/ft_split.c \
		srcs/part2/ft_itoa.c \
		srcs/part2/ft_strmapi.c \
		srcs/part2/ft_striteri.c \
		srcs/part2/ft_putchar_fd.c \
		srcs/part2/ft_putstr_fd.c \
		srcs/part2/ft_putendl_fd.c \
		srcs/part2/ft_putnbr_fd.c

PRINTF = srcs/printf/ft_printf.c \
		 srcs/printf/ft_printf_utils.c

GNL = srcs/gnl/get_next_line.c

SRCS = ${PART1} ${PART2} ${PRINTF} ${GNL}

BONUS_SRC = srcs/bonus/ft_lstnew_bonus.c \
			srcs/bonus/ft_lstadd_front_bonus.c \
			srcs/bonus/ft_lstsize_bonus.c \
			srcs/bonus/ft_lstlast_bonus.c \
			srcs/bonus/ft_lstadd_back_bonus.c \
			srcs/bonus/ft_lstdelone_bonus.c \
			srcs/bonus/ft_lstclear_bonus.c \
			srcs/bonus/ft_lstiter_bonus.c \
			srcs/bonus/ft_lstmap_bonus.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS = $(BONUS_SRC:%.c=$(OBJDIR)/%.o)

all: ${NAME}

${NAME}: ${OBJS} ${OBJS_BONUS}
	@${AR} ${NAME} ${OBJS} ${OBJS_BONUS}
	@printf "$(GREEN)✔  Library '${NAME}' created successfully!$(NC)\n"

# Create obj folder + subfolders automatically
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${CCFLAGS} ${INCLUDE} -c $< -o $@

bonus: ${OBJS} ${OBJS_BONUS}
	@${AR} ${NAME} ${OBJS_BONUS}
	@printf "$(GREEN)⭐  Bonus compiled and added to library!$(NC)\n"

clean:
	@${RM} -r ${OBJDIR}
	@printf "$(RED)🧹 Object files removed$(NC)\n"

fclean: clean
	@${RM} ${NAME}
	@printf "$(RED)🗑  Library removed$(NC)\n"

re: fclean all

.PHONY: all clean fclean re bonus
