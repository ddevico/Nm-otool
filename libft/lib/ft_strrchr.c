/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:40:18 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/18 14:06:21 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sav;

	sav = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			sav = (char *)s;
		s++;
	}
	if (*s == (char)c)
		sav = (char *)s;
	return (sav);
}
