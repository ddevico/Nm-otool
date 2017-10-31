/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/31 14:39:03 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static uint32_t				swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

void						handle_fat(char *ptr, char *name)
{
	struct fat_header		*fat_header;
	struct fat_arch			*arch;
	struct mach_header64 	*header;
	uint32_t				offset;
	uint32_t				i;

	fat_header = (struct fat_header *)ptr;
	arch = (void*)fat_header + sizeof(*fat_header);
	offset = swap_uint32(arch->offset);
	i = 0;
	while (i < swap_uint32(fat_header->nfat_arch))
	{
		offset = swap_uint32(arch->offset);
		header = (void*)ptr + offset;
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			break;
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	nm((void *)header, name);
}
