/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:53:25 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/05 13:56:15 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	space_check_malloc(char *str)
{
	t_var	var;

	var.i = 0;
	var.len = 0;
	while (str[var.i] != '\0')
	{
		var.j = 0;
		if (str[var.i] == '\n' && str[var.i + 1] == ' ')
		{
			var.len++;
			var.i++;
			while (str[var.i] == ' ' && str[var.i] != '\0')
				var.i++;
			if (str[var.i] == '\n')
				var.j = 1;
		}
		var.len++;
		if (var.j != 1 && str[var.i] != '\0')
			var.i++;
	}
	return (var.len);
}

/*Space_check : prend une chaine et supprime les espaces si entre 2 '\n'
il n'y a que des espaces et renvoie la chaine modifie (utilise pour str_arg)*/

static char	*space_check(char *str)
{
	t_var	var;

	var.i = 0;
	var.k = 0;
	var.new_str = malloc(sizeof(char) * (space_check_malloc(str) + 1));
	if (var.new_str == NULL)
		return (free(str), NULL);
	while (str[var.i] != '\0')
	{
		var.j = 0;
		if ((str[var.i] == '\n' && str[var.i + 1] == ' '))
		{
			var.new_str[var.k++] = str[var.i];
			var.i++;
			while (str[var.i] == ' ' && str[var.i] != '\0')
				var.i++;
			if (str[var.i] == '\n')
				var.j = 1;
		}
		var.new_str[var.k++] = str[var.i];
		if (var.j != 1 && str[var.i] != '\0')
			var.i++;
	}
	var.new_str[var.k] = '\0';
	return (free(str), var.new_str);
}

/*Get_file : recupere tout les elements d'un fichier dans une chaine*/

static char	*get_file(char **av, char *str_map)
{
	int		fd;
	char	*temp;

	temp = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		free_make_tab(NULL, str_map, NULL, "Wrong path map");
	temp = get_next_line(fd);
	while (temp)
	{
		str_map = join(str_map, temp);
		if (str_map == NULL)
		{
			free(temp);
			close (fd);
			exit (1);
		}
		temp = get_next_line(fd);
	}
	free (temp);
	close (fd);
	return (str_map);
}

static	void	cut_and_check(t_data *data, char **str_map, char **str_arg)
{
	int	indice_cut;

	indice_cut = 0;
	*str_map = cut_map(*str_map, &indice_cut);
	if (*str_map == NULL)
		free_make_tab(data, *str_map, *str_arg, "Invalid file information");
	*str_arg = ft_substr(*str_arg, 0, indice_cut);
	if (*str_arg == NULL)
		free_make_tab(data, *str_map, *str_arg, NULL);
	*str_arg = space_check(*str_arg);
	if (*str_arg == NULL)
		free_make_tab(data, *str_map, *str_arg, NULL);
	data->map = ft_split(*str_map, '\n');
	if (*str_arg == NULL)
		free_make_tab(data, *str_map, *str_arg, NULL);
	data->arg = ft_split(*str_arg, '\n');
	if (*str_arg == NULL)
		free_make_tab(data, *str_map, *str_arg, NULL);
}

/*Make_tab : Recupere les infos map dans un fichier, decoupe en 2 parties les
elements et la map et stocke dans un double tab chacuns des elements*/

void	make_tab(char **av, t_data *data)
{
	char	*str_map;
	char	*str_arg;

	str_map = NULL;
	str_arg = NULL;
	str_map = ft_calloc(1, 1);
	if (str_map == NULL)
		exit(1);
	str_map = get_file(av, str_map);
	str_arg = ft_strdup(str_map);
	if (str_arg == NULL)
		free_make_tab(data, str_map, str_arg, NULL);
	cut_and_check(data, &str_map, &str_arg);
	free(str_arg);
	free(str_map);
}
