/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:31:20 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/28 10:01:39 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Permets de trouver camera_x et raydir_x/y*/
static void	ray_init(t_ray *ray, int i)
{
	ray->camera_x = 2.00 * i / 1920 - 1;
	ray->raydir_x = ray->dir_x + ray->plan_x * ray->camera_x;
	ray->raydir_y = ray->dir_y + ray->plan_y * ray->camera_x;
}

/*Permet de trouver deltadist_x/y et ainsi sidedist_x/y*/
static void	sidedist_deltadist(t_ray *ray, t_data *data)
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

/*Permet de connaitre la taille des rayons*/
static void	len_ray(t_ray *ray, t_data *data)
{
	while (1)
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
			break ;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
	else if (ray->side == 1)
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
	if (ray->wall_dist == 0)
		ray->wall_dist = 1;
}

/*Fonction qui lance tout le processus de raycasting dans la boucle.
Le reste sert a afficher sur l'écran, dessiner la minimap est faire 
les deplacements du joueur*/
int	throw_ray(t_data *data)
{
	double	i;

	i = -1;
	while (++i <= 1920)
	{
		ray_init(data->ray, i);
		sidedist_deltadist(data->ray, data);
		len_ray(data->ray, data);
		draw_game(data, i);
	}
	mlx_put_image_to_window(data->mlx_init, data->mlx_win, data->img, 0, 0);
	draw_minimap(data);
	move_player_key(data);
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx_init, data->mlx_win, data->img, 0, 0);
	return (0);
}

/*Sert a chercher les rayons et de dessiner la minimap*/
void	throw_ray_minimap(t_ray *ray, t_data *data)
{
	double	i;

	i = -1;
	while (++i <= 1920)
	{
		ray_init(ray, i);
		sidedist_deltadist(ray, data);
		len_ray(ray, data);
		draw_ray_map((data->pos_x / 64) * data->minimap_width,
			(data->pos_y / 64) * data->minimap_width, data);
	}
}
