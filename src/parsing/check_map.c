/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:52:11 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/22 11:13:24 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Check_right_left : Verifie dans le double tableau de la map si a droite et
a gauche il n'y a pas d'espace pour le caractere demanande*/

static int	check_right_left(t_data *data, int j, int i)
{
	if (i == 0 || data->map[j][i + 1] == '\0')
		return (1);
	if (data->map[j][i + 1] == ' ' || data->map[j][i - 1] == ' ')
		return (1);
	return (0);
}

/*Check_up_down : Verifie dans le double tableau de la map si au dessus et
en dessous il n'y a pas d'espace pour le caractere demanande*/

static int	check_up_down(t_data *data, int j, int i)
{
	if (j == 0 || data->map[j + 1] == NULL)
		return (1);
	if ((int)ft_strlen(data->map[j - 1]) < i
		|| (int)ft_strlen(data->map[j + 1]) < i)
		return (1);
	if (data->map[j + 1][i] == ' ' || data->map[j - 1][i] == ' ')
		return (1);
	return (0);
}

/*Next_char_check : Verifie pour un caractere demande
si il n'est pas a cote d'un espace*/

static int	next_char_check(t_data *data, char c)
{
	t_var	var;

	var.j = -1;
	while (data->map[++var.j] != NULL)
	{
		var.i = 0;
		while (data->map[var.j][var.i] != '\0')
		{
			if (data->map[var.j][var.i] == c)
			{
				if (check_right_left(data, var.j, var.i) == 1)
					return (1);
				if (check_up_down(data, var.j, var.i) == 1)
					return (1);
			}
			var.i++;
		}
	}
	return (0);
}

/*Verifie si le nombre de joueur est bien de 1*/

static int	player_check(t_data *data)
{
	t_var	var;

	var.j = -1;
	var.k = 0;
	while (data->map[++var.j] != NULL)
	{
		var.i = 0;
		while (data->map[var.j][var.i] != '\0')
		{
			if (data->map[var.j][var.i] == 'N' || data->map[var.j][var.i] == 'E'
				|| data->map[var.j][var.i] == 'W'
				|| data->map[var.j][var.i] == 'S')
			{
				data->pos_x = (double)(var.i + 0.5) * 64;
				data->pos_y = (double)(var.j + 0.5) * 64;
				data->pos_letter = data->map[var.j][var.i];
				data->map[var.j][var.i] = '0';
				var.k++;
			}
			var.i++;
		}
	}
	if (var.k != 1)
		return (1);
	return (0);
}

/*Check_map : Effectue plusieur check pour verifier si la map est valide*/

void	check_map(t_data *data)
{
	if (player_check(data) == 1)
		free_2_tab(data, "Incorrect player number");
	if (next_char_check(data, '0') == 1 || next_char_check(data, 'N') == 1
		|| next_char_check(data, 'E') == 1 || next_char_check(data, 'S') == 1
		|| next_char_check(data, 'W') == 1)
		free_2_tab(data, "Map not close");
}
