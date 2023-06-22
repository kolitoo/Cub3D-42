/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:39:42 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/22 11:09:00 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*texdir permet de savoir quelle texture mettre selon l'angle vers ou
l'on regarde. wallx est la valeure ou le mur a été touché par le rayon*/
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
		data->ray->wallx = data->pos_y / 64
			+ (data->ray->wall_dist / 64.00) * data->ray->raydir_y;
	else
		data->ray->wallx = data->pos_x / 64
			+ (data->ray->wall_dist / 64.00) * data->ray->raydir_x;
	data->ray->wallx -= floor((data->ray->wallx));
}

/*texx et texy sont les coordonnées x et y de la texture
step est la valeur qui indique de combien augmenter les 
coordonnées de la texture pour chaque pixel texpos est 
la coordonnée de depart. Cette fonction permet de dessiner
la texture correspondant pour chaque rayon*/
void	ft_draw_texture(t_data *data, t_ray *ray, int i)
{
	double	step;
	double	texpos;
	int		texy;
	int		y;
	int		texx;

	y = ray->drawstart - 1;
	ft_init_texture(data);
	step = 1.0 * data->texture[0].height / ray->lineheight;
	texx = (int)(ray->wallx * data->texture[ray->texdir].width);
	if (ray->side == 0 && ray->raydir_x > 0)
		texx = data->texture[ray->texdir].width - texx - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		texx = data->texture[ray->texdir].width - texx - 1;
	texpos = (ray->drawstart - 1080 / 2 + ray->lineheight / 2) * step ;
	while (++y < ray->drawend)
	{
		texy = (int)texpos & (data->texture[ray->texdir].height - 1);
		texpos += step;
		if (y < 1080 && i < 1920)
			my_mlx_pixel_put(data, i, y, data->texture[ray->texdir].addr[texy
				* data->texture[ray->texdir].line_length / 4 + texx]);
	}
}

/*Charge l'image grace a mlx_xpm_file_to_image dans texture->img*/
static void	fill_texture(t_texture *texture, char *path, t_data *data)
{	
	texture->img = mlx_xpm_file_to_image(data->mlx_init,
			path, &texture->width, &texture->height);
}

/*Permet d'init une image pour chaque texture*/
static void	set_addr_texture(t_texture *texture)
{
	texture->addr = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

/*Creer le tableau de structure "texture" et init les 4 textures avec
des fonctions de la mlx*/
void	init_texture_struct(t_data *data)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture) * 4);
	if (!texture)
		free_mlx(data);
	fill_texture(&texture[0], data->no_path, data);
	fill_texture(&texture[1], data->so_path, data);
	fill_texture(&texture[2], data->ea_path, data);
	fill_texture(&texture[3], data->we_path, data);
	set_addr_texture(&texture[0]);
	set_addr_texture(&texture[1]);
	set_addr_texture(&texture[2]);
	set_addr_texture(&texture[3]);
	data->texture = texture;
}
