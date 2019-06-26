/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_list_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:45:42 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/25 15:14:21 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** these two functions create and add a element of their respective structure
** to their linked list;
*/

t_dir_info	*new_dir_elem(t_ls *ls, const char *name)
{
	if (!ls->dirs)
	{
		ls->dirs = (t_dir_info *)malloc(sizeof(t_dir_info));
		ft_bzero(ls->dirs, sizeof(t_dir_info));
		(ls->dirs)->name = ft_strdup(name);
		ls->dirs->prev = NULL;
		ls->last_dir = ls->dirs;
		return (ls->dirs);
	}
	else
	{
		ls->last_dir->next = (t_dir_info *)malloc(sizeof(t_dir_info));
		ft_bzero(ls->last_dir->next, sizeof(t_dir_info));
		ls->last_dir->next->name = ft_strdup(name);
		ls->last_dir->next->prev = ls->last_dir;
		ls->last_dir = ls->last_dir->next;
		return (ls->last_dir);
	}
}

t_file_info	*new_file_elem(t_dir_info *dir)
{
	if (!dir->head)
	{
		dir->head = (t_file_info *)malloc(sizeof(t_file_info));
		ft_bzero(dir->head, sizeof(t_file_info));
		dir->last_file = dir->head;
		dir->last_file->prev = NULL;
		return (dir->head);
	}
	else
	{
		dir->last_file->next = (t_file_info *)malloc(sizeof(t_file_info));
		ft_bzero(dir->last_file->next, sizeof(t_file_info));
		dir->last_file->next->prev = dir->last_file;
		dir->last_file = dir->last_file->next;
		return (dir->last_file);
	}
}
