//
// Created by Ebrose Hugh beesbury on 2019-07-12.
//

#ifndef MLX_HELPER_H
#define MLX_HELPER_H

#include "time.h"

typedef struct	s_mlx
{
	void		*mlx;
	void		*win_ptr;
	clock_t		interval;
	char		pause;
	clock_t		sleep;
	char 		active;
}				t_mlx;

#ifndef MLX_KEY_LAYOUT
#define MLX_KEY_LAYOUT

enum			e_keys
{
	SPEED_INCREASE = 2,
	SPEED_DECREASE = 0,
	STEP_FORWARD = 36,
	PAUSE = 49,
	ACTIVE = 1,
	QUIT = 53
};

#endif

typedef struct	s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_uint2		res;
	int			pos;
}				t_img;

t_mlx	*ft_mlx_init(char *main_wndw_name);

#endif
