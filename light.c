/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 17:16:15 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/06 19:48:38 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	setnor(t_obj *obj, t_vec *pos)
{
	t_vec	nor;

	nor = (t_vec){0.0, 1.0, 0.0};
	if (obj->type == 1)
		nor = vecsub(pos, &obj->pos);
	else if (obj->type == 2)
		nor = (t_vec){pos->x - obj->pos.x, 0.0, pos->z - obj->pos.z};
	else if (obj->type == 3)
		nor = (t_vec){pos->x - obj->pos.x, 0.0, pos->z - obj->pos.z};
	vecnorm(&nor);
	return (nor);
}

t_vec	lambert(t_obj *obj, t_vec *nor, t_vec *pos)
{
	t_vec	lambert;
	t_vec	light;
	double	dist;
	double	value;
	double	sha;

	sha = 1.0;
	dist = sqrt((pos->x - obj->pos.x) * (pos->x - obj->pos.x) + \
		(pos->y - obj->pos.y) * (pos->y - obj->pos.y) + \
		(pos->z - obj->pos.z) * (pos->z - obj->pos.z));
	value = ft_clamp(sqrt(1.0 / (dist * (1.0 - obj->power))), 0.0, 0.9);
	if (nor->x == 0.0 && nor->y == 1.0 && nor->z == 0.0)
		lambert = vecopx(&obj->color, obj->power);
	else
	{
		light = vecsub(&obj->pos, pos);
		vecnorm(&light);
		sha = ft_clamp(vecdot(nor, &light), 0.0, 1.0);
		lambert = vecopx(&obj->color, sha);
		lambert = vecopx(&lambert, obj->power);
	}
	lambert = vecopx(&lambert, value);
	return (lambert);
}

double	phong(t_vec *obj, t_vec *nor, t_vec *rd, t_vec *pos)
{
	double	phong;
	t_vec	ref;
	t_vec	light;

	light = vecsub(obj, pos);
	vecnorm(&light);
	ref = vecreflect(rd, nor);
	vecnorm(&ref);
	phong = ft_clamp(pow(ft_clamp(vecdot(&ref, &light), \
					0.0, 1.0), 50.0), 0.0, 1.0);
	return (phong);
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
			tmp = inter_shadows(e, pos, &obj->pos);
			if (tmp == 1)
				sha -= (e->ln + obj->power) / 2.0;
		}
		obj = obj->next;
	}
	return (ft_clamp(sha, 0.0, 1.0));
}

void	get_lighting(t_env *e, t_vec *col, t_vec *pos, t_vec *nor)
{
	double	sha;
	t_vec	spe;
	t_vec	lig;
	t_obj	*obj;
	t_vec	lig_tmp;

	lig = (t_vec){0.0, 0.0, 0.0};
	spe = (t_vec){0.0, 0.0, 0.0};
	sha = get_shadows(e, pos);
	obj = e->obj;
	while (obj)
	{
		if (obj->type == 4)
		{
			lig_tmp = lambert(obj, nor, pos);
			lig = vecadd(&lig, &lig_tmp);
			spe = vecopplus(&spe, phong(&obj->pos, nor, &e->rd, pos));
		}
		obj = obj->next;
	}
	lig = vecopx(&lig, e->ln);
	lig = vecopx(&lig, sha);
	spe = vecprod(&spe, &lig);
	*col = vecadd(col, &spe);
	vecclamp(col, 0.0, 1.0);
	*col = vecprod(col, &lig);
}
