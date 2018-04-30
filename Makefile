NAME = ft_ssl

LIBNAME = libft/libft.a

FLG = -Wall -Wextra -Werror

SSLSRC = src/base64.c\
		 src/des.c\
		 src/des_util.c\
		 src/helper.c\
		 src/helper2.c\
		 src/init.c\
		 src/input.c\
		 src/main.c\
		 src/usage.c\
		 src/des3.c

SSLOBJ = $(SSLSRC:.c=.o)

all: liball $(NAME)

$(NAME): $(LIBNAME) $(SSLOBJ)
	gcc $(FLG) $^ -o $(NAME)

%.o: %.c
	gcc $(FLG) -c $< -o $@

clean: libclean
	rm -rf $(SSLOBJ)

fclean: libfclean clean
	rm -rf $(NAME)

re: fclean all

$(LIBNAME): liball

liball:
	@make -C libft/ all

libclean:
	@make -C libft/ clean

libfclean:
	@make -C libft/ fclean

libre:
	libfclean liball
