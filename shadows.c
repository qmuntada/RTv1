#include "rtv1.h"

int		ssphere(t_obj *obj, t_vec *ro, t_vec *rd, double tmin)
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
	if (h > 0.0001)
	{
		h = (-b - sqrt(h)) / a;
		return ((h > 0.001) && (h < tmin));
	}
	return (0);
}

int		splane(t_obj *obj, t_vec *ro, t_vec *rd, double tmin)
{
	double	t;

	t = -((vecdot(&obj->rot, ro) - vecdot(&obj->rot, &obj->pos))\
		/ vecdot(&obj->rot, rd));
	if (t < 0.0001)
		return (-1.0);
	return (t);
}

int		scylinder(t_obj *obj, t_vec *ro, t_vec *rd, double tmin)
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
	if (h > 0.0001)
	{
		h = (-b - sqrt(h)) / a;
		return ((h > 0.001) && (h < tmin));
	}
	return (0);
}

int		scone(t_obj *obj, t_vec *ro, t_vec *rd, double tmin)
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
	if (h > 0.0001)
	{
		h = (-b - sqrt(h)) / a;
		return ((h > 0.001) && (h < tmin));
	}
	return (0);
}

double	inter_shadows(t_env *e, t_vec *pos, t_vec *lpos)
{
	t_obj	*lobj;
	int		tmp;
	int		sha;
	t_vec	light;
	double	l;

	lobj = e->obj;
	tmp = 0;
	sha = 0;
	light = vecsub(lpos, pos);
	l = veclength(&light);
	light = vecopdiv(&light, l);
	while (lobj)
	{
		if (lobj->type == 1)
			tmp = ssphere(lobj, pos, &light, l);
		else if (lobj->type == 2)
			tmp = scylinder(lobj, pos, &light, l);
		else if (lobj->type == 3)
			tmp = scone(lobj, pos, &light, l);
		sha = (tmp == 1 ? 1 : sha);
		lobj = lobj->next;
	}
	return (sha);
}
