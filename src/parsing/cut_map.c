/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:31:03 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/05 16:38:37 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Tab_next_to_tab : Si il y'a 2 '\n' d'affile
coupe la chaine sur le 2eme et renvoie cette chaine*/

static char	*tab_next_to_tab(char *str, int i)
{
	t_var	var;

	var.i = i;
	var.new_str = ft_substr(str, var.i, ft_strlen(str) - var.i);
	return (var.new_str);
}

/*Tab_with_empty_line : Si entre 2 '\n' il n'y a que des whitespaces coupe la
chaine au niveau du 2eme '\n et renvoie cette chaine*/

static char	*tab_with_empty_line(char *str, int i)
{
	t_var	var;

	var.j = i - 1;
	while (str[var.j] != '\n' && var.j >= 0)
	{
		if (str[var.j] != ' ' && (str[var.j] < 9 || str[var.j] > 13))
			break ;
		var.j--;
	}
	if (str[var.j] == '\n')
	{
		var.new_str = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
		return (var.new_str);
	}
	return (NULL);
}

/*Tab_with_others : Si apres un '\n' et jusqu'au suivant il y a un caractere
different de ceux autorises coupe la chaine au niveau du 2eme '\n' et
on renvoie cette chaine*/

static char	*tab_with_others(char *str, int i)
{
	t_var	var;

	var.j = i - 1;
	while (var.j >= 0 && str[var.j] != '\n')
	{
		if (str[var.j] != ' ' && str[var.j] != '0' && str[var.j] != '1'
			&& str[var.j] != 'N' && str[var.j] != 'S'
			&& str[var.j] != 'E' && str[var.j] != 'W')
		{
			var.new_str = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
			return (var.new_str);
		}
		var.j--;
	}
	return (NULL);
}

/*Cut_map : Prend la chaine str_map et cherche la map en partant de la fin
en fonction de plusieur condition qui marque le commencement de la map et
modifie via pointeur l'indice de ou se trouve cet endroit dans la chaine*/

char	*cut_map(char *str, int *indice_cut)
{
	t_var	var;

	var.i = ft_strlen(str) + 1;
	while (--var.i >= 0)
	{
		if (var.i >= 1 && str[var.i] == '\n' && str[var.i - 1] == '\n')
		{
			var.new_str = tab_next_to_tab(str, var.i);
			return (*indice_cut = var.i, var.new_str);
		}
		if (var.i >= 1 && str[var.i] == '\n' && (str[var.i - 1] == 32
				|| (str[var.i - 1] >= 9 && str[var.i - 1] <= 13)))
		{
			var.new_str = tab_with_empty_line(str, var.i);
			if (var.new_str != NULL)
				return (*indice_cut = var.i, var.new_str);
		}
		if (var.i >= 1 && str[var.i] == '\n')
		{
			var.new_str = tab_with_others(str, var.i);
			if (var.new_str != NULL)
				return (*indice_cut = var.i, var.new_str);
		}
	}
	return (free(str), NULL);
}
