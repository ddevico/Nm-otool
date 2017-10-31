/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/31 15:16:09 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

int		search_lst(t_offlist *lst, uint32_t off)
{
	t_offlist	*cur;

	cur = lst;
	while (cur)
	{
		if (cur->off == off)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void        file_broken(void)
{
    ft_putstr("File is broken...\n");
}

int            verif(void *ask)
{
    if (ask <= g_buff_addr + g_buff_size)
        return (1);
    return (0);
}
