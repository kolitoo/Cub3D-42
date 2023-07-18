/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:40 by abourdon          #+#    #+#             */
/*   Updated: 2023/07/18 18:10:42 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Init dir_x/y et plan_x_y en fonction de la position 
//de depart du personnage + trouve la couleur rgb sky/floor
static void	init_start_pos_ns(t_data *data, t_ray *ray)
{
	data->color_floor = char_to_hexaint(data->tab_color_floor);
	data->color_sky = char_to_hexaint(data->tab_color_sky);
	if (data->pos_letter == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plan_x = 0.60;
		ray->plan_y = 0;
	}
	if (data->pos_letter == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plan_x = -0.60;
		ray->plan_y = 0;
	}
	data->ray = ray;
}

static void	init_start_pos_ew(t_data *data, t_ray *ray)
{
	if (data->pos_letter == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plan_x = 0;
		ray->plan_y = 0.60;
	}
	else if (data->pos_letter == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plan_x = 0;
		ray->plan_y = -0.60;
	}
	data->ray = ray;
}

int	main(int ac, char **av)
{
	t_data	data;
	t_ray	ray;

	data = (t_data){};
	get_map_info(av, ac, &data);
	init_start_pos_ns(&data, &ray);
	init_start_pos_ew(&data, &ray);
	create_window(&data);
	free_all(&data);
}
