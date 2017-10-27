/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 15:12:22 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void			display_output_otool(long unsigned int addr, unsigned int size, char *ptr)
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
      		ft_printf("%08llx\t", addr);
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

static void						print_output_32(\
					struct segment_command *seg, struct mach_header *mo)
{
  struct section			*sect;
	unsigned int				i;

	i = 0;
  sect = (struct section *)((void *)seg + sizeof(*seg));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sect->sectname, "__text") && !ft_strcmp(sect->segname, "__TEXT"))
		{
			ft_printf("Contents of (__TEXT,__text) section\n");
			display_output_otool(sect->addr, sect->size, (char *)mo + sect->offset);
		}
		sect = (struct section*)((void*)sect + sizeof(struct section));
		i++;
	}
}

void			handle_32_otool(void *ptr)
{
  unsigned int				i;
  struct mach_header		*header;
	struct load_command			*lc;
  struct segment_command	*seg;

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
