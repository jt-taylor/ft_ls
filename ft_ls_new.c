/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:55:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/05 22:20:39 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		ft_bzero(dir->last_file->next, sizeof(t_ft_ls_info));
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