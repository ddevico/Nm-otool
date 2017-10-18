/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:15 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/18 15:52:24 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_TOOL_H
# define NM_TOOL_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

typedef struct				s_section
{
	char					*name;
	unsigned int			nb;
	struct s_section		*next;
}							t_section;

typedef struct				s_lsection
{
	t_section				*first;
	t_section				*last;
}							t_lsection;

struct nlist_64     *tri_bulle(char *stringtable, struct nlist_64 *tab,
                    int taille);
int                 ft_printf(const char *str, ...);

#endif
