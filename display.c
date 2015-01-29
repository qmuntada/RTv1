#include "rtv1.h"

double	isphere(t_obj *obj, t_vec *ro, t_vec *rd)
{
	t_vec	oc;

	oc = vecsub(ro, &obj->pos);
	double b = vecdot(&oc, rd);
	double c = vecdot(&oc, &oc) - obj->size1 * obj->size1;
	double h = b * b - c;
	if (h < 0.0)
		return (-1.0);
	return (-b - sqrt(h));
}

double iplane(t_obj *obj, t_vec *ro, t_vec *rd)
{
	return (((-1.0) - ro->y) / rd->y);
}

t_vec	ray_tracing(t_env *e, double x, double y)
{
	double	u;
	double	v;

	u = (e->screen.width - x * 2.0) / e->screen.height;
	v = (e->screen.height - y * 2.0) / e->screen.height;

	t_vec	light;
	t_vec	rd;
	t_vec	ro;

	setvec(&light, 0.7, 0.4, 0.3);
	vecnorm(&light);
	setvec(&ro, 0.0, 0.0, 4.0);
	setvec(&rd, u, v, -2.0);
	vecnorm(&rd);
	t_vec col;
	setvec(&col, 0.1, 0.1, 0.3); // couleur de base
	double tmin = 100000.0;
	double tmp = tmin;
	t_vec	pos;
	t_vec	nor;
	t_obj	*obj;
	t_obj	*objtmp;

	obj = e->obj;
	objtmp = obj;
	// recherche de l'objet le plus proche
	while (obj)
	{
		if (obj->type == 1) // seul les sphere sont supporte pour l'instant
			tmp = isphere(obj, &ro, &rd);
		if (tmp > 0.0 && tmp < tmin)
		{
			objtmp  = obj;
			tmin = tmp;
		}
		obj = obj->next;
	}
	if (tmin > 0.0) // objet trouve (donc pas de vide)
	{
		setvec(&pos, ro.x + tmin * rd.x, ro.y + tmin * rd.y, ro.z + tmin * rd.z);
		nor = vecsub(&pos, &objtmp->pos);
		vecnorm(&nor); // normale (ombre)
		obj = e->obj;
		tmp = -1.0;
		double shadows = 1.0;
		obj = e->obj;
		while (obj)
		{
			tmp = isphere(obj, &pos, &light);
			if (tmp > 0.0)
				shadows = 0;
			obj = obj->next;
		}
		if (tmin < 1000.0)
		{
			setvec(&col, objtmp->color.x, objtmp->color.y, objtmp->color.z);
			double lig;
			lig = vecdot(&nor, &light);//LUMIERE DE LAMBERT
			lig = (lig > 1.0 ? 1.0 : lig);//clamp
			lig = (lig < 0.0 ? 0.0 : lig);//clamp
			col = vecopx(&col, lig);
			col = vecopx(&col, shadows);
			col = vecopx(&col, exp(-0.05 * tmin));//fog
		}
	}
	return (col);
}

void	display(t_env *e)
{
	int		x;
	int		y;
	t_vec	col;
	t_vec	col2;

	y = -1;
	while (++y < e->screen.height)
	{
		x = -1;
		while (++x < e->screen.width)
		{
			col = ray_tracing(e, x, y);
			if (1) // ANTI ALIASING
			{
				col2 = ray_tracing(e, x, y + 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x + 0.5, y);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x + 0.5, y + 0.5);
				col = vecadd(&col, &col2);
				col.x /= 4.0;
				col.y /= 4.0;
				col.z /= 4.0;
			}
			col = vecopx(&col, 0.2 + 0.8 * pow(16.0 * (double)x / e->screen.width * (double)y / e->screen.height * (1.0 - (double)x / e->screen.width ) * (1.0 - (double)y / e->screen.height ), 0.25)); // VIGNETTE
			pixel_put(e, x, y, &col);
		}
	}
}
