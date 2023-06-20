/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:14:19 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/15 15:42:02 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void draw_circle(t_data *data, int center_x, int center_y, int rayon)
{
	int i;
	int j;

	i = -rayon;
	while (++i < rayon)
	{
		j = -rayon;
		while (++j < rayon)
		{
			if (i * i + j * j <= rayon * rayon)
				my_mlx_pixel_put(data, (center_x * 1) + (i * 1) - (rayon * 2), (center_y * 1) + (j * 1) - (rayon * 2), 0x0000FF);
		}
	}
}

static void draw_background(t_data *data, int x, int y)
{
	int k;
	int m;

	k = -1;
	while (++k < data->minimap_width)
	{
		m = -1;
		while (++m < data->minimap_width)
		{
			if (data->map[y][x] == '0' || data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')//patch pb map
				my_mlx_pixel_put(data, (x * data->minimap_width) + m, (y * data->minimap_width) + k, 0xFFFFFF);
			if (data->map[y][x] == '1')
				my_mlx_pixel_put(data, (x * data->minimap_width) + m, (y * data->minimap_width) + k, 0x000000);
		}
	}
}

// Dessine les côtés des zéros en noir
// Dessine les côtés des wall en blanc
static void	draw_wall_sides(t_data *data, int x, int y)
{
	int k;

	k = -1;
	while (++k < data->minimap_width)
	{
		if (data->map[y][x] == '0' || data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')//patch pb map
		{
			my_mlx_pixel_put(data, (x * data->minimap_width) + k, (y * data->minimap_width), 0x000000);
			my_mlx_pixel_put(data, (x * data->minimap_width) + k, (y * data->minimap_width) + ((data->minimap_width - 1)), 0x000000);
			my_mlx_pixel_put(data, (x * data->minimap_width), (y * data->minimap_width) + k, 0x000000);
			my_mlx_pixel_put(data, (x * data->minimap_width) + ((data->minimap_width - 1)), (y * data->minimap_width) + k, 0x000000);
		}
		else if (data->map[y][x] == '1')
		{
			my_mlx_pixel_put(data, (x * data->minimap_width) + k, (y * data->minimap_width), 0xFFFFFF);
			my_mlx_pixel_put(data, (x * data->minimap_width) + k, (y * data->minimap_width) + ((data->minimap_width - 1)), 0xFFFFFF);
			my_mlx_pixel_put(data, (x * data->minimap_width), (y * data->minimap_width) + k, 0xFFFFFF);
			my_mlx_pixel_put(data, (x * data->minimap_width) + ((data->minimap_width - 1)), (y * data->minimap_width) + k, 0xFFFFFF);
		} 
	}
}

static void	bigger_line(t_data *data)
{
	int	j;

	j = -1;
	data->minimap_width = 0;
	while (data->map[++j] != NULL)
	{
		if (data->minimap_width < (int)ft_strlen(data->map[j]))
			data->minimap_width = (int)ft_strlen(data->map[j]);
	}
	data->minimap_width = 400 / data->minimap_width;
}

void draw_minimap(t_data *data)
{
	int x;
	int y;
	int center_x;
	int center_y;
	int rayon;

	y = 0;
	bigger_line(data);
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			draw_background(data, x, y);
			draw_wall_sides(data, x, y);
			x++;
		}
		y++;
	}
	center_x = ((data->pos_x / 64) * data->minimap_width) + (data->minimap_width / 2);
	center_y = ((data->pos_y / 64) * data->minimap_width) + (data->minimap_width / 2);
	rayon = (data->minimap_width / 2) * 0.5;
	draw_circle(data, center_x, center_y, rayon);
	throw_ray_minimap(data->ray, data);
}
