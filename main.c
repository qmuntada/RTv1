/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:56:05 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/19 17:35:07 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_image(t_env *e)
{
	int		x;
	int		y;
	t_vec	color;

	y = -1;
	setvec(&color, 0.0, 0.0, 0.0);
	while (++y < e->screen.height)
	{
		x = -1;
		while (++x < e->screen.width)
			pixel_put(e, x, y, &color);
	}
}

int		expose_hook(t_env *e)
{
	//init_image(e);
	display(e);
	mlx_put_image_to_window(e->mlx, e->win, e->screen.img_ptr, 0, 0);
	return (1);
}

int		main(int ac, char **av)
{
	t_env e;

	init_env_preparsing(&e);
	parser(&e, ac, av);
	init_env_postparsing(&e);
	mlx_hook(e.win, KeyPress, KeyPressMask, &key_press, &e);
	mlx_hook(e.win, KeyRelease, KeyReleaseMask, &key_release, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (1);
}
