/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 11:12:58 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

int		search_lst(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*cur;

	cur = lst;
	while (cur)
	{
		if (cur->off == off && cur->strx)
			return (1);
		cur = cur->next;
	}
	return (0);
}
