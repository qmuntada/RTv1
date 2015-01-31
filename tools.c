#include "rtv1.h"

void	pixel_put(t_env *e, int x, int y, t_vec *color)
{
	int		pos;

	pos = (x * e->screen.bpp / 8) + (y * e->screen.sl);
	e->screen.img[pos] = (int)(color->z * 256.0);
	e->screen.img[pos + 1] = (int)(color->y * 256.0);
	e->screen.img[pos + 2] = (int)(color->x * 256.0);
}
