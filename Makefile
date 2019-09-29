NAME_LEMIN = lem-in
SRC_LEMIN = $(wildcard *.c)
OBJ_LEMIN = $(addprefix $(OBJ_PATH), $(SRC_LEMIN:.c=.o))
OBJ_PATH = obj/
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB := ./libft/lib/libft.a
LIBDIR = libft/
LIBSPATH = -I libft/includes/ -I /usr/local/include/ -I ./
HDR := ./lem_in.h
CFLAGS = #-Wall -Wextra -Werror

$(OBJ_PATH)%.o: %.c $(HDR) $(LIB)
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

