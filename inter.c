#include "rtv1.h"

double	isphere(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;

	oc = vecsub(ro, &obj->pos);
	double a = vecdot(rd, rd);
	double b = vecdot(&oc, rd);
	double c = vecdot(&oc, &oc) - obj->size * obj->size;
	double h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}

double	iplane(t_obj *obj, t_vec *ro, t_vec *rd)
{
	double t = -((vecdot(&obj->rot, ro) - vecdot(&obj->rot, &obj->pos))\
		/ vecdot(&obj->rot, rd));
	if (t < 0.0001)
		return (-1.0);
	return (t);
}

double	icylinder(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;

	oc = vecsub(ro, &obj->pos);
	double a = rd->x * rd->x + rd->z * rd->z;
	double b = (rd->x * oc.x + rd->z * oc.z);
	double c = oc.x * oc.x + oc.z * oc.z - obj->size * obj->size;
	double h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}

double	icone(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;

	oc = vecsub(ro, &obj->pos);
	double a = rd->x * rd->x - rd->y * rd->y + rd->z * rd->z;
	double b = rd->x * oc.x - rd->y * oc.y + rd->z * oc.z;
	double c = oc.x * oc.x + oc.z * oc.z - oc.y * oc.y;
	double h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}
