/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/26 10:07:28 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

t_symtab		init_symtab(t_symtab symt)
{
	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.i = -1;
	symt.j = 0;
	symt.ns = 1;
	symt.exec = 0;
	return (symt);
}

int				print_error(char *file, char *str)
{
	ft_printf("ft_nm: %s: %s.\n", file, str);
	return (0);
}

void			nm(char *ptr, char *name)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, name);
	else
		ft_printf("Fichier non gere: \n%s\n", ptr);
}
