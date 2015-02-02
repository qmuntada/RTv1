
#include "rtv1.h"

double	sssphere(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;
	double	d;
	double	t;

	oc = vecsub(&obj->pos, ro);
	a = vecdot(rd, rd);
	b = vecdot(&oc, rd);
	c = vecdot(&oc, &oc) - obj->size * obj->size;
	h = a * c - b * b;
	d = obj->size * obj->size - h;
	d = (d < 0 ? 0 : d);
	d = sqrt(d) - obj->size;
	h = (h < 0 ? 0 : h);
	t = b - sqrt(h);
	return (t < 0.0001 ? 1.0 : ft_smoothstep(0.0, 1.0, SMOOTH_SHADOWS * d / t));
}

double	ssplane(t_obj *obj, t_vec *ro, t_vec *rd)
{
	double	t;

	t = -((vecdot(&obj->rot, ro) - vecdot(&obj->rot, &obj->pos))\
		/ vecdot(&obj->rot, rd));
	if (t < 0.0001)
		return (1.0);
	return (0.0);
}

double	sscylinder(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;

	oc = vecsub(&obj->pos, ro);
	a = rd->x * rd->x + rd->z * rd->z;
	b = (rd->x * oc.x + rd->z * oc.z);
	c = oc.x * oc.x + oc.z * oc.z - obj->size * obj->size;
	h = a * c - b * b;
	return (b < 0.0001 ? 1.0 : ft_clamp(SMOOTH_SHADOWS * h / b, 0.0, 1.0));
}

double	sscone(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	h;

	oc = vecsub(&obj->pos, ro);
	a = rd->x * rd->x - rd->y * rd->y + rd->z * rd->z;
	b = rd->x * oc.x - rd->y * oc.y + rd->z * oc.z;
	c = oc.x * oc.x + oc.z * oc.z - oc.y * oc.y;
	h = a * c - b * b;
	return (b < 0.0001 ? 1.0 : ft_clamp(SMOOTH_SHADOWS * h / b, 0.0, 1.0));
}

double	soft_shadows(t_env *e, t_vec *ro, t_vec *rd)
{
	t_obj	*obj;
	double	tmp;
	double	sha;

	obj = e->obj;
	sha = 1.0;
	while (obj)
	{
		tmp = 1.0;
		if (obj->type == 0)
			tmp *= ssplane(obj, ro, rd);
		else if (obj->type == 1)
			tmp *= sssphere(obj, ro, rd);
		else if (obj->type == 2)
			tmp *= sscylinder(obj, ro, rd);
		else if (obj->type == 3)
			tmp *= sscone(obj, ro, rd);
		if (tmp < sha)
			sha = tmp;
		obj = obj->next;
	}
	return (1.0 - sha);
}
