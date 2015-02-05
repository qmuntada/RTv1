#include "rtv1.h"

t_vec	vecadd(t_vec *a, t_vec *b)
{
	t_vec	v;

	v.x = a->x + b->x;
	v.y = a->y + b->y;
	v.z = a->z + b->z;
	return (v);
}

t_vec	vecprod(t_vec *a, t_vec *b)
{
	t_vec	v;

	v.x = a->x * b->x;
	v.y = a->y * b->y;
	v.z = a->z * b->z;
	return (v);
}

t_vec	vecopx(t_vec *a, double x)
{
	t_vec v;

	v.x = a->x * x;
	v.y = a->y * x;
	v.z = a->z * x;
	return (v);
}
