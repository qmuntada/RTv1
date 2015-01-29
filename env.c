#include "rtv1.h"

void	init_env_postparsing(t_env *e)
{
	e->win = mlx_new_window(e->mlx, e->screen.width, e->screen.height, e->screen_name);
	e->screen.img_ptr = mlx_new_image(e->mlx, e->screen.width, e->screen.height);
	e->screen.img = (unsigned char*)mlx_get_data_addr(e->screen.img_ptr, \
				&e->screen.bpp, &e->screen.sl, &e->screen.endian);
}

void	init_env_preparsing(t_env *e)
{
	e->mlx = mlx_init();
	setvec(&e->cam_pos, 0, 0, 0);
	setvec(&e->cam_dir, 0, 0, 0);
	e->obj = NULL;
	e->screen_name = "RTv1@42";
	e->screen.width = 1000;
	e->screen.height = 1000;
}
