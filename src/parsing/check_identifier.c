/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:41:33 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/05 13:56:05 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Check_all_identifier et Check_identifier : Parcours tout le double tableau 
et verfier si il y'a tout les identifiants*/

static int	check_identifier(t_data *data, char c1, char c2)
{
	t_var	var;

	var.j = 0;
	while (data->arg[var.j] != NULL)
	{
		var.i = 0;
		while (data->arg[var.j][var.i] == ' ')
			var.i++;
		if (c2 == '\0')
		{
			if (data->arg[var.j][var.i] == c1)
				return (0);
		}
		else
		{
			if (data->arg[var.j][var.i] == c1
				&& data->arg[var.j][var.i + 1] == c2)
				return (0);
		}
		var.j++;
	}
	return (1);
}

void	check_all_identifier(t_data *data)
{
	if (check_identifier(data, 'N', 'O') == 1)
		free_2_tab(data, "Invalid identifier");
	if (check_identifier(data, 'S', 'O') == 1)
		free_2_tab(data, "Invalid identifier");
	if (check_identifier(data, 'W', 'E') == 1)
		free_2_tab(data, "Invalid identifier");
	if (check_identifier(data, 'E', 'A') == 1)
		free_2_tab(data, "Invalid identifier");
	if (check_identifier(data, 'F', '\0') == 1)
		free_2_tab(data, "Invalid identifier");
	if (check_identifier(data, 'C', '\0') == 1)
		free_2_tab(data, "Invalid identifier");
}
