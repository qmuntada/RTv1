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
	double	value;

	light = vecsub(&obj->pos, pos);
	value = vecdistance(pos, &light);
	value = ft_clamp(sqrt(1.0 / (value * (1.0 - obj->power))), 0.0, 0.9);
	if (nor->x == 0.0 && nor->y == 1.0 && nor->z == 0.0)
		lambert = vecopx(&obj->color, obj->power);
	else
	{
		vecnorm(&light);
		value = ft_clamp(vecdot(nor, &light), 0.0, 1.0);
		lambert = vecopx(&obj->color, value);
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
				sha -= obj->power;
		}
		obj = obj->next;
	}
	return (ft_clamp(sha, 0.0, 1.0));
}

t_vec	get_diff(t_env *e, t_vec *pos, t_vec *nor)
{
	t_obj	*obj;
	t_vec	lig;
	t_vec	lig_tmp;

	obj = e->obj;
	lig = (t_vec){0.0, 0.0, 0.0};
	while (obj)
	{
		if (obj->type == 4)
		{
			lig_tmp = lambert(obj, nor, pos);
			lig = vecadd(&lig, &lig_tmp);
		}
		obj = obj->next;
	}
	lig = vecopx(&lig, e->ln);
	vecclamp(&lig, 0.0, 1.0);
	return (lig);
}

t_vec	get_spe(t_env *e, t_vec *pos, t_vec *nor)
{
	t_obj	*obj;
	t_vec	spe;

	obj = e->obj;
	spe = (t_vec){0.0, 0.0, 0.0};
	while (obj)
	{
		if (obj->type == 4)
			spe = vecopplus(&spe, phong(&obj->pos, nor, &e->rd, pos));
		obj = obj->next;
	}
	vecclamp(&spe, 0.0, 1.0);
	return (spe);
}


void	get_lighting(t_env *e, t_vec *col, t_vec *pos)
{
	double	sha;
	t_vec	spe;
	t_vec	lig;
	t_vec	nor;

	nor = setnor(e->objs, pos);
	sha = get_shadows(e, pos);
	lig = get_diff(e, pos, &nor);
	spe = get_spe(e, pos, &nor);
	lig = vecopx(&lig, sha);
	spe = vecprod(&spe, &lig);
	*col = vecadd(col, &spe);
	vecclamp(col, 0.0, 1.0);
	*col = vecprod(col, &lig);
}
