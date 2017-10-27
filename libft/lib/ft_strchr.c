/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:19:43 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 14:30:58 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char		i;

	i = c;
	if (s == NULL)
		return (NULL);
	while (*s != i)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
