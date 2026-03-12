# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamys <kamys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/03 08:51:15 by cassunca          #+#    #+#              #
#    Updated: 2026/03/12 17:56:35 by kamys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- Settings ----------
NAME		= $(BINDIR)/cub3d

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;95m
NC			= \033[0m

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g2 -MMD -MP
INCLUDE		= -I $(LIBS_DIR)/libft/srcs/includes -I includes -I $(LIBS_DIR)/minilibx-linux
MLX 		= -L$(LIBS_DIR)/minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

RM			= rm -rf
RUNLIB		= -C $(LIBS_DIR)/libft
RUNMLX      = -C $(LIBS_DIR)/minilibx-linux

# Directories
SRCSDIR		= src
OBJDIR		= .objs
BINDIR		= bin
LIBS_DIR	= libs

# Source files
SRCS		= main.c

# Add directory prefix

SRCS		:= $(addprefix $(SRCSDIR)/, $(SRCS))

# Object files
OBJS		= $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)
TOTAL		= $(words $(OBJS))
COUNT		= 0

DEPS		= $(OBJS:.o=.d)

# Libs
LIBFT		= $(LIBS_DIR)/libft/libft.a
MLX_LIB		= $(LIBS_DIR)/minilibx-linux/libmlx.a

# ---------- Rules ----------
all: $(NAME)
	@printf "$(GREEN)✅ $(NAME) is ready!$(NC)\n"

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX) -o $(NAME)
	@printf "$(GREEN)🎉 Executable $(NAME) successfully created!$(NC)\n"

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PROGRESS=$$((100 * $(COUNT) / $(TOTAL))); \
	BAR_LEN=$$((20 * $(COUNT) / $(TOTAL))); \
	BAR=""; EMPTY=""; \
	FULL_LEN=$$((BAR_LEN * 10 / 10)); \
	MID_LEN=$$((BAR_LEN - FULL_LEN)); \
	for i in $$(seq 1 $$FULL_LEN); do BAR="$${BAR}▓"; done; \
	for i in $$(seq 1 $$MID_LEN); do BAR="$${BAR}▒"; done; \
	for i in $$(seq $$((BAR_LEN+1)) 20); do EMPTY="$${EMPTY}░"; done; \
	printf "\r\033[K$(PURPLE)Compiling: $(GREEN)[$$BAR$$EMPTY] %3d%% $(BLUE)[%d/%d]$(PURPLE) -> %s$(NC)" \
	$$PROGRESS $(COUNT) $(TOTAL) $<
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Compile libft silently
$(LIBFT):
	@$(MAKE) $(RUNLIB) -j -s > /dev/null 2>&1
	@printf "\n$(GREEN)✅ Libft successfully compiled$(NC)\n"

# Compile minilibx silently
$(MLX_LIB):
	@$(MAKE) $(RUNMLX) -s > /dev/null 2>&1
	@printf "$(GREEN)✅ MiniLibX compilada com sucesso$(NC)\n"

# Cleanup
clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean $(RUNLIB) -s > /dev/null 2>&1
	@$(MAKE) clean $(RUNMLX) -s > /dev/null 2>&1
	@printf "$(YELLOW)🧹 Objects cleaned$(NC)\n"

fclean: clean
	@$(RM) $(BINDIR)
	@$(MAKE) fclean $(RUNLIB) -s > /dev/null 2>&1
	@printf "$(YELLOW)🗑️ Executable removed$(NC)\n"

valgrind:
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
