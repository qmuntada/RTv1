/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 18:05:57 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/19 18:39:50 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_scene(t_env *e, t_list *list)
{
	while (list && strstr(list->content, "{"))
		list = list->next;
	while (list && strstr(list->content, "}"))
	{
		if (strstr(list->content, "name"))
			get_name(e, ft_strsplit(list->content), '|');
		else if (strstr(list->content, "camera"))
			get_camera(e, ft_strsplit(list->content), '|');
		else if (strstr(list->content, "render"))
			get_render(e, ft_strsplit(list->content), '|');
		list = list->next;
	}
}


void	file_reader(t_env *e, t_list *list)
{
	while (list)
	{
		if (strstr(list->content, "scene"))
			get_scene(e, list);
		else if (strstr(list->content, "object"))
			get_object(e, list);
		list = list->next;
	}
}
