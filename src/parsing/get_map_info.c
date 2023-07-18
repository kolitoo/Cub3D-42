/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:05:09 by abourdon          #+#    #+#             */
/*   Updated: 2023/07/18 15:39:41 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Check que le path vers la map se finit bien par .cub*/
int	check_filename(char *file, char a, char b, char c)
{
	t_var	var;

	var.len = ft_strlen(file);
	if (var.len < 4)
		return (1);
	if (file[var.len - 1] != c)
		return (1);
	if (file[var.len - 2] != b)
		return (1);
	if (file[var.len - 3] != a)
		return (1);
	if (file[var.len - 4] != '.')
		return (1);
	if (var.len - 4 == 0 || file[var.len - 5] == '/')
		return (1);
	if (ft_isascii(file[var.len - 5]) == 0)
		return (1);
	return (0);
}

/*Get_map_info : Recupere les infos (map et elements),
decoupe les infos en 2 parties map et
elements et check que chaque partie et correct*/
int	get_map_info(char **av, int ac, t_data *data)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number argument\n");
		exit (1);
	}
	if (check_filename(av[1], 'c', 'u', 'b') == 1)
	{
		printf("Error\nInvalid file name, write something.cub\n");
		exit (1);
	}
	make_tab(av, data);
	check_elements(data);
	check_map(data);
	return (0);
}
