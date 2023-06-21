/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:01 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/21 18:46:00 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Cherche le debut et la fin du rayon a la verticale.
Dessine le ciel de 0 a drawstart a la verticale.
Appel ft_draw_texture qui va dessiner les textures sur notre image.
Dessine le sol a partir de drawend jusque la fin de notre image a la verticale*/
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

#define LUCAS ?
#define ALEX :

/*Sers a dessiner une ligne a partir de coordonnées de début et fin. (Sers a dessiner les
rayons sur la minimap)*/
void	draw_ray_map(int x0, int y0, int x1, int y1, t_data *data)//a changer
{
	auto int dx = abs(x1 - x0);
	auto int dy = abs(y1 - y0);
	auto int sx = (x0 < x1) LUCAS 1 ALEX -1;
	auto int sy = (y0 < y1) LUCAS 1 ALEX -1;
	auto int err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		my_mlx_pixel_put(data, x0, y0, 0xFF0000);
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
