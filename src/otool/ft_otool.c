/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/25 21:05:27 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

int				print_error(char *file, char *str)
{
	ft_printf("ft_nm: %s: %s.\n", file, str);
	return (0);
}

void			otool(void *ptr, char *name)
{
	struct mach_header_64		*mach;
	struct load_command			*lc;
	unsigned int magic_number;

	mach = ptr;
	lc = ptr + sizeof(struct mach_header_64);
	magic_number = *(int *)ptr;
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib_otool(ptr, name);
}

static int				loop_arg(char *av)
{
	struct stat	buf;
	int			fd;
	void		*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	g_stat = buf;
	otool(ptr, av);
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
	if (ac < 2)
		ft_printf("Bad argument\n");
	while (i < ac)
	{
		ft_printf("Archive: %s\n", av[i]);
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
