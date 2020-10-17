SRC	=	add_obj.c\
		cam_calc.c\
		init.c\
		input.c\
		misc.c\
		raymarching.c\
		test_func.c\

OBJ	=	add_obj.o\
		cam_calc.o\
		init.o\
		input.o\
		misc.o\
		raymarching.o\
		test_func.o\

FLAGS =	-Wall -Werror -Wextra

all:
	gcc -c $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf test

re: fclean all

test: all
	gcc main.c $(OBJ) ../minilibx-linux-master/*.a -L.. -lmlx -lXext -lX11 -lm -lbsd -o test && ./test

.PHONY: all clean fclean re test
