/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 15:54:45 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static int				loop_arg(char *av)
{
	struct stat	buf;
	int			fd;
	void		*ptr;
	unsigned int magic_number;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	g_stat = buf;
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_MAGIC)
		ft_printf("%s:\n", av);
	otool(ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
	return (0);
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
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
