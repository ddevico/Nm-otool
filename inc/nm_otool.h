/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:55 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/24 13:09:17 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <ar.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

struct stat			g_stat;
int					g_data;
int					g_bss;
int					g_text;

typedef struct		s_symtab
{
	int				data;
	int				bss;
	int				text;
	int				i;
	int				j;
	int				ns;
	int				exec;
}					t_symtab;

int					ft_printf(const char *str, ...);

/*
** NM
*/

t_symtab			init_symtab(t_symtab symt);
int					print_error(char *file, char *str);
void				nm(char *ptr, char *av);
int					loop_arg(char *av);

/*
** DISPLAY
*/

int					is_executable_file(void);
char				type_n_sect(unsigned int n_sect, t_symtab *symt);
char				get_type(uint32_t type, uint32_t n_sect, int value,
	t_symtab *symt);
void				display_output(struct nlist elem, char *str,
	t_symtab *symt);
void				display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt);

/*
** SORT
*/

struct nlist		*fill_array(struct nlist *tab, int nsyms,
	char *stringtable);
struct nlist		*tri_bulle(char *stringtable, struct nlist *tab,
	int nsyms);
struct nlist_64		*fill_array_64(struct nlist_64 *tab, int nsyms,
	char *stringtable);
struct nlist_64		*tri_bulle_64(char *stringtable, struct nlist_64 *tab,
	int nsyms);

/*
** ARCH_64
*/

static void			symtab_building_bis_64(t_symtab *symt,
	struct segment_command_64 *seg, struct section_64 *sect);
void				symtab_building_64(t_symtab *symt,
	struct mach_header_64 *header, struct load_command *lc);
void				print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr);
void				handle_64(char *ptr);

/*
** ARCH_32
*/

static void			symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect);
void				symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc);
void				print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr);
void				handle_32(char *ptr);

/*
** ARCH_32
*/

void				ar_nm(char *ptr, char *name);

#endif
