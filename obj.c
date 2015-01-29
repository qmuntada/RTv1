#include "rtv1.h"

void	objinit(t_obj *obj)
{
	obj->type = 0;
	obj->size1 = 0.5;
	obj->size2 = 0.5;
	setvec(&obj->pos, 0, 0, 0);
	setvec(&obj->rot, 0, 0, 0);
	obj->color.x = 1.0;
	obj->color.y = 1.0;
	obj->color.z = 1.0;
}

t_obj	*objnew(t_obj *obj)
{
	t_obj	*ret;

	ret = malloc(sizeof(t_obj));
	ret->type = obj->type;
	ret->size1 = obj->size1 / 100.0;
	ret->size2 = obj->size2 / 100.0;
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
	{
		e->obj = objnew(obj);
	}
}
