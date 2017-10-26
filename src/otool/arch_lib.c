/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/25 21:06:30 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void			print_ar_tool(uint32_t off, char *ptr, char *file)
{
	int				size;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = get_name(arch->ar_name);
	size = get_size(arch->ar_name);
	ft_putchar('\n');
	ft_putstr(file);
	ft_putchar('(');
	ft_putstr(name);
	ft_putchar(')');
	ft_putstr(":\n");
	//do_otool((void*)arch + sizeof(*arch) + size, file);
}

static void				print_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist		*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar_tool(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}

void			handle_lib_otool(char *ptr, char *name)
{
	struct ranlib	*ran;
	t_offlist		*lst;
	int				i;
	int				size;
	char			*offset_struct;

	lst = NULL;
	i = get_size((void*)ptr + SARMAG);
	offset_struct = (void*)ptr + sizeof(struct ar_hdr) + SARMAG + i;
	ran = (void*)ptr + sizeof(struct ar_hdr) + SARMAG + i + sizeof(uint32_t);
	size = (*((int *)offset_struct)) / sizeof(struct ranlib);
	i = -1;
	while (++i < size)
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
	print_ar(order_off(lst), ptr, name);
}
