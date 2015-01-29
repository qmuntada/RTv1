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
# define S 115
# define W 119
# define A 97
# define D 100

typedef struct			s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef struct			s_obj
{
	int					type; // 1 Plan 2 Sphere 3 Cylindre 4 Cone
	t_vec				pos;
	t_vec				rot;
	t_vec				color;
	double				size1;
	double				size2;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_img
{
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
	t_img				screen;
	t_vec				cam_pos;
	t_vec				cam_dir;
	t_obj				*obj;
	char				*screen_name;
}						t_env;

int						expose_hook(t_env *e);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
void					parser(t_env *e, int ac, char **av);
void					file_reader(t_env *e, t_list *list);
void					get_name(t_env *e, char *info);
void					get_camera(t_env *e, char *info);
void					get_render(t_env *e, char *info);
void					get_color(t_obj *obj, char *info);
void					get_size(t_obj *obj, char *info);
void					get_objvec(t_vec *vec, char *info);
void					setvec(t_vec *vec, double x, double y, double z);
void					objinit(t_obj *obj);
t_obj					*objnew(t_obj *obj);
void					objpushback(t_env *e, t_obj *obj);
void					init_env_preparsing(t_env *e);
void					init_env_postparsing(t_env *e);
void					pixel_put(t_env *e, int x, int y, t_vec *color);
void					display(t_env *e);
void					vecnorm(t_vec *vec);
double					vecdot(t_vec *a, t_vec *b);
t_vec					vecsub(t_vec *a, t_vec *b);
double					veclength(t_vec *vec);
t_vec					veccross(t_vec *a, t_vec *b);
t_vec					vecadd(t_vec *a, t_vec *b);
t_vec					vecdiv(t_vec *a, t_vec *b);
t_vec					vecprod(t_vec *a, t_vec *b);
t_vec					vecopx(t_vec *a, double x);

#endif
