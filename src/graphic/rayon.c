/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:31:20 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/20 14:07:52 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ray_init(t_ray *ray, int i)
{
	ray->camera_x = (double)2 * i / 1920 - 1;
	ray->raydir_x = ray->dir_x + ray->plan_x * ray->camera_x;
	ray->raydir_y = ray->dir_y + ray->plan_y * ray->camera_x;
}

static void	sideDist_deltaDist(t_ray *ray, t_data *data)
{
	ray->map_x = data->pos_x;
	ray->map_y = data->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
        	ray->step_x = 1;
        	ray->sidedist_x = (ray->map_x + 1 - data->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1 - data->pos_y) * ray->deltadist_y;
	}
}

static void	len_ray(t_ray *ray, t_data *data)
{
	int	hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[(int)ray->map_y / 64][(int)ray->map_x / 64] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
	else if (ray->side == 1)
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
	if (ray->wall_dist == 0)
		ray->wall_dist = 1;
}

int    throw_ray(t_data *data)
{
    double    i;

    i = -1;
    while (++i <= 1920)
    {
        ray_init(data->ray, i);
        sideDist_deltaDist(data->ray, data);
        len_ray(data->ray, data);
        draw_game(data, i);
    }
    mlx_put_image_to_window(data->mlx_init, data->mlx_win, data->img, 0, 0);
    draw_minimap(data);
    handle_input(data);
    return (0);
}

void	throw_ray_minimap(t_ray *ray, t_data *data)
{
	double	i;

	i = -1;
	while (++i <= 1920)
	{
		ray_init(ray, i);
		sideDist_deltaDist(ray, data);
		len_ray(ray, data);
		draw_ray_map((data->pos_x / 64) * data->minimap_width, (data->pos_y / 64) * data->minimap_width, (ray->map_x / 64) * data->minimap_width, (ray->map_y / 64) * data->minimap_width, data);
	}
}