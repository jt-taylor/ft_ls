/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:36:12 by jtaylor           #+#    #+#             */
/*   Updated: 2019/04/24 16:07:34 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **argv)
{
	t_ft_ls		*ls;
	int			i;

	i = 0;
	if (!(ls = (t_ft_ls *)malloc(sizeof(t_ft_ls))))
		return (FT_MALLOC_ERROR_CODE);
	ft_bzero(ls, sizeof(t_ft_ls));
	ls->
}
