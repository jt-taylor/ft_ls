/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 13:11:54 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 14:48:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ft_ls_dir_info	*ft_ls_new_dir(t_ft_ls *ls, const char *name)
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
		ls->last_dir->next = (t_ft_ls_dir_info *)malloc(sizeof(t_ft_ls_dir_info));
		ft_bzero(ls->last_dir->next, sizeof(t_ft_ls_dir_info));
		ls->last_dir->next->name = ft_strdup(name);
		ls->last_dir->next->prev = ls->last_dir;
		ls->last_dir = ls->last_dir->next;
		return (ls->last_dir);
	}
}

t_info		*ft_ls_new_file(t_ft_ls_dir_info *dir)
{
	if (!dir->head)
	{
		if (!(dir->head = (t_ft_ls_base_info *)malloc(sizeof(t_ft_ls_dir))))
			exit(EXIT_FAILURE);
		ft_bzero(dir->head, sizeof(t_ft_ls_base_info));
		dir->last_file = dir->head;
		dir->last_file->prev = NULL;
		return (dir->head);
	}
	else
	{
		if (!(dir->head = (t_ft_ls_base_info *)malloc(sizeof(t_ft_ls_base_info))))
			exit(EXIT_FAILURE);
		ft_bzero(dir->last_file->next, sizeof(t_ft_ls_base_info));
		dir->last_file->next->prev = dir->last_file;
		dir->last_file = dir->last_file->next;
		return (dir->last_file);
	}
}


