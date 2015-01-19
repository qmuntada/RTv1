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

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (1);
}

int		main(int ac, char **av)
{
	t_env e;

	parser(&e, ac, av);
	mlx_hook(e.win, KeyPress, KeyPressMask, &key_press, &e);
	mlx_hook(e.win, KeyRelease, KeyReleaseMask, &key_release, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (1);
}
