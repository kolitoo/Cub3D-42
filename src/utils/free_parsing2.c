/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:29:16 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/05 13:56:19 by abourdon         ###   ########.fr       */
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
	if (data->map != NULL)
		free_tab(data->map);
	exit (1);
}
