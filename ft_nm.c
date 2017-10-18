#include "libft/includes/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <stdlib.h>

#define ERROR(name)                                                                   \
    ft_putstr(ft_strjoin(ft_strjoin("nm: ", name), " No such file or directory.\n")); \
    return (-1)


struct nlist_64     *fill_array(struct nlist_64 *tab, int taille)
{
    struct nlist_64 *tab2;
    int             i;

    tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * taille);
    i = 4;
    while (i < taille)
    {
        tab2[i] = tab[i];
        i++;
    }
    return (tab2);
}

struct nlist_64     *tri_bulle(char *stringtable, struct nlist_64 *tab, int taille)
{
    struct nlist_64 *tab2;
    struct nlist_64 temp;
    int i;
    int j;

    i = 0;
    tab2 = fill_array(tab, taille);
    while (i < taille - 4)
    {
        j = 0;
        while(j < taille - 4)
        {
            if (ft_strcmp(stringtable + tab2[i].n_un.n_strx,
                stringtable + tab2[j].n_un.n_strx) < 0)
            {
                temp = tab2[i];
                tab2[i] = (struct nlist_64)tab2[j];
                tab2[j] = temp;
            }
            j++;
        }
        i++;
    }
    return (tab2);
}

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
    int i = 0;
    char *stringtable;
    struct nlist_64 *array;

    array = (void *)ptr + symoff;
    stringtable = (void *)ptr + stroff;
    i = 0;
    array = tri_bulle(stringtable, array, nsyms);
    ft_putstr(stringtable + array[1].n_un.n_strx);
    ft_putstr("\n\n");
    while (i < nsyms)
    {
        // ft_putnbr(array[i].n_value);
        // ft_putnbr(array[i].n_type);
        // ft_putstr(ft_itoa_base(symoff + array[i].n_un.n_strx, 16));
        // ft_putstr("    ");
        if (array[i].n_un.n_strx[0])
        {
            if (array[i].n_value == 0)
              ft_printf("                 U ");
            else
              ft_printf("00000001%08x T ", array[i].n_value);
            ft_putstr(stringtable + array[i].n_un.n_strx);
            ft_putchar('\n');
        }
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
