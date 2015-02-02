#include "rtv1.h"

void	set_cam(t_env *e, double x, double y)
{
	double	u;
	double	v;
	t_vec	ww;
	t_vec	uu;
	t_vec	vv;

	u = (e->screen.width - x * 2.0) / e->screen.height;
	v = (e->screen.height - y * 2.0) / e->screen.height;
	e->ro = (t_vec){e->cam_pos.x * cos(e->cam_dir.x), e->cam_dir.y, \
		e->cam_pos.x * sin(e->cam_dir.x)};
	ww = vecsub(&(t_vec){0.0, 1.0, 0.0}, &e->ro);
	vecnorm(&ww);
	uu = veccross(&ww, &(t_vec){0.0, 1.0, 0.0});
	vecnorm(&uu);
	vv = veccross(&uu, &ww);
	e->rd = (t_vec){u * uu.x + v * vv.x + 1.5 * ww.x, u * uu.y + v * \
		vv.y + 1.5 * ww.y , u * uu.z + v * vv.z + 1.5 * ww.z};
	vecnorm(&e->rd);
	e->objs = NULL;
}

t_obj	*inter_object(t_env *e, t_vec *ro, t_vec *rd, double *dmin)
{
	t_obj	*lobj;
	t_obj	*obj;
	double	tmp;

	obj = NULL;
	lobj = e->obj;
	tmp = *dmin;
	while (lobj)
	{
		if (lobj->type == 0)
			tmp = iplane(lobj, ro, rd);
		else if (lobj->type == 1)
			tmp = isphere(lobj, ro, rd);
		else if (lobj->type == 2)
			tmp = icylinder(lobj, ro, rd);
		else if (lobj->type == 3)
			tmp = icone(lobj, ro, rd);
		if (tmp > 0.0001 && tmp < *dmin)
		{
			obj = lobj;
			*dmin = tmp;
		}
		lobj = lobj->next;
	}
	return (obj);
}

double	get_shadows(t_env *e, t_vec *pos)
{
	t_obj	*obj;
	double	sha;
	double	tmp;

	obj = e->obj;
	sha = 1.0;
	while (obj)
	{
		if (obj->type == 4)
		{
			tmp = 10000.0;
			inter_object(e, pos, &obj->pos, &tmp);
			if (tmp < 10000.0)
				sha -= e->ln;
			//tmp = soft_shadows(e, pos, &obj->pos);
			//sha -= tmp * e->ln;
		}
		obj = obj->next;
	}
	return (sha);
}

void	get_lighting(t_env *e, t_vec *col, t_vec *pos, t_vec *nor)
{
	double	sha;
	double	spe;
	t_vec	lig;
	t_obj	*obj;
	t_vec	lig_tmp;

	lig = (t_vec){0.0, 0.0, 0.0};
	spe = 0.0;
	sha = get_shadows(e, pos);
	obj = e->obj;
	while (obj)
	{
		if (obj->type == 4)
		{
			lig_tmp = lambert(&obj->pos, nor, &obj->color);
			//lig_tmp = vecopx(&lig_tmp, e->ln);
			lig = vecadd(&lig, &lig_tmp);
			spe += phong(&obj->pos, nor, &e->rd) * e->ln;
		}
		obj = obj->next;
	}
	spe *= sha;
	*col = vecopplus(col, spe);
	lig = vecopx(&lig, sha);
	*col = vecprod(col, &lig);
	vecclamp(col, 0.0, 1.0);
}

t_vec	object_color(t_env *e, t_vec *ro, t_vec *rd)
{
	t_vec	color;
	t_vec	pos;
	t_vec	nor;

	e->tmin = 10000.0;
	e->objs = inter_object(e, &e->ro, &e->rd, &e->tmin);
	color = (t_vec){0.0, 0.0, 0.0};
	if (e->tmin > 0.0001 && e->objs)
	{
		color = (t_vec){e->objs->color.x, e->objs->color.y, e->objs->color.z};
		// color *= e->objs->ref * e->objs->tra;
		if (e->tmin < 10000.0)
		{
			pos = (t_vec){e->ro.x + e->tmin * e->rd.x, e->ro.y + e->tmin * \
				e->rd.y, e->ro.z + e->tmin * e->rd.z};
			nor = setnor(e->objs, &pos);
			get_lighting(e, &color, &pos, &nor);
		}
	}
	color.x = ft_mix(color.x, 0.0, 1.0 - exp(-0.02 * e->tmin));
	color.y = ft_mix(color.y, 0.0, 1.0 - exp(-0.02 * e->tmin));
	color.z = ft_mix(color.z, 0.0, 1.0 - exp(-0.02 * e->tmin));
	/*
	while (e->objs && e->ref++ < 16 && e->objs->ref < 1.0)
		col += vecadd(&col, object_color(e, &e->objs->pos, refdir));
	while (e->objs && e->objs->tra < 1.0)
		col += vecadd(&col, object_color(e, &e->objs->pos, &e->rd));
	*/
	return (color);
}

t_vec	ray_tracing(t_env *e, double x, double y)
{
	t_vec	col;

	set_cam(e, x, y);
	col = object_color(e, &e->ro, &e->rd);
	return (col);
}

void	display(t_env *e)
{
	int		x;
	int		y;
	t_vec	coltmp;

	y = -1;
	while (++y < e->screen.height)
	{
		x = -1;
		while (++x < e->screen.width)
		{
			e->col = ray_tracing(e, x, y);
			// POST EFFECT
			if (0)
			{
				// ANTI ALIASING 4X
				coltmp = ray_tracing(e, x, y + 0.5);
				e->col = vecadd(&e->col, &coltmp);
				coltmp = ray_tracing(e, x + 0.5, y);
				e->col = vecadd(&e->col, &coltmp);
				coltmp = ray_tracing(e, x, y - 0.5);
				e->col = vecadd(&e->col, &coltmp);
				coltmp = ray_tracing(e, x - 0.5, y);
				e->col = vecadd(&e->col, &coltmp);
				e->col = vecopx(&e->col, 0.2);
				//VIGNETTE
				e->col = vecopx(&e->col, 0.2 + 0.8 * pow(16.0 * (double)x / \
					e->screen.width * (double)y / e->screen.height * (1.0 - \
					(double)x / e->screen.width ) * (1.0 - (double)y / \
					e->screen.height ), 0.15));
			}
			vecclamp(&e->col, 0.0, 1.0);
			pixel_put(e, x, y);
		}
	}
}
