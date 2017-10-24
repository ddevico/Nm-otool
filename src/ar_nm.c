/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/24 14:36:24 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

void				ar_nm(char *ptr, char *name)
{
    struct ar_hdr	*ar;
    struct ranlib	*rlib;
    int		size;
	char	*word;
    int i;

    ar = (void*)ptr + SARMAG;
    i = 0;
    size = ft_atoi((void *)ar + sizeof(AR_EFMT1) - 1);
    rlib = (void *)ar + sizeof(struct ar_hdr) + size + sizeof(uint32_t);
    //i++;
}
