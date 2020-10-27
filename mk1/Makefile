SRC	=	add_obj.c\
		cam_calc.c\
		dist.c\
		init.c\
		input.c\
		misc.c\
		raymarching.c\
		test_func.c\
		dist/bx.c\
		dist/cy.c\
		dist/pl.c\
		dist/sp.c\
		dist/sq.c\
		dist/tr.c\

FLAGS =	-Wall -Werror -Wextra

all:
	gcc -c $(SRC)
	mv *.o comp

clean:
	rm -rf comp/*.o

fclean: clean
	rm -rf test

re: fclean all

test: all
	gcc $(FLAGS) main.c comp/*.o ../minilibx-linux-master/*.a -L.. -lmlx -lXext -lX11 -lm -lbsd -o test && ./test

.PHONY: all clean fclean re test
