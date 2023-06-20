/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:33 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/20 14:00:17 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
		free (tab[i]);
	free (tab);
}

void	free_2_tab(t_data *data, char *str)
{
	free_tab(data->arg);
	free_tab(data->map);
	printf("Error\n%s\n", str);
	exit(1);
}

void	free_parsing(t_data *data, char *str)
{
	free_tab(data->arg);
	free_tab(data->map);
	if (data->no_path != NULL)
		free(data->no_path);
	if (data->so_path != NULL)
		free(data->so_path);
	if (data->we_path != NULL)
		free(data->we_path);
	if (data->ea_path != NULL)
		free(data->ea_path);
	if (data->floor_color != NULL)
		free(data->floor_color);
	if (data->sky_color != NULL)
		free(data->sky_color);
	printf("Error\n%s\n", str);
	exit(1);
}

void	close_fd(t_var fd, t_data *data, int bool)
{
	if (bool == 1)
		close(fd.i);
	if (bool == 2)
	{
		close(fd.i);
		close(fd.j);
	}
	if (bool == 3)
	{
		close(fd.i);
		close(fd.j);
		close(fd.k);
	}
	free_parsing(data, "Invalid path texture");
}

void	free_all(t_data *data)
{
	free_tab(data->arg);
	free_tab(data->map);
	free(data->no_path);
	free(data->so_path);
	free(data->we_path);
	free(data->ea_path);
	free(data->floor_color);
	free(data->sky_color);
}
