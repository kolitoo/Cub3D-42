/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:55:13 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/28 13:29:54 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	tab_len(char **tab)
{
	t_var	var;

	var.j = 0;
	while (tab[var.j] != NULL)
		var.j++;
	return (var.j);
}

static int	len_itoa(int nbr)
{
	int	len;

	len = 1;
	while (nbr > 15)
	{
		nbr = nbr / 16;
		len++;
	}
	len++;
	return (len);
}

char	*itoahex(int nbr)
{
	char	*str;
	char	*base;
	int		i;

	i = 0;
	base = "0123456789ABCDEF";
	if (nbr == 0)
	{
		str = malloc(sizeof(char) * 3);
		str[0] = '0';
		str[1] = '0';
		str[2] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * len_itoa(nbr));
	i = len_itoa(nbr) - 1;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = base[nbr % 16];
		nbr = nbr / 16;
		i--;
	}
	return (str);
}

int	char_to_hexaint(char **tab_color)
{
	int	i;
	int	j;
	int	indice;
	int	nbr;
	int	index;

	j = -1;
	nbr = 0;
	indice = 1048576;
	while (tab_color[++j] != NULL)
	{
		i = 0;
		while (tab_color[j][i] != '\0')
		{
			if (tab_color[j][i] >= '0' && tab_color[j][i] <= '9')
				index = tab_color[j][i] - '0';
			else if (tab_color[j][i] >= '0')
				index = tab_color[j][i] - 55;
			nbr = nbr + (index * indice);
			indice = indice / 16;
			i++;
		}
	}
	return (nbr);
}
