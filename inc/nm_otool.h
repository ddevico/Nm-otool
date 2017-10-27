/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:55 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/26 16:01:56 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

struct stat				g_stat;
int						g_data;
int						g_bss;
int						g_text;

typedef struct			s_symtab
{
	int					data;
	int					bss;
	int					text;
	int					i;
	int					j;
	int					ns;
	int					exec;
}						t_symtab;

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

int						ft_printf(const char *str, ...);

/*
** NM
*/

t_symtab				init_symtab(t_symtab symt);
int						print_error(char *file, char *str);
void					nm(char *ptr, char *av);
void					display_output(struct nlist elem, char *str,
	t_symtab *symt);
void					display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt);
struct nlist			*tri_bulle_alpha(char *stringtable, struct nlist *tab,
	int nsyms);
struct nlist_64			*tri_bulle_64_alpha(char *stringtable,
		struct nlist_64 *tab, int nsyms);
t_offlist				*order_off(t_offlist *lst);
void					handle_64(char *ptr);
void					handle_32(char *ptr);
int					get_size(char *name);
char					*get_name(char *name);
t_offlist		*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
void					handle_lib(char *ptr, char *name);
int						search_lst(t_offlist *lst, uint32_t off);
void					handle_fat(char *ptr);

/*
** OTOOL
*/

void 					otool(void *ptr, char *name);
void					handle_lib_otool(char *ptr, char *name);
void					handle_fat_otool(char *ptr);
void					handle_64_otool(void *ptr);



#endif
