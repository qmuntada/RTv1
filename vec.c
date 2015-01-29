#include "rtv1.h"

double	veclength(t_vec *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

void	vecnorm(t_vec *vec)
{
	double	n;

	n = 1.0 / sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	vec->x *= n;
	vec->y *= n;
	vec->z *= n;
}

double	vecdot(t_vec *a, t_vec *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_vec	veccross(t_vec *a, t_vec *b)
{
	t_vec v;

	v.x = a->y * b->z - a->z * b->y;
	v.y = a->z * b->x - a->x * b->z;
	v.z = a->x * b->y - a->y * b->x;
	return (v);
}

t_vec	vecsub(t_vec *a, t_vec *b)
{
	t_vec	v;

	v.x = a->x - b->x;
	v.y = a->y - b->y;
	v.z = a->z - b->z;
	return (v);
}

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

t_vec	vecdiv(t_vec *a, t_vec *b)
{
	t_vec	v;

	v.x = a->x / b->x;
	v.y = a->y / b->y;
	v.z = a->z / b->z;
	return (v);
}

void	setvec(t_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
