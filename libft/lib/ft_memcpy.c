/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:31:21 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/18 14:05:33 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pdst;
	const char	*psrc;

	pdst = dst;
	psrc = src;
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}
