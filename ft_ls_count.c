/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:56:08 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 10:58:17 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	ft_ls_count(intmax_t n, short int base)
{
	size_t	c;

	if (n >= 0)
		c = 1;
	else
		c = 2;
	while (n / base != 0)
	{
		n /= base;
		c++;
	}
	return (c);
}
