/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:29:16 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/22 10:59:22 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_make_tab(t_data *data, char *str_map, char *str_arg, char *str)
{
	if (str != NULL)
		printf("Error\n%s\n", str);
	if (str_map != NULL)
		free(str_map);
	if (str_arg != NULL)
		free(str_arg);
	if (data != NULL)
		if (data->map != NULL)
			free_tab(data->map);
	exit (1);
}

void	free_tab_color(t_data *data, char *str, int bool)
{
	free_tab(data->arg);
	free_tab(data->map);
	free(data->no_path);
	free(data->so_path);
	free(data->we_path);
	free(data->ea_path);
	free(data->floor_color);
	free(data->sky_color);
	if (bool == 1)
		free(data->tab_color_floor);
	printf("Error\n%s\n", str);
	exit(1);
}
