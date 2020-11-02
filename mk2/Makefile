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
		obj/add_c.c\
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
		parse/settings.c\
		parse/def_ft.c\
		parse/def_obj.c\
		parse/def_sp.c\
		parse/def_pl.c\
		parse/def_cy.c\
		parse/def_sq.c\
		parse/def_tr.c\
		parse/def_bx.c\
		parse/elements.c\
		parser.c\
		save.c\

OBJ =	cam_calc.o\
		dist.o\
		init.o\
		input.o\
		raymarching.o\
		test_func.o\
		bx.o\
		cy.o\
		pl.o\
		sp.o\
		sq.o\
		tr.o\
		add_bx.o\
		add_cy.o\
		add_l.o\
		add_c.o\
		add_pl.o\
		add_sp.o\
		add_sq.o\
		add_tr.o\
		geo_op.o\
		mlx_comp.o\
		operators.o\
		rgb_hex.o\
		vectors_0.o\
		vectors_1.o\
		get_next_line_bonus.o\
		settings.o\
		def_ft.o\
		def_obj.o\
		def_sp.o\
		def_pl.o\
		def_cy.o\
		def_sq.o\
		def_tr.o\
		def_bx.o\
		elements.o\
		parser.o\
		save.o\

MLX =	../minilibx-linux-master/*.a

LFT =	libft/libft.a

CFLAGS =	-Wall -Werror -Wextra

LFLAGS =	-L.. -lmlx -lXext -lX11 -lm -lbsd

all:
	make -C libft
	gcc -c $(SRC)

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf test

re: fclean all

test: all
	gcc main_test.c $(OBJ) $(LFT) $(MLX) $(LFLAGS) -o test && ./test "../default.rt"

parser: all
	gcc main_parser.c $(OBJ) $(LFT) $(MLX) $(LFLAGS) -o parser && ./parser "../default.rt"

.PHONY: all clean fclean re test
