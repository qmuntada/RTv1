#include "rtv1.h"

double	isphere(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;

	oc = vecsub(ro, &obj->pos);
	a = vecdot(rd, rd);
	b = vecdot(&oc, rd);
	c = vecdot(&oc, &oc) - obj->size * obj->size;
	h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}

double	iplane(t_obj *obj, t_vec *ro, t_vec *rd)
{
	double	t;

	t = -((vecdot(&obj->rot, ro) - vecdot(&obj->rot, &obj->pos))\
		/ vecdot(&obj->rot, rd));
	if (t < 0.0001)
		return (-1.0);
	return (t);
}

double	icylinder(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;

	oc = vecsub(ro, &obj->pos);
	a = rd->x * rd->x + rd->z * rd->z;
	b = (rd->x * oc.x + rd->z * oc.z);
	c = oc.x * oc.x + oc.z * oc.z - obj->size * obj->size;
	h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}

double	icone(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;

	oc = vecsub(ro, &obj->pos);
	a = rd->x * rd->x - rd->y * rd->y + rd->z * rd->z;
	b = rd->x * oc.x - rd->y * oc.y + rd->z * oc.z;
	c = oc.x * oc.x + oc.z * oc.z - oc.y * oc.y;
	h = b * b - a * c;
	if (h < 0.0001)
		return (-1.0);
	return ((-b - sqrt(h)) / a);
}
