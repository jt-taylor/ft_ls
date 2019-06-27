/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:36:12 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/27 12:00:42 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	ft_ls_work(t_ls *ls, t_dir_info *dirt)
{
	if (dirt->head)
		ft_ls_sort_lists(ls, dirt);
	if (dirt->close)
		ft_ls_error(dirt->name, 1);
	else if (ls->flag & FLAG_LO_L && dirt->head)
		ft_printf("total %d\n", dirt->total);
	if (dirt->head && ls->flag & FLAG_LO_L && ls->flag & FLAG_LO_R)
		ft_ls_print_long(dirt->last_file, ls, dirt);
	else if (ls->flag & FLAG_LO_R && ls->flag & FLAG_LO_L)
		ft_ls_print_long(dirt->head, ls, dirt);
	else
		ft_ls_print_simple(dirt, ls->flag);
}

static inline void	dir_info(t_ls *ls, t_dir_info *dirt)
{
	t_file_info	*file;
	t_dir_info	*dir;

	if (&ls->dirs->name != &dirt->name)
		ft_printf("%s:\n", dirt->name);
	ft_ls_work(ls, dirt);
	file = (ls->flag & FLAG_LO_R) ? dirt->last_file : dirt->head;
	while (file)
	{
		if (file->mode[0] == 'd' && ft_strcmp(file->name_file, ".") != 0 &&
				ft_strcmp(file->name_file, "..") != 0)
		{
			ft_ls_read_dir_info(ls, file->pwd);
			dir = ls->last_dir;
			write(1, "\n", 1);
			dir_info(ls, dir);
		}
		file = (ls->flag & FLAG_LO_R) ? file->prev : file->next;
	}
}

void	ft_ls_recursion(t_ls *ls, t_dir_info *dir)
{
	t_dir_info	*tmp;

	tmp = ls->last_dir;
	while (dir)
	{
		dir_info(ls, dir);
		if (&tmp->name == &dir->name)
			break ;
		write(1, "\n", 1);
		dir = dir->next;
		//
		ft_printf("is going through dir");
	}
	//
	ft_printf("made it into recursion\n");
}
