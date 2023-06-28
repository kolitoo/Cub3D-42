/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:32:31 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/28 11:47:05 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str, int *i)
{
	int	nb;
	int	old_nb;

	nb = 0;
	while (str[*i] == ' ' || str[*i] == '\f'
		|| str[*i] == '\t' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == '\v')
		*i = *i + 1;
	if (str[*i] == '\0' || str[*i] == ',')
		return (-1);
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			return (-1);
		*i = *i + 1;
	}
	while (str[*i] >= 48 && str[*i] <= 57)
	{
		old_nb = nb;
		nb = nb * 10 + str[*i] - 48;
		if (nb < old_nb)
			return (-1);
		*i = *i + 1;
	}
	return (nb);
}
