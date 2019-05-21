/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:45:22 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/20 22:56:02 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this prints in long format each file elem in the directory
** checks for the 'n' flag for numeric group user id
** checks if the element is a block / charector special file
*/

void		ft_ls_print_ln(t_ft_ls_info *info, t_ft_ls *ls, t_ft_ls_dir *dir)
{
	while (info)
	{
		if (!info->fail)
		{
			if (ls->flag & FLAG_N)
				ft_printf("%s %*d %-5d %-5d %*d %-12.12s", info->mode,
				dir->s_link, info->nlinks, info->uid, info->gid, dir->s_size,
				info->size, &info->data[4], info->name_file);
			else if (info->mode[0] == 'c' || info->mode[0] == 'b')
				ft_printf("%s %d %-*s %-*s %3d, %3d %-12.12s", info->mode,
				dir->s_link, info->nlinks, dir->s_name, info->name_user,
				dir->s_group, info->name_group, major(info->rdev),
				minor(info->rdev), &info->data[4]);
			else
				ft_printf("%s %*d %-s %-s %*d %-12.12s", info->mode,
				dir->s_link, info->nlinks, dir->s_name, info->name_user,
				dir->s_group, info->name_group, dir->s_size, info->size,
				&info->data[4]);
			ft_printf("%s\n", info->name_file);
		}
		info = (ls->flag & FLAG_R) ? info->prev : info->next;
	}
}

void				ft_ls_print_just(t_ft_ls_dir *dir, char flag)
{
	t_ft_ls_info	*tmp;

	tmp = (flag & FLAG_R) ? dir->last_file : dir->head;
	while (tmp)
	{
		if (!tmp->fail)
			ft_printf("%s\n", tmp->name_file);
		tmp = (flag & FLAG_R) ? tmp->prev : tmp->next;
	}
}

static inline void	ft_ls_out_errnfiles(t_ft_ls *ls, t_ft_ls_info *info,
		int *files)
{
	t_ft_ls_info	*tmp;
	tmp = info;
	while (tmp)
	{
		if (tmp->fail)
			ft_error(tmp->name_file, 0);
		else if (tmp->mode[0] == 'd' && !(ls->flag & FLAG_D))
			tmp->fail = 1;
		else
			*files = 1;
		tmp = tmp->next;
	}
	if ((ls->flag & FLAG_N || ls->flag & FLAG_L) && ls->flag & FLAG_R)
		ft_ls_print_ln(ls->files->last_file, ls, ls->files);
	else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
		ft_ls_print_ln(info, ls, ls->files);
	else
		ft_ls_print_just(ls->files, ls->flag);
}

void		ft_ls_output_handle(t_ft_ls *ls, t_ft_ls_dir *dir,
		t_ft_ls_dir **next)
{
	while (dir)
	{
		if (dir->head)
			ft_ls_sort_list_elem(ls, dir);
		if (*next)
			ft_printf("%s:\n", dir->name);
		if (dir->close)
			ft_error(dir->name, 1);
		else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
			ft_printf("total: %d\n", dir->total);
		if (dir->head && ls->flag & FLAG_R &&
				(ls->flag & FLAG_N || ls->flag & FLAG_L))
			ft_ls_print_ln(dir->last_file, ls, dir);
		else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
			ft_ls_print_ln(dir->head, ls, dir);
		else
			ft_ls_print_just(dir, ls->flag);
		(dir->prev && ls->flag & FLAG_R) ? write(1, "\n", 1) : 0;
		(dir->next && !(ls->flag & FLAG_R)) ? write(1, "\n", 1) : 0;
		dir = (ls->flag & FLAG_R) ? dir->prev : dir->next;
	}
}

void		ft_ls_printing(t_ft_ls *ls)
{
	int		files;

	files = 0;
	if (ls->files->head)
		ft_ls_out_errnfiles(ls, ls->files->head, &files);
	if (ls->files->head && files && ls->dirs)
		write(1, "\n", 1);
	if (ls->flag & FLAG_UP_R)
		ft_ls_recursion(ls, ls->dirs);
	else if (ls->flag & FLAG_R)
		ft_ls_output_handle(ls, ls->last_dir, &ls->last_dir->prev);
	else
		ft_ls_output_handle(ls, ls->dirs, &ls->dirs->next);
}
