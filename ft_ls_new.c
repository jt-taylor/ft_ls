/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:55:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/12 14:03:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		this creates a new element in the dir list
*/

t_ft_ls_dir					*ft_ls_new_dir_elem(t_ft_ls *ls, const char *name)
{
	if (!ls->dirs)
	{
		ls->dirs = (t_ft_ls_dir *)malloc(sizeof(t_ft_ls_dir));
		ft_bzero(ls->dirs, (sizeof(t_ft_ls_dir)));
		ls->dirs->name = ft_strdup(name);
		ls->dirs->prev = NULL;
		ls->last_dir = ls->dirs;
		return (ls->dirs);
	}
	else
	{
		ls->last_dir->next = (t_ft_ls_dir *)malloc(sizeof(t_ft_ls_dir));
		ft_bzero(ls->last_dir->next, sizeof(t_ft_ls_dir));
		ls->last_dir->next->name = ft_strdup(name);
		ls->last_dir->next->prev = ls->last_dir;
		ls->last_dir = ls->last_dir->next;
		return (ls->last_dir);
	}
}

/*
** mabey this should be two seperate functions ?
**
** if it is the head of the linked list it allocates the memory and sets 
** 		->last_file = ->head
** 		->last_file->prev = NULL
** otherwise it is just a element in the linked list so it allocates memory for
** 	the next link in the chain and moves to the new ->last_file
*/

t_ft_ls_info				*ft_ls_new_file_elem(t_ft_ls_dir *dir)
{
	if (!dir->head)
	{
		dir->head = (t_ft_ls_info *)malloc(sizeof(t_ft_ls_info));
		ft_bzero(dir->head, sizeof(t_ft_ls_info));
		dir->last_file = dir->head;
		dir->last_file->prev = NULL;
		return (dir->head);
	}
	else
	{
		dir->last_file->next = (t_ft_ls_info *)malloc(sizeof(t_ft_ls_info));
		ft_bzero(dir->last_file->next, sizeof(t_ft_ls_info));
		dir->last_file->next->prev = dir->last_file;
		dir->last_file = dir->last_file->next;
		return (dir->last_file);
	}
}
