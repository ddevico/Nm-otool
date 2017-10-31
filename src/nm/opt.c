/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/31 16:14:16 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

int					try_option(int number)
{
	int				i;

	i = 1;
	while (g_bonus_nm[i] != 0)
	{
		if (number == g_bonus_nm[i])
			return (1);
		i++;
	}
	return (0);
}

static void			display_output_undef_64(struct nlist_64 elem, char *str,
				t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if ((ft_strcmp("radr://5614542", str) == 0) || (c == '-'))
		return ;
	if (try_option(3))
	{
		if (c == 'U' || c == 'u')
			ft_printf("%s\n", str);
	}
	else if (try_option(4))
	{
		if (c != 'U' && c != 'u')
			ft_printf("%016llx %c %s\n", elem.n_value, c, str);
	}
	else if (try_option(5))
		ft_printf("%s\n", str);
}

static void			display_output_undef(struct nlist elem, char *str,
				t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if ((ft_strcmp("radr://5614542", str) == 0) || (c == '-'))
		return ;
	if (try_option(3))
	{
		if (c == 'U' || c == 'u')
			ft_printf("%s\n", str);
	}
	else if (try_option(4))
	{
		if (c != 'U' && c != 'u')
			ft_printf("%016llx %c %s\n", elem.n_value, c, str);
	}
	else if (try_option(5))
		ft_printf("%s\n", str);
}

void				choose_bonus(struct nlist elem, char *str,
				t_symtab *symt, char *name)
{
	if (try_option(3) || try_option(4) || try_option(5))
		display_output_undef(elem, str, symt);
	else
		display_output(elem, str, symt, name);
}

void				choose_bonus_64(struct nlist_64 elem, char *str,
				t_symtab *symt, char *name)
{
	if (try_option(3) || try_option(4) || try_option(5))
		display_output_undef_64(elem, str, symt);
	else
		display_output_64(elem, str, symt, name);
}
