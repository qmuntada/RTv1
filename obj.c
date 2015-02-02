/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 19:31:27 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/02 19:38:30 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	objinit(t_obj *obj)
{
	obj->type = 0;
	obj->size = 0.5;
	obj->pos = (t_vec){0, 0, 0};
	obj->rot = (t_vec){0, 0, 0};
	obj->color.x = 1.0;
	obj->color.y = 1.0;
	obj->color.z = 1.0;
}

t_obj	*objnew(t_obj *obj)
{
	t_obj	*ret;

	ret = malloc(sizeof(t_obj));
	ret->type = obj->type;
	ret->size = obj->size / 100.0;
	ret->pos = obj->pos;
	ret->rot = obj->rot;
	ret->color = obj->color;
	return (ret);
}

void	objpushback(t_env *e, t_obj *obj)
{
	t_obj	*cur;

	cur = e->obj;
	if (cur)
	{
		while (cur->next)
			cur = cur->next;
		cur->next = objnew(obj);
	}
	else
		e->obj = objnew(obj);
}
