/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/30 16:32:48 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

void			display_output_otool(long unsigned int addr, unsigned int size,
	char *ptr, char *section)
{
	unsigned int	i;
	char			*str;

	i = 0;
	ft_printf("%s\n", section);
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%016llx\t", addr);
		}
		str = ft_itoa_base(ptr[i], 16, 2);
		ft_printf("%s ", str);
		free(str);
		if ((i + 1) % 16 == 0 && i + 1 < size)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}
