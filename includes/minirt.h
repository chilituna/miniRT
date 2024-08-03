/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:39:01 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/03 10:59:55 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif

// 3D vector
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

// R,G,B colors in range [0-255]
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

// Ray from camera
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}			t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_mlx;

// ambient lighting ratio in range [0.0,1.0]
// R,G,B colors in range [0-255]
typedef struct s_ambient
{
	float	ratio;
	t_color	*color;
}			t_ambient;

// camera position
// camera orientation: In range [-1,1] for each x,y,z
// horizontal field of view in degrees in range [0,180]
typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		fov;
	t_vector	pixel00_location;
	t_vector	pixel_delta_x;
	t_vector	pixel_delta_y;
}				t_camera;

// light position
// light brightness in range [0.0,1.0]
typedef struct s_light
{
	t_vector	*origin;
	float		ratio;
}				t_light;

// sphere position
// sphere diameter
// R,G,B colors in range [0-255]
typedef struct s_sphere
{
	t_vector		*origin;
	float			diameter;
	t_color			*color;
	struct s_sphere	*next;
}			t_sphere;

// plane position
// orientation: In range [-1,1] for each x,y,z
// R,G,B colors in range [0-255]
typedef struct s_plane
{
	t_vector		*origin;
	t_vector		*orientation;
	t_color			*color;
	struct s_plane	*next;
}			t_plane;

// cylinder position (center of the cylinder)
// orientation: In range [-1,1] for each x,y,z
// cylinder diameter and height
// R,G,B colors in range [0-255]
typedef struct s_cylinder
{
	t_vector			*origin;
	t_vector			*orientation;
	float				diameter;
	float				height;
	t_color				*color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct s_data
{
	t_mlx		*mlx;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}			t_data;

// Hit distance and sphere
typedef struct s_hit
{
	float		distance;
	t_vector	hitpoint;
	t_vector	normal;
	t_sphere	*sphere;
}				t_hit;

//Start program
int			main(int argc, char **argv);
void		ft_init_data(t_data *data);
void		ft_launch_mlx(t_data *data);

//Error handling and cleanup
void		ft_error(char *message, t_data *data);
void		ft_parsing_error(char *str, t_data *data, char *line);
void		ft_free_array(char **arr);
void		ft_free_all(t_data *data);

//Parsing
int			ft_parse_scene(char *file, t_data *data);
void		ft_parsing(int fd, char *line, t_data *data);
void		ft_parse_ambient(char *line, t_data *data);
void		ft_parse_camera(char *line, t_data *data);
void		ft_parse_light(char *line, t_data *data);
void		ft_parse_sphere(char *line, t_data *data);
void		ft_parse_plane(char *line, t_data *data);
void		ft_parse_cylinder(char *line, t_data *data);
void		ft_set_cylinder(t_cylinder *cyl, char **pos,
				char **vec, char **rgb);
void		ft_set_cylinder_2(t_cylinder *cylinder, char **arr);

//Parsing Utils
int			ft_check_pos(char **pos, char **arr);
int			ft_check_vectors(char **arr, char **pos, char **vec);
int			ft_check_rgb(char **arr, char **rgb);
int			ft_check_rgb_2(char **arr, char **pos, char **vec, char **rgb);
void		ft_check_size(char **arr, int i, t_data *data, char *l);

// Drawing
void		ft_draw_scene(t_data *data);
t_hit		ft_hit_sphere(t_data *data, t_ray ray);
void		ft_setup_camera(t_camera *camera);

// Drawing utils
void		ft_my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int			ft_calculate_gradient(int x, int y);
int			ft_create_trgb(int t, double r, double g, double b);
int			ft_trgb(int t, t_color *color);

// Utils vector math
t_vector	ft_add(t_vector *v1, t_vector *v2);
t_vector	ft_subtract(t_vector *v1, t_vector *v2);
t_vector	ft_scale(t_vector *v, float scale);
t_vector	ft_normalize(t_vector *v);
float		ft_dot(t_vector *v1, t_vector *v2);

//Utils
void		ft_normalize_whitespace(char *line);
void		ft_remove_whitespace(char **arr);

//Hooks
int			ft_key_handle(int keysym, t_data *data);
int			ft_mouse_quit(t_data *data);

#endif
