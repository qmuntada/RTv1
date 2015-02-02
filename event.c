/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:33:47 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/19 16:57:07 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_press(int keycode, t_env *e)
{
	if (keycode == W && e->cam_pos.x > 2.0)
		e->cam_pos.x -= 1.0;
	if (keycode == S)
		e->cam_pos.x += 1.0;
	if (keycode == A)
		e->cam_dir.x -= 0.25;
	if (keycode == D)
		e->cam_dir.x += 0.25;
	expose_hook(e);
	return (1);
}

int		key_release(int keycode, t_env *e)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(EXIT_SUCCESS);
	}
	return (1);
}
