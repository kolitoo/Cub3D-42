/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:43:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/06/02 10:40:00 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_strdup(""));
	if (start + len > len_s)
		len = len_s - start;
	sub = malloc(len + 1);
	if (sub == NULL)
	{
		free(s);
		return (NULL);
	}
	ft_strlcpy(sub, (s + start), (len + 1));
	free(s);
	return (sub);
}
