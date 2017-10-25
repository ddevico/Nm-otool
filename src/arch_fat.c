/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/25 17:12:18 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static uint32_t			swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

void					handle_fat(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	int					magic_number;
	uint32_t			number;
	uint32_t			offset;

	fat = (void *)ptr;
	magic_number = *(int *)ptr;
	number = swap_uint32(fat->nfat_arch);
	arch = (void*)ptr + sizeof(fat);
	while (number)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		number--;
	}
	nm(ptr + swap_uint32(offset), NULL);
}
