#include "rtv1.h"

t_vec	lambert(t_obj *obj, t_vec *nor, t_vec *pos)
{
	t_vec	lambert;
	t_vec	light;
	double	value;
	double	dist;

	dist = vecdistance(pos, &obj->pos);
	dist = ft_clamp(sqrt(GAMMA / (dist * (1.0 - obj->power))), 0.0, 1.0);
	light = vecsub(&obj->pos, pos);
	vecnorm(&light);
	value = ft_clamp(vecdot(nor, &light), 0.0, 1.0);
	if (nor->x == 0.0 && nor->y == 1.0 && nor->z == 0.0)
		value = 1.0;
	lambert = vecopx(&obj->color, value);
	lambert = vecopx(&lambert, obj->power);
	lambert = vecopx(&lambert, dist);
	return (lambert);
}

double	phong(t_obj *obj, t_vec *nor, t_vec *rd, t_vec *pos)
{
	double	phong;
	t_vec	ref;
	t_vec	light;

	light = vecsub(&obj->pos, pos);
	vecnorm(&light);
	ref = vecreflect(rd, nor);
	vecnorm(&ref);
	phong = ft_clamp(pow(ft_clamp(vecdot(&ref, &light), \
					0.0, 1.0), 50.0), 0.0, 1.0);
	phong *= pow(obj->power, 0.5);
	return (phong);
}
