/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:25:22 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/27 14:30:28 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_atoi_loop(const char *str, int i)
{
	int		compt;

	compt = 0;
	while (ft_isdigit(str[i]))
	{
		compt = compt * 10;
		compt = compt + str[i] - '0';
		i++;
	}
	return (compt);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		compt;
	int		min;

	i = 0;
	compt = 0;
	min = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 14))
		i++;
	if (str[i] == '-')
	{
		i++;
		min++;
	}
	else if (str[i] == '+')
		i++;
	compt = ft_atoi_loop(str, i);
	if (min > 0)
		return (-compt);
	return (compt);
}
