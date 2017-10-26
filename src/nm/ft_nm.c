/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/25 21:03:20 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

t_symtab		init_symtab(t_symtab symt)
{
	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.i = -1;
	symt.j = 0;
	symt.ns = 1;
	symt.exec = 0;
	return (symt);
}

int				print_error(char *file, char *str)
{
	ft_printf("ft_nm: %s: %s.\n", file, str);
	return (0);
}

void			nm(char *ptr, char *name)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, name);
	else
		ft_printf("Fichier non gere: \n%s\n", ptr);
}

static int				loop_arg(char *av)
{
	struct stat	buf;
	int			fd;
	char		*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	g_stat = buf;
	nm(ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
	return (1);
}

int				main(int ac, char **av)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	if (ac == 1)
		loop_arg("a.out");
	while (i < ac)
	{
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
