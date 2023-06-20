/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:21:55 by abourdon          #+#    #+#             */
/*   Updated: 2023/06/05 16:40:19 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_mlx(t_data *data)
{
	free_all(data);
	if (data->mlx_init != NULL)
	{
		mlx_destroy_display(data->mlx_init);
		free(data->mlx_init);
	}
	exit(1);
}
