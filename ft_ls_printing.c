/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:42:58 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/25 16:45:17 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** more overhead for non recusive stuff
*/

/*
** so this should take the ls structure that contains the linked list of the
** directory (which hold linked lists for the files in them)
** and should handle the overhead for all of it
*/
void		ft_ls_printing(t_ls *ls)
{
	//print the errorfiles && (?) newline
	//
	//if 'R' flag go into the recursion
	//
	//otherwise print according to the 'r' flag
	//this section is just testing that the struct exists
	if (ls)
		printf("struct exists\n");
	if (ls->files)
		printf("ls->files\n");
	if (ls->dirs)
		printf("ls->dirs\n");
	if (ls->last_dir)
		printf("ls->last_dir\n");
	//
}
