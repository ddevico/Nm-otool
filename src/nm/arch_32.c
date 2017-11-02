/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/02 12:00:49 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void					sort_duplicate_strx_by_value(struct nlist *array,
							char *stringtable, uint32_t size)
{
	struct nlist			tmp_value;
	int						sorted;
	uint32_t				increment;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (compare_strx(stringtable, array, increment))
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1];
					array[increment + 1] = array[increment];
					array[increment] = tmp_value;
					sorted = 0;
				}
			}
			++increment;
		}
	}
}

static void					symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect)
{
	uint32_t				i;

	i = 0;
	while (i < seg->nsects)
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
		i++;
	}
}

void						symtab_building(t_symtab *symt,
							struct mach_header *header, struct load_command *lc)
{
	uint32_t				i;
	struct segment_command	*seg;
	struct section			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void					print_output(struct symtab_command *sym,
							struct mach_header *header, char *ptr, char *name)
{
	unsigned int			i;
	struct load_command		*lc;
	char					*stringtable;
	struct nlist			*array;
	t_symtab				symt;

	symt = init_symtab();
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if (!verif((void *)array) || !verif((void *)lc)
		|| !verif((void *)stringtable))
	{
		file_broken();
		return ;
	}
	if (!try_option(2))
		array = tri_bulle_alpha(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value(array, stringtable, sym->nsyms);
	symtab_building(&symt, header, lc);
	while (++i < sym->nsyms)
		choose_bonus(array[i], stringtable + array[i].n_un.n_strx,
		&symt, name);
}

void						handle_32(char *ptr, char *name)
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
			print_output(sym, header, ptr, name);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
