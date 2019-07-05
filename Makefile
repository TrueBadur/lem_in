NAME_PS = lem_in
SRC_PUSHSWAP = $(wildcard *.c)
OBJ_PUSHSWAP=$(SRC_PUSHSWAP:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB := ./libft/lib/libft.a
LIBDIR = libft/
LIBSPATH = -I libft/includes/ -I /usr/local/include/ -I ./
HDR := ./lem_in.h
VIZ =
HID =
LINK = -lmlx -framework OpenGL -framework AppKit -L /usr/local/lib/

viz: VIZ = -D VIZUALIZER
viz: re

hidden: HID = -D HIDDEN
hidden: re

viz_hid: VIZ = -D VIZUALIZER
viz_hid: HID = -D HIDDEN
viz_hid: re

%.o: %.c $(HDR) $(LIB)
	$(CC) $(CFLAGS) $(VIZ) $(HID) $(LIBSPATH) -c $< -o $@

all: lib $(NAME_CH) $(NAME_PS)

$(NAME_PS): $(OBJ_COMMON) $(OBJ_PUSHSWAP) $(OBJ_HIDDEN)
	$(CC) $(CFLAGS) $(LIBSPATH) $(HID) -o $(NAME_PS) $(LINK) $(LIB) $(OBJ_COMMON) $(OBJ_PUSHSWAP) $(OBJ_HIDDEN)

$(NAME_CH): $(OBJ_COMMON) $(OBJ_CHECKER) $(OBJ_HIDDEN)
	$(CC) $(CFLAGS) $(LIBSPATH) $(HID) $(VIZ) -o $(NAME_CH) $(LINK) $(LIB) $(OBJ_COMMON) $(OBJ_CHECKER) $(OBJ_HIDDEN)

lib:
	make -C $(LIBDIR)

fclean: clean cleanlib
	/bin/rm -f $(NAME)

clean:
	@/bin/rm -f $(OBJ_COMMON) $(OBJ_PUSHSWAP) $(OBJ_CHECKER)

cleanlib:
	make -C $(LIBDIR) clean

re: fclean all

clean_all: cleanlib clean

fclean_all: clean_all
	/bin/rm -f $(NAME)
	make -C $(LIBDIR) fclean

re_all: fclean_all all

