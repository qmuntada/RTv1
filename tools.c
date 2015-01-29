#include "rtv1.h"

void	pixel_put(t_env *e, int x, int y, t_vec *color)
{
	int		pos;

	//if (color->x > 0.0 && color->x == color->y && color->y == color->z)
	//	printf("c'est bon\n");
	pos = (x * e->screen.bpp / 8) + (y * e->screen.sl);
	e->screen.img[pos] = (int)(color->z * 256.0) % 256;
	e->screen.img[pos + 1] = (int)(color->y * 256.0) % 256;
	e->screen.img[pos + 2] = (int)(color->x * 256.0) % 256;
}
