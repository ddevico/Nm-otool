/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/30 10:21:22 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/nm_otool.h"

static int				ft_count_opt(char **av)
{
	int					i;
	int					cpt;

	i = 0;
	cpt = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			cpt++;
		i++;
	}
	return (cpt);
}

static void				ft_help(void)
{
	ft_printf("    -A    Precede each symbol by the name of the input file.\n");
	ft_printf("    -p    Don't sort; display in symbol-table order.\n");
	ft_printf("    -u    Display only undefined symbols.\n");
	ft_printf("    -U    Don't display undefined symbols.\n");
	ft_printf("    -j    Just display the symbol names (no value or type).\n");
}

static int				option(char **av, int i)
{
	if (ft_strcmp(av[i], "-h") == 0 && !g_icount)
	{
		ft_help();
		return (1);
	}
	else if (ft_strcmp(av[i], "-A") == 0 && g_icount != ft_count_opt(av))
		g_bonus_nm[++g_icount] = 1;
	else if (ft_strcmp(av[i], "-p") == 0 && g_icount != ft_count_opt(av))
		g_bonus_nm[++g_icount] = 2;
	else if (ft_strcmp(av[i], "-u") == 0 && g_icount != ft_count_opt(av))
		g_bonus_nm[++g_icount] = 3;
	else if (ft_strcmp(av[i], "-U") == 0 && g_icount != ft_count_opt(av))
		g_bonus_nm[++g_icount] = 4;
	else if (ft_strcmp(av[i], "-j") == 0 && g_icount != ft_count_opt(av))
		g_bonus_nm[++g_icount] = 5;
	else
	{
		ft_help();
		return (1);
	}
	return (0);
}

static int				loop_arg(char *av)
{
	struct stat			buf;
	int					fd;
	char				*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	nm(ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
	return (0);
}

int						main(int ac, char **av)
{
	int					i;
	char				*str;

	i = 1;
	str = NULL;
	g_icount = 0;
	if (ac == 1)
		loop_arg("a.out");
	while (i < ac)
	{
		while (av[i][0] == '-' && g_icount != ft_count_opt(av))
		{
			if (option(av, i))
				return (0);
			i++;
		}
		if (ac - ft_count_opt(av) > 2 && ft_strcmp(av[1], "-A"))
			ft_printf("\n%s:\n", av[i]);
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
