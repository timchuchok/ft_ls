NAME = ft_ls

GCC = gcc -c -Wall -Wextra -Werror

SRC =	main.c \
		parse.c \
		print.c \
		print_std.c \
		sort_list.c \
		print_permissions_link.c \
		read_args_dir.c \
		print_def.c

OBJ = $(SRC:.c=.o)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
DEL_COLOR=\033[31;01m

all: $(NAME)

$(NAME): $(OBJ) libft_ ft_printf_
	@gcc -o $(NAME) $(OBJ) libft/libft.a ft_printf/libftprintf.a
	@echo $(NAME) "$(OK_COLOR)[COMPILED] $(NO_COLOR)"

%.o : %.c $(HEADER)
	@$(GCC) -o  $@ $<
	@echo $@ "$(OK_COLOR)[OK] $(NO_COLOR)"

libft_:
	@make -C libft

ft_printf_:
	@make -C ft_printf

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@make clean -C ft_printf
	@echo $(OBJ) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf
	@echo $(NAME) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

re: fclean all