/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:15:23 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/18 13:37:23 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_tool.h"

#define ERROR(name)                                                                   \
    ft_putstr(ft_strjoin(ft_strjoin("nm: ", name), " No such file or directory.\n")); \
    return (-1)

char				type_n_sect(unsigned int n_sect)
{
    if (n_sect == 1)
        return ('T');
    if (n_sect == 2)
        return ('D');
    if (n_sect == 3)
        return ('B');
    return ('S');
}

char				type_element(uint32_t type, uint32_t n_sect, int addr)
{
    char car;

    car = '?';
	if ((type & N_TYPE) == N_UNDF)
    {
        if (addr)
            car = 'C';
        else
            car = 'U';
    }
	else if ((type & N_TYPE) == N_ABS)
		car = 'A';
    else if ((type & N_TYPE) == N_SECT)
        car = type_n_sect(n_sect);
	else if ((type & N_TYPE) == N_PBUD)
		car = 'U';
	else if ((type & N_TYPE) == N_INDR)
		car = 'I';
    if (!(type & N_EXT) && car != '?')
        car = ft_tolower(car);
	return (car);
}

void                display_out(int value, char *str, char type)
{
    if (value == 0)
		ft_putstr("                ");
	else
    {
        //ft_putstr(ft_itohex(value, 16));
        ft_putstr("000000010000");
        ft_putstr(ft_itoa_base(value, 16));
    }
	ft_putstr(" ");
	ft_putchar(type);
	ft_putstr(" ");
	ft_putendl(str);
    ft_printf("");
}

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
    int i = 0;
    char car;
    char *stringtable;
    struct nlist_64 *array;

    array = (void *)ptr + symoff;
    stringtable = (void *)ptr + stroff;
    i = 0;
    array = tri_bulle(stringtable, array, nsyms);
    while (i < nsyms)
    {
        car = type_element(array[i].n_type, array[i].n_sect, array[i].n_value);
        display_out(array[i].n_value, stringtable + array[i].n_un.n_strx, car);
        i++;
    }
}

void handle_64(char *ptr)
{
    int ncmds;
    int i;
    struct mach_header_64 *header;
    struct load_command *lc;
    struct symtab_command *sym;

    //converti en header
    header = (struct mach_header_64 *)ptr;
    ncmds = header->ncmds;
    i = 0;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *)lc + lc->cmdsize;
        i++;
    }
}

void handle_32(char *ptr)
{
}

void nm(char *ptr)
{
    int magic_number;
    //on prend le premier octet que l'on convertit en int
    magic_number = *(int *)ptr;
    //regarder si 64bits
    if (magic_number == MH_MAGIC_64)
        handle_64(ptr);
    if (magic_number == MH_MAGIC)
        handle_32(ptr);
}

int main(int ac, char **av)
{
    int fd;
    void *ptr;
    struct stat buf;

    if (ac < 2)
        av[1] = "a.out\0";
    if ((fd = open(av[1], O_RDONLY)) != -1)
    {
        if (fstat(fd, &buf) < 0)
        {
            ERROR("ok");
        }
        if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        {
            ERROR("ok");
        }
        nm(ptr);
    }
    else
        ERROR(av[1]);
    return 0;
}
