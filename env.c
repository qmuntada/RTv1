#include "rtv1.h"

void	init_env_postparsing(t_env *e)
{
	e->win = mlx_new_window(e->mlx, e->screen.width, e->screen.height, e->screen_name);
	e->screen.img_ptr = mlx_new_image(e->mlx, e->screen.width, e->screen.height);
	e->screen.img = (unsigned char*)mlx_get_data_addr(e->screen.img_ptr, \
				&e->screen.bpp, &e->screen.sl, &e->screen.endian);
	e->ln = 1.0 / e->ln;
}

void	init_env_preparsing(t_env *e)
{
	e->mlx = mlx_init();
	e->cam_pos = (t_vec){0, 0, 0};
	e->cam_dir = (t_vec){0, 0, 0};
	e->obj = NULL;
	e->objs = NULL;
	e->ln = 0;
	e->screen_name = "RTv1@42";
	e->screen.width = 1000;
	e->screen.height = 1000;
}
