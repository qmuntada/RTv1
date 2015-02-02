/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 19:30:55 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/02 19:37:52 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_cam(t_env *e, double x, double y)
{
	double	u;
	double	v;
	t_vec	ww;
	t_vec	uu;
	t_vec	vv;

	u = (e->screen_width - x * 2.0) / e->screen_height;
	v = (e->screen_height - y * 2.0) / e->screen_height;
	e->ro = (t_vec){e->cam_pos.x * cos(e->cam_dir.x), e->cam_dir.y, \
		e->cam_pos.x * sin(e->cam_dir.x)};
	ww = vecsub(&(t_vec){0.0, 1.0, 0.0}, &e->ro);
	vecnorm(&ww);
	uu = veccross(&ww, &(t_vec){0.0, 1.0, 0.0});
	vecnorm(&uu);
	vv = veccross(&uu, &ww);
	e->rd = (t_vec){u * uu.x + v * vv.x + 1.5 * ww.x, u * uu.y + v * \
		vv.y + 1.5 * ww.y, u * uu.z + v * vv.z + 1.5 * ww.z};
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
	while (++y < e->screen_height)
	{
		x = -1;
		while (++x < e->screen_width)
		{
			e->col = ray_tracing(e, x, y);
			vecclamp(&e->col, 0.0, 1.0);
			pixel_put(e, x, y);
		}
	}
}
