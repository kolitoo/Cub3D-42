/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:46:30 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/20 15:36:21 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int    close_window(t_data *data)
{
    mlx_loop_end(data->mlx_init);
    destroy_img(data);
    mlx_destroy_window(data->mlx_init, data->mlx_win);
    free_mlx(data);
    return (0);
}

static int    key_press(int keycode, t_data *data)
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

static int    key_release(int keycode, t_data *data)
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

void create_window(t_data *data, t_ray *ray)
{
    (void)ray;
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
    data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    mlx_put_image_to_window(data->mlx_init, data->mlx_win, data->img, 0, 0);
    mlx_hook(data->mlx_win, 17, 0, close_window, data);
    mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
    mlx_loop_hook(data->mlx_init, throw_ray, data);
    mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
    mlx_loop(data->mlx_init);
}
