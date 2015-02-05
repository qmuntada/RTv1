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
	ww = vecsub(&e->cam_dir, &e->cam_pos);
	vecnorm(&ww);
	uu = veccross(&ww, &(t_vec){0.0, 1.0, 0.0});
	vecnorm(&uu);
	vv = veccross(&uu, &ww);
	e->rd = (t_vec){u * uu.x + v * vv.x + FOV * ww.x, u * uu.y + v * \
		vv.y + FOV * ww.y, u * uu.z + v * vv.z + FOV * ww.z};
	vecnorm(&e->rd);
	e->ro = e->cam_pos;
	e->objs = NULL;
}

t_vec	object_color(t_env *e, t_vec *ro, t_vec *rd)
{
	t_vec	color;
	t_vec	pos;
	t_vec	nor;

	e->tmin = 10000.0;
	e->objs = inter_object(e, ro, rd, &e->tmin);
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
	return (color);
}

t_vec	ray_tracing(t_env *e, double x, double y)
{
	t_vec	col;
	t_vec	ro;
	t_vec	rd;

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
