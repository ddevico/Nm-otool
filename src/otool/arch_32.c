/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/07 09:38:22 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void						print_output_32(\
					struct segment_command *seg, struct mach_header *header)
{
	struct section				*sect;
	unsigned int				i;

	i = 0;
	sect = (struct section *)((void *)seg + sizeof(*seg));
	while (++i < seg->nsects)
	{
		if (g_bonus_otool == 0)
		{
			if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sect->segname, SEG_TEXT) == 0)
			{
				display_output_otool(sect->addr, sect->size, (char *)header
				+ sect->offset, "Contents of (__TEXT,__text) section");
			}
		}
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
		{
			display_output_otool(sect->addr, sect->size,
				(char *)header + sect->offset,
				"Contents of (__DATA,__data) section");
		}
		sect = (struct section*)((void*)sect + sizeof(struct section));
	}
}

void							handle_32_otool(void *ptr)
{
	unsigned int				i;
	struct mach_header			*header;
	struct load_command			*lc;
	struct segment_command		*seg;

	i = 0;
	header = ptr;
	lc = ptr + sizeof(struct mach_header);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			print_output_32(seg, header);
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
