SRC	=	cam_calc.c\
		dist.c\
		init.c\
		input.c\
		raymarching.c\
		test_func.c\
		dist/bx.c\
		dist/cy.c\
		dist/pl.c\
		dist/sp.c\
		dist/sq.c\
		dist/tr.c\
		obj/add_bx.c\
		obj/add_cy.c\
		obj/add_l.c\
		obj/add_pl.c\
		obj/add_sp.c\
		obj/add_sq.c\
		obj/add_tr.c\
		misc/geo_op.c\
		misc/mlx_comp.c\
		misc/operators.c\
		misc/rgb_hex.c\
		misc/vectors_0.c\
		misc/vectors_1.c\
		gnl/get_next_line_bonus.c\
		gnl/get_next_line_utils_bonus.c\

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
