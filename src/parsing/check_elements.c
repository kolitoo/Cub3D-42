/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:46:17 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/22 11:11:46 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Get_elemets et Fill_elements : Remplie a partir du double tableau d'argument
chaque chaine en passant l'identifiant*/

static char	*fill_elements(t_data *data, int j, int i)
{
	char	*str;

	str = NULL;
	while (data->arg[j][i] == ' ')
		i++;
	str = ft_substr_nofree(data->arg[j], i, ft_strlen(data->arg[j]) - i);
	return (str);
}

static void	get_elements(t_data *data)
{
	t_var	va;

	va.j = 0;
	while (data->arg[va.j] != NULL)
	{
		va.i = 0;
		while (data->arg[va.j][va.i] == ' ')
			va.i++;
		if (data->arg[va.j][va.i] == 'N' && data->arg[va.j][va.i + 1] == 'O')
			data->no_path = fill_elements(data, va.j, va.i + 2);
		if (data->arg[va.j][va.i] == 'S' && data->arg[va.j][va.i + 1] == 'O')
			data->so_path = fill_elements(data, va.j, va.i + 2);
		if (data->arg[va.j][va.i] == 'W' && data->arg[va.j][va.i + 1] == 'E')
			data->we_path = fill_elements(data, va.j, va.i + 2);
		if (data->arg[va.j][va.i] == 'E' && data->arg[va.j][va.i + 1] == 'A')
			data->ea_path = fill_elements(data, va.j, va.i + 2);
		if (data->arg[va.j][va.i] == 'F')
			data->floor_color = fill_elements(data, va.j, va.i + 1);
		if (data->arg[va.j][va.i] == 'C')
			data->sky_color = fill_elements(data, va.j, va.i + 1);
		va.j++;
	}
}

/*Check_path : Ouvre les chemins des textures des 4 faces des murs
et verifie que le chemin est valide et peut etre ouvert*/

static void	check_path(t_data *data)
{
	t_var	fd;

	fd.j = 0;
	fd.k = 0;
	fd.len = 0;
	fd.i = open(data->no_path, O_RDONLY);
	if (fd.i == -1)
		free_parsing(data, "Invalid texture path");
	fd.j = open(data->so_path, O_RDONLY);
	if (fd.j == -1)
		close_fd(fd, data, 1);
	fd.k = open(data->we_path, O_RDONLY);
	if (fd.k == -1)
		close_fd(fd, data, 2);
	fd.len = open(data->ea_path, O_RDONLY);
	if (fd.len == -1)
		close_fd(fd, data, 3);
	close(fd.i);
	close(fd.j);
	close(fd.k);
	close(fd.len);
}

/*Check_RGB : Parcour les chaines floor et sky et verifie si il y'a bien 3
chiffres pour le RGB et si ils sont bien entre 0 et 255*/

static int	check_rgb(char	*str, char **tab_color)
{
	t_var	var;

	var.i = 0;
	if (str[var.i] == '\0')
		return (1);
	var.color = ft_atoi(str, &var.i);
	if (var.color < 0 || var.color > 255 || str[var.i] == '\0')
		return (1);
	if (str[var.i] == '\0')
		return (1);
	var.i++;
	tab_color[0] = itoahex(var.color);
	var.color = ft_atoi(str, &var.i);
	if (var.color < 0 || var.color > 255 || str[var.i] == '\0')
		return (1);//free si pb psk color_* est malloc
	var.i++;
	if (str[var.i] == '\0')
		return (1);
	tab_color[1] = itoahex(var.color);
	var.color = ft_atoi(str, &var.i);
	if (var.color < 0 || var.color > 255 || str[var.i] != '\0')
		return (1);//free si pb psk color_* est malloc
	tab_color[2] = itoahex(var.color);
	tab_color[3] = NULL;
	return (0);
}

/*Check_elements : Execute plusieurs check pour verifier
si les elements sont valides*/

void	check_elements(t_data *data)
{
	if (tab_len(data->arg) != 6)
		free_2_tab(data, "Incorrect number elements");
	check_all_identifier(data);
	get_elements(data);
	if (data->no_path == NULL || data->so_path == NULL || data->we_path == NULL
		|| data->ea_path == NULL || data->floor_color == NULL
		|| data->sky_color == NULL)
		free_parsing(data, "Invalid identifier");
	check_path(data);
	data->tab_color_floor = malloc(sizeof(char *) * 4);
	if (!data->tab_color_floor)
		free_tab_color(data, "tab_color_floor failed", 0);
	data->tab_color_sky = malloc(sizeof(char *) * 4);
	if (!data->tab_color_sky)
		free_tab_color(data, "tab_color_sky failed", 1);
	if (check_rgb(data->floor_color, data->tab_color_floor) == 1
		|| check_rgb(data->sky_color, data->tab_color_sky) == 1)
		free_parsing(data, "Incorrect RGB value");
}
