/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:01 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/28 10:26:33 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Cherche le debut et la fin du rayon a la verticale.
Dessine le ciel de 0 a drawstart a la verticale.
Appel ft_draw_texture qui va dessiner les textures sur notre image.
Dessine le sol a partir de drawend jusque la fin de notre image 
a la verticale*/
void	draw_game(t_data *data, int i)
{
	int	j;

	j = -1;
	data->ray->lineheight = (int)((1080 * 80) / data->ray->wall_dist);
	data->ray->drawstart = -data->ray->lineheight / 2 + 1080 / 2;
	if (data->ray->drawstart < 0)
		data->ray->drawstart = 0;
	data->ray->drawend = data->ray->lineheight / 2 + 1080 / 2;
	if (data->ray->drawend >= 1080)
		data->ray->drawend = 1080 - 1;
	while (++j < data->ray->drawstart)
		my_mlx_pixel_put(data, 1920 - i, j, data->color_sky);
	if (j <= data->ray->drawend)
		ft_draw_texture(data, data->ray, 1920 - i);
	j = data->ray->drawend - 1;
	while (++j < 1080)
		my_mlx_pixel_put(data, 1920 - i, j, data->color_floor);
}

/*Fonction qui permet de dessiner les pixel sur notre image*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_ray_loop_map(t_var var, t_data *data, int x, int y)
{
	int	e2;

	while (x != (int)((data->ray->map_x / 64) * data->minimap_width)
		|| y != (int)((data->ray->map_y / 64) * data->minimap_width))
	{
		my_mlx_pixel_put(data, x, y, 0xFF0000);
		e2 = 2 * var.err;
		if (e2 > -var.j)
		{
			var.err -= var.j;
			x += var.k;
		}
		if (e2 < var.i)
		{
			var.err += var.i;
			y += var.l;
		}
	}
}

/*Sers a dessiner une ligne a partir de coordonnées de début et fin. 
(Sers a dessiner les rayons sur la minimap)*/
void	draw_ray_map(int x, int y, t_data *data)
{
	t_var	var;

	var.i = abs((int)((data->ray->map_x / 64) * data->minimap_width) - x);
	var.j = abs((int)((data->ray->map_y / 64) * data->minimap_width) - y);
	var.k = -1;
	if (x < (int)((data->ray->map_x / 64) * data->minimap_width))
		var.k = 1;
	var.l = -1;
	if (y < (int)((data->ray->map_y / 64) * data->minimap_width))
		var.l = 1;
	var.err = var.i - var.j;
	draw_ray_loop_map(var, data, x, y);
}
