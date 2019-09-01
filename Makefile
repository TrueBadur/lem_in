NAME_LEMIN = lem_in
SRC_LEMIN = $(wildcard *.c)
OBJ_LEMIN =$(SRC_LEMIN:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB := ./libft/lib/libft.a
LIBDIR = libft/
LIBSPATH = -I libft/includes/ -I /usr/local/include/ -I ./
HDR := ./lem_in.h
VIZ =
HID =
LINK =
CFLAGS =

viz: VIZ = -D VIZUALIZER
viz: LINK = -lmlx -framework OpenGL -framework AppKit -L /usr/local/lib/
viz: re

%.o: %.c $(HDR) $(LIB)
	$(CC) $(CFLAGS) $(VIZ) $(HID) $(LIBSPATH) -c $< -o $@

all: lib $(NAME_LEMIN)

$(NAME_LEMIN): $(OBJ_COMMON) $(OBJ_LEMIN)
	$(CC) $(CFLAGS) $(LIBSPATH) -o $(NAME_LEMIN) $(LINK) $(LIB) $(OBJ_LEMIN)


lib:
	make -C $(LIBDIR)

fclean: clean cleanlib
	/bin/rm -f $(NAME_LEMIN)

clean:
	@/bin/rm -f $(OBJ_LEMIN)

cleanlib:
	make -C $(LIBDIR) clean

re: fclean all

clean_all: cleanlib clean

fclean_all: clean_all
	/bin/rm -f $(NAME_LEMIN)
	make -C $(LIBDIR) fclean

re_all: fclean_all all

