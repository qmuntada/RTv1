
#include "rtv1.h"

t_vec	setnor(t_obj *obj, t_vec *pos)
{
	t_vec	nor;

	nor = (t_vec){0.0, 1.0, 0.0};
	if (obj->type == 0)
		nor = (t_vec){obj->rot.x, obj->rot.y, obj->rot.z};
	else if (obj->type == 1)
		nor = vecsub(pos, &obj->pos);
	else if (obj->type == 2)
		nor = (t_vec){pos->x - obj->pos.x, 0.0, pos->z - obj->pos.z};
	else if (obj->type == 3)
		nor = (t_vec){pos->x - obj->pos.x, -(pos->y - obj->pos.y), \
			pos->z - obj->pos.z};
	vecnorm(&nor);
	return (nor);
}

t_vec	lambert(t_vec *light, t_vec *nor, t_vec *col)
{
	t_vec	lambert;

	lambert = vecopx(col, vecdot(nor, light));
	vecclamp(&lambert, 0.0, 1.0);
	return (lambert);
}

double	phong(t_vec *light, t_vec *nor, t_vec *rd)
{
	double	phong;
	t_vec	ref;

	ref = vecreflect(rd, nor);
	vecnorm(&ref);
	phong = ft_clamp(pow(ft_clamp(vecdot(&ref, light), 0.0, 1.0), 200.0), 0.0, 1.0);
	return (phong);
}
