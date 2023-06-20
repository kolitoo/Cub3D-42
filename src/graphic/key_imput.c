/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_imput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:40:47 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/20 15:42:21 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_player_front(t_data *data, double move_step)
{
	if (data->perso_up == 1)
	{
		if (data->map[(int)data->pos_y / 64][(int)((data->pos_x
				+ data->ray->dir_x * move_step) / 64)] == '0')
			data->pos_x = data->pos_x + data->ray->dir_x * move_step;
		if (data->map[(int)(data->pos_y + data->ray->dir_y
				* move_step) / 64][(int)data->pos_x / 64] == '0')
			data->pos_y = data->pos_y + data->ray->dir_y * move_step;
	}
	if (data->perso_down == 1)
	{
		if (data->map[(int)data->pos_y / 64][(int)((data->pos_x
				- data->ray->dir_x * move_step) / 64)] == '0')
		data->pos_x = data->pos_x - data->ray->dir_x * move_step;
		if (data->map[(int)((data->pos_y - data->ray->dir_y
					* move_step) / 64)][(int)data->pos_x / 64] == '0')
		data->pos_y = data->pos_y - data->ray->dir_y * move_step;
	}
}

static void	move_player_side(t_data *data, double move_step)
{
	if (data->perso_right == 1)
	{
		if (data->map[(int)data->pos_y / 64][(int)((data->pos_x
				- data->ray->plan_x * move_step) / 64)] == '0')
			data->pos_x = data->pos_x - data->ray->plan_x * move_step;
		if (data->map[(int)((data->pos_y - data->ray->plan_y
					* move_step) / 64)][(int)data->pos_x / 64] == '0')
			data->pos_y = data->pos_y - data->ray->plan_y * move_step;
	}
	if (data->perso_left == 1)
	{
		if (data->map[(int)data->pos_y / 64][(int)((data->pos_x
				+ data->ray->plan_x * move_step) / 64)] == '0')
			data->pos_x = data->pos_x + data->ray->plan_x * move_step;
		if (data->map[(int)((data->pos_y + data->ray->plan_y
					* move_step) / 64)][(int)data->pos_x / 64] == '0')
			data->pos_y = data->pos_y + data->ray->plan_y * move_step;
	}
}

static void	move_camera_key(t_data *data)
{
	const double	olddir_x = data->ray->dir_x;
	const double	oldplan_x = data->ray->plan_x;

	if (data->cam_right == 1)
	{
		data->ray->dir_x = data->ray->dir_x * cos(0.04)
			- data->ray->dir_y * sin(0.04);
		data->ray->dir_y = olddir_x * sin(0.04)
			+ data->ray->dir_y * cos(0.04);
		data->ray->plan_x = data->ray->plan_x * cos(0.04)
			- data->ray->plan_y * sin(0.04);
		data->ray->plan_y = oldplan_x
			* sin(0.04) + data->ray->plan_y * cos(0.04);
	}
	if (data->cam_left == 1)
	{
		data->ray->dir_x = data->ray->dir_x
			* cos(-0.04) - data->ray->dir_y * sin(-0.04);
		data->ray->dir_y = olddir_x * sin(-0.04)
			+ data->ray->dir_y * cos(-0.04);
		data->ray->plan_x = data->ray->plan_x * cos(-0.04)
			- data->ray->plan_y * sin(-0.04);
		data->ray->plan_y = oldplan_x * sin(-0.04)
			+ data->ray->plan_y * cos(-0.04);
	}
}

void	move_player_key(t_data *data)
{
	double	move_step;

	move_step = 8;
	move_player_side(data, move_step);
	move_player_front(data, move_step);
	move_camera_key(data);
}
