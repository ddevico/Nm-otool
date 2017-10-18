/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:48:29 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/18 14:05:28 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

void		*ft_memalloc(size_t size)
{
	void	*t;

	t = malloc(sizeof(void *) * size);
	if (!t)
		return (NULL);
	ft_memset(t, 0, size);
	return (t);
}
