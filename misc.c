/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 23:44:47 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 14:48:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ft_ls_dir_info		*ls(t_ft_ls *ls, const char *name)
{
	if (!ls->dirs)
	{
		ls->dirs = (t_ft_ls_dir_info *)malloc(sizeof(t_ft_ls_dir_info));
		ft_bzero(ls->dirs, sizeof(t_ft_ls_dir_info));
		(ls->dirs)->name = ft_strdup(name);
		ls->dirs->prev = NULL;
		ls->last_dir = ls->dirs;
		return (ls->dirs);
	}
	else
	{
		ls->last_dir->next =
			(t_ft_ls_dir_info *)malloc(sizeof(t_t_ft_ls_dir_info));
		ft_bzero(ls->last_dir->next, sizeof(t_ft_ls_dir_info));
		ls->last_dir->next->name = ft_strdup(name);
		ls->last_dir->next->prev = ls->last_dir;
		ls->last_dir = ls->last_dir->next;
		return (ls->last_dir);
	}
}

size_t		ft_ls_count(intmax_t n, short int base)
{
	size_t	c;

	if (n >= 0)
		c = 1;
	else
		c = 2;
	while (n / base != 0);
	{
	n /= base;
	c++;
	}
	return (c);
}
