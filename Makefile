# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/18 14:42:35 by ddevico           #+#    #+#              #
#    Updated: 2017/10/25 21:41:32 by davydevico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM     =   ft_nm
NAME_OTOOL	=	ft_otool

SRC_DIR_NM	= ./src/nm
SRC_DIR_OTOOL	= ./src/otool

SRC_NM =	ft_nm.c \
		sort.c \
		display.c \
		arch_64.c \
		arch_32.c \
		arch_lib.c \
		utils.c   \
		arch_fat.c

SRC_OTOOL =	ft_otool.c \
						arch_lib.c \


O_DIR_NM	= ./obj/nm
OBJ_NM		= $(addprefix $(SRC_DIR_NM)/,$(SRC_NM:.c=.o))
O_DIR_OTOOL	= ./obj/otool
OBJ_OTOOL		= $(addprefix $(SRC_DIR_OTOOL)/,$(SRC_OTOOL:.c=.o))

CC = gcc

CFLAGS = #-Wall -Werror -Wextra -g

HEADERS = -I inc/

I_LIBFT = -I libft/inc/

I_PRINTF = libft/ft_printf/libftprintf.a

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): ft_nm

$(NAME_OTOOL): ft_otool

ft_nm: obj $(OBJ_NM)
	@echo "\n"---------------------- NM COMPILING -------------------------
	@echo "\n\033[31m==> COMPILING in progress ...\033[0m\n"
	@make -C libft
	@$(CC) $(WFLAGS) -o $@ $(OBJ_NM) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\033[37mNM: \033[35mOK\n"
	@echo "\033[32m==> SUCCESS !\033[0m\n"

ft_otool: obj $(OBJ_OTOOL)
		@echo "\n"---------------------- OTOOL COMPILING -------------------------
		@echo "\n\033[31m==> COMPILING in progress ...\033[0m\n"
		@make -C libft
		@$(CC) $(WFLAGS) $(HEADERS) -o $@ $(OBJ_OTOOL) $(LIBFT) $(I_PRINTF)
		@echo "\033[37mNM: \033[35mOK\n"
		@echo "\033[32m==> SUCCESS !\033[0m\n"

obj/%.o: %.c
	@$(CC) $(WFLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

obj:
	@mkdir -p obj/nm
	@mkdir -p obj/otool

res:
	@mkdir -p res/
	@cat /usr/include/mach-o/loader.h > res/loader.h
	@cat /usr/include/mach-o/nlist.h > res/nlist.h
	@cat /usr/include/mach-o/fat.h > res/fat.h
	@cat /usr/include/ar.h > res/ar.h
	@cat /usr/include/mach-o/ranlib.h > res/ranlib.h

clean:
	@echo "\n"----------------------- NM CLEAN ---------------------------
	@echo "\n\033[35m==> CLEANING in progress ...\033[0m\n"
	@rm -rf $(OBJ_NM) $(NAME_NM)

fclean: clean
	@make fclean -C libft
	@echo "\033[35m==> CLEANING test files ...\033[0m\n"
	@rm -rf ./obj
	@echo ---------------------------- END -------------------------------"\n"

re: fclean all

norminette:
	@echo "\n"----------------------- NORMINETTE LIBFT --------------------------"\n"
	@norminette libft/lib/*.c libft/ft_printf/src/*.c libft/ft_printf/lib/*.c libft/inc/*.h
	@echo "\n"----------------------- NORMINETTE NM -------------------------"\n"
	@norminette src/*.c inc/nm_otool.h
	@echo "\n"--------------------------- END -----------------------------------"\n"

.PHONY: re fclean clean all norminette
