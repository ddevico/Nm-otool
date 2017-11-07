/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/07 08:52:49 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static void			option(void)
{
	ft_printf("Option:\n");
	ft_printf("    -d    Precede each symbol by the name of the input file.\n");
}

static int			loop_arg(char *av)
{
	struct stat		buf;
	int				fd;
	void			*ptr;
	unsigned int	magic_number;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_MAGIC)
		ft_printf("%s:\n", av);
	otool(ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
	return (0);
}

int					main(int ac, char **av)
{
	int				i;

	i = 0;
	if (ac > 1)
	{
		if (av[1][0] == '-' && ft_strcmp(av[1], "-d"))
		{
			option();
			return (0);
		}
		if (ft_strcmp(av[1], "-d") == 0)
		{
			g_bonus_otool = 1;
			i++;
		}
		else
			g_bonus_otool = 0;
		while (av[++i])
			loop_arg(av[i]);
	}
	else
		print_error("[-d]", "<file .o / .a>");
	return (0);
}
