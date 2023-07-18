/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:46:30 by lgirault          #+#    #+#             */
/*   Updated: 2023/07/18 12:12:52 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*ferme la fenetre avec echap ou clic sur la croix avec la souris*/
int	close_window(t_data *data)
{
	mlx_loop_end(data->mlx_init);
	destroy_img(data);
	mlx_destroy_window(data->mlx_init, data->mlx_win);
	free_mlx(data);
	return (0);
}

/*met variables a 1 lorsque l'on press la touche*/
static int	key_press(int keycode, t_data *data)
{
	if (keycode == RI)
		data->cam_right = 1;
	else if (keycode == LE)
		data->cam_left = 1;
	else if (keycode == W)
		data->perso_up = 1;
	else if (keycode == S)
		data->perso_down = 1;
	else if (keycode == A)
		data->perso_left = 1;
	else if (keycode == D)
		data->perso_right = 1;
	else if (keycode == XK_Escape)
		close_window(data);
	return (1);
}

/*met variables a 0 lorsque l'on relache la touche*/
static int	key_release(int keycode, t_data *data)
{
	if (keycode == RI)
		data->cam_right = 0;
	else if (keycode == LE)
		data->cam_left = 0;
	else if (keycode == W)
		data->perso_up = 0;
	else if (keycode == S)
		data->perso_down = 0;
	else if (keycode == A)
		data->perso_left = 0;
	else if (keycode == D)
		data->perso_right = 0;
	return (1);
}

/*mlx_init + init la window grace a mlx_new_window
Cette fonction sert a lancer tout le programme (initialisation des textures,
lancement raycasting et fonctions de deplacement)*/
void	create_window(t_data *data)
{
	data->mlx_init = mlx_init();
	if (data->mlx_init == NULL)
	{
		free_all(data);
		exit(1);
	}
	data->mlx_win = mlx_new_window(data->mlx_init, 1920, 1080, "CUB3D");
	if (data->mlx_win == NULL)
		free_mlx(data);
	init_texture_struct(data);
	data->img = mlx_new_image(data->mlx_init, 1920, 1080);
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx_init, data->mlx_win, data->img, 0, 0);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx_init, throw_ray, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_loop(data->mlx_init);
}
