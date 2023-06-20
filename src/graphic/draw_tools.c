/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:07:01 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/20 14:06:26 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = (char *)data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_ray_map(int x0, int y0, int x1, int y1, t_data *data)//a changer
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

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

void	draw_all_black(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x <= 1920)
	{
		y = 0;
		while (y <= 1080)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}