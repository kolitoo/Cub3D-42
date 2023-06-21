/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:40 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/21 18:28:11 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Init dir_x/y et plan_x_y en fonction de la position de depart du personnage + trouve la couleur rgb sky/floor
static void	init_mlx(t_data *data, t_ray *ray)
{
	data->mlx_init = NULL;
	data->mlx_win = NULL;
	data->color_floor = test(data->tab_color_floor);
	data->color_sky = test(data->tab_color_sky);
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
	else if (data->pos_letter == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plan_x = 0.60;
		ray->plan_y = 0;
	}
	else if (data->pos_letter == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plan_x = -0.60;
		ray->plan_y = 0;
	}
	data->ray = ray;
}


int	main(int ac, char **av)
{
	t_data	data;
	t_ray	ray;

	(void)ray;
	data = (t_data){};
	// data.cam_right = 0;
	// data.cam_left = 0;
	// data.perso_up = 0;
	// data.perso_down = 0;
	// data.perso_left = 0;
	// data.perso_right = 0;
	get_map_info(av, ac, &data);
	init_mlx(&data, &ray);
	create_window(&data);
	free_all(&data);
}
