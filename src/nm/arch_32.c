/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/25 20:33:18 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void		symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect)
{
	symt->i = 0;
	while (symt->i < seg->nsects)
	{
		if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sect->segname, SEG_TEXT) == 0)
			symt->text = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->data = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_BSS) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->bss = symt->ns;
		sect = (void *)sect + sizeof(*sect);
		symt->ns++;
		symt->i++;
	}
}

static void			symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc)
{
	struct segment_command	*seg;
	struct section			*sect;

	while (symt->j < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		symt->j++;
	}
}

static void			print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr)
{
	int					i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist		*array;
	t_symtab			symt;

	symt = init_symtab(symt);
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	array = tri_bulle_alpha(stringtable, array, sym->nsyms);
	symtab_building(&symt, header, lc);
	while (++i < sym->nsyms)
		display_output(array[i], stringtable + array[i].n_un.n_strx, &symt);
}

void			handle_32(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
