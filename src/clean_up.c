/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:46:59 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/03 23:01:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Clean light and camera
void	ft_clean_scene(t_data *data)
{
	if (data->ambient)
	{
		if (data->ambient->color)
			free(data->ambient->color);
		free(data->ambient);
	}
	if (data->camera)
	{
		if (data->camera->origin)
			free(data->camera->origin);
		if (data->camera->direction)
			free(data->camera->direction);
		free(data->camera);
	}
	if (data->light)
	{
		if (data->light->origin)
			free(data->light->origin);
		free(data->light);
	}
}

// Clean sphere linked list
void	ft_clean_sphere(t_data *data)
{
	t_sphere	*sphere;
	t_sphere	*tmp;

	sphere = data->sphere;
	while (sphere)
	{
		tmp = sphere->next;
		free(sphere->color);
		free(sphere->origin);
		free(sphere);
		sphere = tmp;
	}
}

// Clean plane linked list
void	ft_clean_plane(t_data *data)
{
	t_plane	*plane;
	t_plane	*tmp;

	plane = data->plane;
	while (plane)
	{
		tmp = plane->next;
		free(plane->color);
		free(plane->origin);
		free(plane->orientation);
		free(plane);
		plane = tmp;
	}
}

// Clean cylinder linked list
void	ft_clean_cylinder(t_data *data)
{
	t_cylinder	*cylinder;
	t_cylinder	*tmp;

	cylinder = data->cylinder;
	while (cylinder)
	{
		tmp = cylinder->next;
		free(cylinder->color);
		free(cylinder->origin);
		free(cylinder->orientation);
		free(cylinder);
		cylinder = tmp;
	}
}

// Free all the allocated memory
void	ft_free_all(t_data *data)
{
	ft_clean_scene(data);
	if (data->sphere)
		ft_clean_sphere(data);
	if (data->plane)
		ft_clean_plane(data);
	if (data->cylinder)
		ft_clean_cylinder(data);
	if (data->mlx->img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	if (data->mlx->win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx->mlx)
		mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	free(data);
}
