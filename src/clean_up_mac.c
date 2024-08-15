/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_mac.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:46:59 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/15 21:31:19 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Clean sphere linked list
void	ft_clean_sphere(t_data *data)
{
	t_sphere	*sphere;
	t_sphere	*tmp;

	sphere = data->sphere;
	while (sphere)
	{
		tmp = sphere->next;
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
		free(cylinder);
		cylinder = tmp;
	}
}

// Free all the allocated memory
void	ft_free_all(t_data *data)
{
	if (data->ambient)
		free(data->ambient);
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
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
	free(data->mlx->mlx);
	free(data->mlx);
	free(data);
}
