/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/26 16:54:32 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

void			display_output_otool(long unsigned int addr, unsigned int size, char *ptr)
{
	unsigned int	i;
	char			*str;

	i = 0;
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
		if ((i + 1) % 16 == 0)
      ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

static void						print_output_64(\
					struct segment_command_64 *seg, struct mach_header_64 *mo)
{
  struct section_64			*sect;
	unsigned int				i;

	i = 0;
  sect = (struct section_64 *)((void *)seg + sizeof(*seg));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sect->sectname, "__text") && !ft_strcmp(sect->segname, "__TEXT"))
		{
			ft_printf("Contents of (__TEXT,__text) section\n");
			display_output_otool(sect->addr, sect->size, (char *)mo + sect->offset);
		}
		sect = (struct section_64*)((void*)sect + sizeof(struct section_64));
		i++;
	}
}

void			handle_64_otool(void *ptr)
{
  unsigned int				i;
  struct mach_header_64		*header;
	struct load_command			*lc;
  struct segment_command_64	*seg;

	i = 0;
  header = ptr;
	lc = ptr + sizeof(struct mach_header_64);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
    {
    	seg = (struct segment_command_64*)lc;
      print_output_64(seg, header);
    }
    lc = (void *)lc + lc->cmdsize;
	}
}
