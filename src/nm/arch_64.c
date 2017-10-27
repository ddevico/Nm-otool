/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 10:44:10 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void		sort_duplicate_strx_by_value_64(struct nlist_64 *array,
	char *stringtable, uint32_t size)
{
	uint64_t		tmp_value;
	int				sorted;
	int				increment;

	sorted = 0;
	tmp_value = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = -1;
		while ((uint32_t)++increment < size - 1)
		{
			if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
				stringtable + array[increment + 1].n_un.n_strx) == 0)
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			}
		}
	}
}

static void		symtab_building_bis_64(t_symtab *symt,
	struct segment_command_64 *seg, struct section_64 *sect)
{
	symt->i = 0;
	while ((uint32_t)symt->i < seg->nsects)
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

static void			symtab_building_64(t_symtab *symt,
	struct mach_header_64 *header, struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sect;

	while ((uint32_t)symt->j < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((void *)seg + sizeof(*seg));
			symtab_building_bis_64(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		symt->j++;
	}
}

static void			print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr)
{
	uint32_t					i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist_64		*array;
	t_symtab			symt;

	symt = init_symtab(symt);
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	array = tri_bulle_64_alpha(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value_64(array, stringtable, sym->nsyms);
	symtab_building_64(&symt, header, lc);
	while (++i < sym->nsyms)
		display_output_64(array[i], stringtable + array[i].n_un.n_strx, &symt);
}

void			handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
