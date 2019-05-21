/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 16:54:06 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/20 22:59:48 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this goes to the printing function according to the flags for a directory
*/
static inline void	ls_dir_inside(t_ft_ls *ls, t_ft_ls_dir *direct)
{
	if (direct->head)
		ft_ls_sort_list_elem(ls, direct);
	if (direct->close)
		ft_error(direct->name, 1);
	else if ((ls->flag & FLAG_N || ls->flag & FLAG_L) && direct->head)
		ft_printf("total %d\n", direct->total);
	if (direct->head && ls->flag & FLAG_R && (ls->flag & FLAG_N ||
				ls->flag & FLAG_L))
		ft_ls_print_ln(direct->last_file, ls, direct);
	else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
		ft_ls_print_ln(direct->head, ls, direct);
	else
		ft_ls_print_just(direct, ls->flag);
}

/*
** this handles the recursion for the dir
** will call itself as long as 
*/

static inline void	ls_dir_info(t_ft_ls *ls, t_ft_ls_dir *direct)
{
	t_ft_ls_info	*file;
	t_ft_ls_dir		*dir;

	if (&ls->dirs->name != &direct->name)
		ft_printf("%s:\n", direct->name);
	ls_dir_inside(ls, direct);
	file = (ls->flag & FLAG_R) ? direct->last_file : direct->head;
	while (file)
	{
		if (file->mode[0] == 'd' && ft_strcmp(file->name_file, ".") != 0
				&& ft_strcmp(file->name_file, "..") != 0)
		{
			ft_ls_read_dir_info(ls, file->pwd);
			dir = ls->last_dir;
			write(1, "\n", 1);
			ls_dir_info(ls, dir);
		}
		file = (ls->flag & FLAG_R) ? file->prev : file->next;
	}
}

/*
**	this is the "recursion" function for the directories
*/

void		ft_ls_recursion(t_ft_ls *ls, t_ft_ls_dir *dir)
{
	t_ft_ls_dir	*last;

	last = ls->last_dir;
	while (dir)
	{
		ls_dir_info(ls, dir);
		if (&last->name == &dir->name)
			break;
		write(1, "\n", 1);
		dir = dir->next;
	}
}
