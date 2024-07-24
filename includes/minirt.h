/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:39:01 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/24 19:24:23 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif

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
	int		color_r;
	int		color_g;
	int		color_b;
}			t_ambient;

// camera position
// camera orientation: In range [-1,1] for each x,y,z
// horizontal field of view in degrees in range [0,180]
typedef struct s_camera
{
	float	origin_x;
	float	origin_y;
	float	origin_z;
	float	vector_x;
	float	vector_y;
	float	vector_z;
	float	fov;
}			t_camera;

// light position
// light brightness in range [0.0,1.0]
typedef struct s_light
{
	float	origin_x;
	float	origin_y;
	float	origin_z;
	float	ratio;
}			t_light;

// sphere position
// sphere diameter
// R,G,B colors in range [0-255]
typedef struct s_sphere
{
	float			origin_x;
	float			origin_y;
	float			origin_z;
	float			diameter;
	int				color_r;
	int				color_g;
	int				color_b;
	struct s_sphere	*next;
}			t_sphere;

// plane position
// orientation: In range [-1,1] for each x,y,z
// R,G,B colors in range [0-255]
typedef struct s_plane
{
	float			origin_x;
	float			origin_y;
	float			origin_z;
	float			vector_x;
	float			vector_y;
	float			vector_z;
	int				color_r;
	int				color_g;
	int				color_b;
	struct s_plane	*next;
}			t_plane;

// cylinder position (center of the cylinder)
// orientation: In range [-1,1] for each x,y,z
// cylinder diameter and height
// R,G,B colors in range [0-255]
typedef struct s_cylinder
{
	float				origin_x;
	float				origin_y;
	float				origin_z;
	float				vector_x;
	float				vector_y;
	float				vector_z;
	float				diameter;
	float				height;
	int					color_r;
	int					color_g;
	int					color_b;
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

//Start program
int		main(int argc, char **argv);
void	ft_init_data(t_data *data);
void	ft_launch_mlx(t_data *data);

//Error handling and cleanup
void	ft_error(char *message, t_data *data);
void	ft_parsing_error(char *str, t_data *data, char *line);
void	ft_free_array(char **arr);
void	ft_clean_data(t_data *data);
void	ft_free_all(t_data *data);

//Parsing
int		ft_parse_scene(char *file, t_data *data);
void	ft_parsing(int fd, char *line, t_data *data);
void	ft_parse_ambient(char *line, t_data *data);
void	ft_parse_camera(char *line, t_data *data);
void	ft_set_camera(t_camera *camera, char **arr, char **pos, char **vec);
void	ft_parse_light(char *line, t_data *data);

//Utils
void	ft_normalize_whitespace(char *line);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);

//Hooks
int		ft_key_handle(int keysym, t_data *data);
int		ft_mouse_quit(t_data *data);

#endif
