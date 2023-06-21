/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:05:09 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/21 18:27:16 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Check du que le path vers la map se finit bien par .cub*/
static int	check_cub(char **av)
{
	t_var	var;

	var.len = ft_strlen(av[1]);
	if (av[1][var.len - 1] != 'b')
		return (1);
	if (av[1][var.len - 2] != 'u')
		return (1);
	if (av[1][var.len - 3] != 'c')
		return (1);
	if (av[1][var.len - 4] != '.')
		return (1);
	if (ft_isascii(av[1][var.len - 5]) == 0)
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
	if (check_cub(av) == 1)
	{
		printf("Error\nInvalid file name, write something.cub\n");
		exit (1);
	}
	make_tab(av, data);
	check_elements(data);
	check_map(data);
	return (0);
}
