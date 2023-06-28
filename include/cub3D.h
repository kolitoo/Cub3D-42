/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:19:48 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/28 13:30:13 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*minilibx*/
# include "../mlx-linux/mlx.h"

/*libft*/
# include "../libft/libft.h"

/*math*/
# include <math.h>

/*keybord*/
# include <X11/keysym.h>

/*printf, perror*/
# include <stdio.h>

/*perror*/
# include <errno.h>

/*open*/
# include <fcntl.h>

/*close, read, write, */
# include <unistd.h>

/*malloc, exit*/
# include <stdlib.h>

/*strerror*/
# include <string.h>

# define S 0x0073
# define A 0x0061
# define W 0x0077
# define D 0x0064
# define UP 0xff52
# define DO 0xff54
# define RI 0xff53
# define LE 0xff51

typedef struct s_texture
{
	char	**pixel_tab;
	void	*img;
	int		**color_tab;
	int		width;
	int		height;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_texture;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plan_x;
	double	plan_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	map_x;
	double	map_y;
	double	wallx;
	int		step_x;
	int		step_y;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texdir;
}t_ray;

typedef struct s_data
{
	char		**tab_color_sky;
	char		**tab_color_floor;
	char		**map;
	char		**arg;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_color;
	char		*sky_color;
	char		pos_letter;
	int			color_sky;
	int			color_floor;
	int			minimap_width;
	int			bool;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			cam_right;
	int			cam_left;
	int			perso_up;
	int			perso_down;
	int			perso_right;
	int			perso_left;
	int			*addr;
	void		*mlx_init;
	void		*mlx_win;
	void		*img;
	void		*img2;
	double		pos_x;
	double		pos_y;
	t_ray		*ray;
	t_texture	*texture;

}t_data;

typedef struct s_var
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		err;
	int		len;
	int		color;
	char	*str;
	char	*new_str;
}t_var;

/*get_map_info.c*/
int		get_map_info(char **av, int ac, t_data *data);
int		check_filename(char *file, char a, char b, char c);

/*check_map.c*/
void	check_map(t_data *data);

/*check_elements*/
void	check_elements(t_data *data);

/*free_parsing.c*/
void	free_tab(char **tab);
void	free_2_tab(t_data *data, char *str);
void	free_parsing(t_data *data, char *str);
void	free_all(t_data *data);
void	close_fd(t_var fd, t_data *data, int bool);

/*free_parsing2.c*/
void	free_make_tab(t_data *data, char *str_map, char *str_arg, char *str);
void	free_tab_color(t_data *data, char *str, int bool);

/*free_graphic.c*/
void	free_mlx(t_data *data);
void	destroy_img(t_data *data);

/*cut_map.c*/
char	*cut_map(char *str, int *indice_cut);

/*make_tab.c*/
void	make_tab(char **av, t_data *data);

/*check_identifier.c*/
void	check_all_identifier(t_data *data);

/*utils.c*/
char	*itoahex(int nbr);
int		tab_len(char **tab);
int		char_to_hexaint(char **tab_color);

/*window.c*/
void	create_window(t_data *data);

/*rayon.c*/
int		throw_ray(t_data *data);
void	throw_ray_minimap(t_ray *ray, t_data *data);

/*draw_map.C*/
void	draw_minimap(t_data *data);

/*draw_tools.c*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_ray_map(int x, int y, t_data *data);
void	draw_game(t_data *data, int i);
void	draw_all_black(t_data *data, int color);

/*key_imput.c*/
void	move_player_key(t_data *data);

/*texture.c*/
void	init_texture_struct(t_data *data);
void	ft_draw_texture(t_data *data, t_ray *ray, int i);

/*temporaire*/
void	print_map(char **tab);

#endif