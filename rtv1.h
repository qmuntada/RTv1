/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:51:43 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/19 18:12:27 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <X11/X.h>
# include <X11/Xlib.h>
# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ESC 65307

typedef struct			s_ray
{
	float				xs;
	float				ys;
	float				zs;
	float				xd;
	float				yd;
	float				zd;
}						t_ray;

typedef struct			s_img
{
	void				*win;
	void				*img_ptr;
	unsigned char		*img;
	int					bpp;
	int					sl;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_ray				cam;
	char				*screen_name;
}						t_env;

void	parser(t_env *e, int ac, char **av);
void	file_reader(t_env *e, t_list *list);

#endif
