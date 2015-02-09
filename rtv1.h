/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:51:43 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/06 18:20:16 by qmuntada         ###   ########.fr       */
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
# define FOV 2.5
# define GAMMA 1.0

typedef struct			s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef struct			s_obj
{
	int					type;
	t_vec				pos;
	t_vec				rot;
	t_vec				color;
	double				size;
	double				power;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	int					screen_height;
	int					screen_width;
	t_vec				cam_pos;
	t_vec				cam_dir;
	t_vec				ro;
	t_vec				rd;
	t_vec				col;
	t_obj				*obj;
	t_obj				*objs;
	char				*screen_name;
	double				ln;
	double				tmin;
}						t_env;

int						expose_hook(t_env *e);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
void					parser(t_env *e, int ac, char **av);
void					file_reader(t_env *e, t_list *list);
void					get_name(t_env *e, char *info);
void					get_camera(t_env *e, char *info, int type);
void					get_render(t_env *e, char *info);
void					get_color(t_obj *obj, char *info);
void					get_double(t_obj *obj, char *info, int type);
void					get_objvec(t_vec *vec, char *info);
void					objinit(t_obj *obj);
t_obj					*objnew(t_obj *obj);
void					objpushback(t_env *e, t_obj *obj);
void					init_env_preparsing(t_env *e);
void					init_env_postparsing(t_env *e);
void					pixel_put(t_env *e, int x, int y);
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
t_vec					vecreflect(t_vec *i, t_vec *n);
t_vec					vecopplus(t_vec *a, double x);
t_vec					vecopdiv(t_vec *a, double x);
void					vecclamp(t_vec *vec, double a, double b);
t_vec					setnor(t_obj *obj, t_vec *pos);
void					get_lighting(t_env *e, t_vec *col, t_vec *pos, \
							t_vec *nor);
t_obj					*inter_object(t_env *e, t_vec *ro, t_vec *rd, \
							double *dmin);
double					inter_shadows(t_env *e, t_vec *pos, t_vec *lpos);
double					vecdistance(t_vec *a, t_vec *b);


#endif
