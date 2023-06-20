/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:39:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/20 14:03:43 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_texture(t_data *data)
{
	if (data->ray->side == 1 && data->ray->raydir_y < 0)
		data->ray->texdir = 0;
	if (data->ray->side == 1 && data->ray->raydir_y >= 0)
		data->ray->texdir = 1;
	if (data->ray->side == 0 && data->ray->raydir_x >= 0)
		data->ray->texdir = 2;
	if (data->ray->side == 0 && data->ray->raydir_x < 0)
		data->ray->texdir = 3;
	if (data->ray->side == 0)
		data->ray->wallx = data->pos_y / 64 + (data->ray->wall_dist / 64.00) * data->ray->raydir_y;
	else
		data->ray->wallx = data->pos_x / 64 + (data->ray->wall_dist / 64.00) * data->ray->raydir_x;// / 64
	data->ray->wallx -= floor((data->ray->wallx));
}

void	ft_draw_texture(t_data *data, t_ray *ray, int i)
{
	double step;
	double texPos;
	int	texY;
	int	y;
	int	texx;

	y = ray->drawstart - 1;
	ft_init_texture(data);
	step = 1.0 * data->texture[0].height / ray->lineheight;
	texx = (int)(ray->wallx * data->texture[ray->texdir].width);
	if (ray->side == 0 && ray->raydir_x > 0)
		texx = data->texture[ray->texdir].width - texx - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		texx = data->texture[ray->texdir].width - texx - 1;
	texPos = (ray->drawstart - 1080 / 2 + ray->lineheight / 2) * step ;
	while (++y < ray->drawend)
	{
		texY = (int)texPos & ( data->texture[ray->texdir].height - 1);
		texPos += step;
		if (y < 1080 && i < 1920)
			my_mlx_pixel_put(data, i, y, data->texture[ray->texdir].addr[texY * data->texture[ray->texdir].line_length / 4 + texx]);
	}
}

static void	fill_texture(t_texture *texture, char *path, t_data *data)
{	
	texture->img = mlx_xpm_file_to_image(data->mlx_init, path, &texture->width, &texture->height);
}

void	init_texture_struct(t_data *data)
{
	t_texture	*texture;
	
	texture = malloc(sizeof(t_texture) * 4);
	// if (!texture)
		// ;//protect
	fill_texture(&texture[0], data->no_path, data);
	fill_texture(&texture[1], data->so_path, data);
	fill_texture(&texture[2], data->ea_path, data);
	fill_texture(&texture[3], data->we_path, data);
	texture[0].addr = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].line_length, &texture[0].endian);
	texture[1].addr = (int *)mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel, &texture[1].line_length, &texture[1].endian);
	texture[2].addr = (int *)mlx_get_data_addr(texture[2].img, &texture[2].bits_per_pixel, &texture[2].line_length, &texture[2].endian);
	texture[3].addr = (int *)mlx_get_data_addr(texture[3].img, &texture[3].bits_per_pixel, &texture[3].line_length, &texture[3].endian);
	data->texture = texture;
}