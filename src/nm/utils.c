/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/01 11:00:55 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

int		compare_strx(char *stringtable, struct nlist *array,
	uint32_t increment)
{
	if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
		stringtable + array[increment + 1].n_un.n_strx) == 0 &&
		array[increment].n_value != 0 && array[increment + 1].n_value != 0)
		return (1);
	return (0);
}

int		compare_strx_64(char *stringtable, struct nlist_64 *array,
	uint32_t increment)
{
	if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
		stringtable + array[increment + 1].n_un.n_strx) == 0 &&
		array[increment].n_value != 0 && array[increment + 1].n_value != 0)
		return (1);
	return (0);
}

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
