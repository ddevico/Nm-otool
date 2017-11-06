/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/06 12:34:59 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

void			otool(void *ptr, char *name)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64_otool(ptr);
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		ft_printf("%s:\n", name);
		handle_fat_otool(ptr);
	}
	else if (magic_number == MH_MAGIC)
		handle_32_otool(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		ft_printf("Archive : %s\n", name);
		handle_lib_otool(ptr, name);
	}
}
