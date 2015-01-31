#include "rtv1.h"

double	phong(t_vec *light, t_vec *nor, t_vec *rd)
{
	double	phong;
	t_vec	ref;

	phong = ft_clamp(vecdot(nor, light), 0.0, 1.0);
	ref = vecreflect(rd, nor);
	vecnorm(&ref);
	phong = ft_clamp(phong + phong *\
		pow(ft_clamp(vecdot(&ref, light), 0.0, 1.0), 50.0), 0.0, 1.0);
	return (phong);
}

t_vec	setnor(t_obj *obj, t_vec *pos)
{
	t_vec	nor;

	setvec(&nor, 0.0, 1.0, 0.0);
	if (obj->type == 0)
		setvec(&nor, 0.0, 1.0, 0.0);
	else if (obj->type == 1)
		nor = vecsub(pos, &obj->pos);
	else if (obj->type == 2)
		setvec(&nor, pos->x - obj->pos.x, 0.0, pos->z - obj->pos.z);
	else if (obj->type == 3)
		setvec(&nor, pos->x - obj->pos.x, -(pos->y - obj->pos.y), pos->z - obj->pos.z);
	vecnorm(&nor);
	return (nor);

}

t_vec	ray_tracing(t_env *e, double x, double y)
{
	t_vec col;

	col = (t_vec){0.9, 0.9, 0.9};
	double tmin = 100000.0;
	double tmp = tmin;
	t_vec	pos;
	t_vec	nor;
	t_obj	*obj;
	t_obj	*objtmp;
	t_vec	light;
	setvec(&light, 10.0, 2.0, 2.0);
	vecnorm(&light);

	obj = e->obj;
	objtmp = obj;
	while (obj)
	{
		if (obj->type == 0)
			tmp = iplane(obj, &e->ro, &e->rd);
		else if (obj->type == 1)
			tmp = isphere(obj, &e->ro, &e->rd);
		else if (obj->type == 2)
			tmp = icylinder(obj, &e->ro, &e->rd);
		else if (obj->type == 3)
			tmp = icone(obj, &e->ro, &e->rd);
		if (tmp > 0.0001 && tmp < tmin)
		{
			objtmp  = obj;
			tmin = tmp;
		}
		obj = obj->next;
	}
	if (tmin > 0.0001)
	{
		setvec(&pos, e->ro.x + tmin * e->rd.x, e->ro.y + tmin * e->rd.y, e->ro.z + tmin * e->rd.z);
		obj = e->obj;
		tmp = -1.0;
		int shab = 0;
		double sha = 1.0;
		t_obj	*obj2;
		while (obj)
		{
			if (obj->type == 4)
			{
				obj2 = e->obj;
				shab = 0;
				while (obj2)
				{
						if (obj2->type == 0)
							tmp = iplane(obj2, &pos, &obj->pos);
						else if (obj2->type == 1)
							tmp = isphere(obj2, &pos, &obj->pos);
						else if (obj2->type == 2)
							tmp = icylinder(obj2, &pos, &obj->pos);
						else if (obj2->type == 3)
							tmp = icone(obj2, &pos, &obj->pos);
						if (tmp > -0.0001)
							shab = 1;
					obj2 = obj2->next;
				}
				if (shab == 1)
					sha -= e->ln; // car deux lumieres  1 / nl
			}
			obj = obj->next;
		}
		if (tmin < 1000.0)
		{
			setvec(&col, objtmp->color.x, objtmp->color.y, objtmp->color.z);
			nor = setnor(objtmp, &pos);
			obj = e->obj;
			double lig = 0.0;
			while (obj)
			{
				if (obj->type == 4)
				{
					lig += phong(&obj->pos, &nor, &e->rd) * e->ln;
				}
				obj = obj->next;
			}
			lig *= sha;
			lig = ft_clamp(lig, 0.0, 1.0);
			col = vecopx(&col, lig);
			//FOG
			col.x = ft_mix(col.x, 0.9, 1.0 - exp(-0.02 * tmin));
			col.y = ft_mix(col.y, 0.9, 1.0 - exp(-0.02 * tmin));
			col.z = ft_mix(col.z, 0.9, 1.0 - exp(-0.02 * tmin));
		}
	}
	return (col);
}

void	set_cam(t_env *e, double x, double y)
{
	double	u;
	double	v;
	t_vec	ww;
	t_vec	uu;
	t_vec	vv;

	u = (e->screen.width - x * 2.0) / e->screen.height;
	v = (e->screen.height - y * 2.0) / e->screen.height;
	setvec(&e->ro, 5.0 * cos(e->cam_dir.x), \
		e->cam_dir.y, 5.0 * sin(e->cam_dir.x));
	ww = vecsub(&(t_vec){0.0, 1.0, 0.0}, &e->ro);
	vecnorm(&ww);
	uu = veccross(&ww, &(t_vec){0.0, 1.0, 0.0});
	vecnorm(&uu);
	vv = veccross(&uu, &ww);
	setvec(&e->rd, u * uu.x + v * vv.x + 1.5 * ww.x, \
		u * uu.y + v * vv.y + 1.5 * ww.y , u * uu.z + v * vv.z + 1.5 * ww.z);
	vecnorm(&e->rd);
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
			set_cam(e, x, y);
			col = ray_tracing(e, x, y);
			// POST EFFECT
			if (0)
			{
				// ANTI ALIASING
				col2 = ray_tracing(e, x, y + 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x + 0.5, y);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x + 0.5, y + 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x, y - 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x - 0.5, y);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x - 0.5, y - 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x + 0.5, y - 0.5);
				col = vecadd(&col, &col2);
				col2 = ray_tracing(e, x - 0.5, y + 0.5);
				col = vecadd(&col, &col2);
				col = vecopx(&col, 0.112);
				//VIGNETTE
				col = vecopx(&col, 0.2 + 0.8 * pow(16.0 * (double)x / \
					e->screen.width * (double)y / e->screen.height * (1.0 - \
					(double)x / e->screen.width ) * (1.0 - (double)y / \
					e->screen.height ), 0.15));
			}
			vecclamp(&col, 0.0, 1.0);
			pixel_put(e, x, y, &col);
		}
	}
}
