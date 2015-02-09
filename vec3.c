/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 17:14:58 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/05 17:14:59 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_vec	v;

	v.x = a->x * x;
	v.y = a->y * x;
	v.z = a->z * x;
	return (v);
}

double	vecdistance(t_vec *a, t_vec *b)
{
	double	distance;

	distance = sqrt((a->x - b->x) * (a->x - b->x) + \
		(a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
	return (distance);
}
