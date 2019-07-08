/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:42:58 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/08 13:04:08 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this prints for anything witht the long option turned on
** major and minor are used to manage the device number
** charector and block special files have their own format
** otherwize ls -l treats them all withe the same format
*/
void	ft_ls_print_long(t_file_info *file, t_ls *ls, t_dir_info *dir)
{
	while (file)
	{
		if (file->failure)
		{
			file = (ls->flag & FLAG_LO_R) ? file->prev : file->next;
			continue ;
		}
		(file->mode[0] == 'c' || file->mode[0] == 'b') ? ft_printf("%s %*d %-*s\
				%-*s %3d, %3d %-12.12s", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, major(file->rdev),
				minor(file->rdev), &file->data[4]) : ft_printf("%s %*d %-*s\
				%-*s %*d %-12.12s", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, dir->s_size, file->size,
				&file->data[4]);
		ft_printf(" %s\n", file->name_file);
		file = (ls->flag & FLAG_LO_R) ? file->prev : file->next;
	}
}

/*
** this will print the non long format
*/
void		ft_ls_print_simple(t_dir_info *dir, char flag)
{
	t_file_info *tmp;

	tmp = (flag & FLAG_LO_R) ? dir->last_file : dir->head;
	//
	ft_printf("value of flag == %b\n", flag);
	while (tmp)
	{
		if (!tmp->failure)
			ft_printf("%s\n", tmp->name_file);
		tmp = (flag & FLAG_LO_R) ? tmp->prev : tmp->next;
		//
//		ft_printf("is looping here %i\t", testing_int++);
//		ft_printf("name of prev dir == %s\t", tmp->prev->name_file);
//		ft_printf("\tname of 2pre dir == %s\t", tmp->prev->prev->name_file);
//		sleep(1);
	}
	//
	//ft_printf("is outside this loop\n");
}

static int	ft_ls_print_error_files(t_ls *ls, t_file_info *file)
{
	int	i;
	t_file_info	*tmp;

	i = 0;
	tmp = file;
	while (tmp)
	{
		if (tmp->failure)
		{
			ft_ls_error(tmp->name_file, 0);
			//
			ft_printf("//is in ft_ls_print_error\n");
		}
		else
			i = 1;
		tmp = tmp->next;
	}
	if (ls->flag & FLAG_LO_R && ls->flag & FLAG_LO_L)
		ft_ls_print_long(ls->files->last_file, ls, ls->files);
	else if (ls->flag & FLAG_LO_L)
		ft_ls_print_long(file, ls, ls->files);
	else
		ft_ls_print_simple(ls->files, ls->flag);
	return (i);
}

/*
** more overhead for non recusive stuff
*/
void		print_output_handle(t_ls *ls, t_dir_info *dir, t_dir_info **point)
{
	while (dir)
	{
		(dir->head) ? ft_ls_sort_lists(ls, dir) : 0;
		(*point) ? ft_printf("%s:\n", dir->name) : 0;
		if (dir->close)
			ft_ls_error(dir->name, 1);
		else
			(ls->flag & FLAG_LO_L) ? ft_printf("total: %d\n", dir->total) : 0;
		if (dir->head && ls->flag & FLAG_LO_R && ls->flag & FLAG_LO_L)
			ft_ls_print_long(dir->last_file, ls, dir);
		(ls->flag & FLAG_LO_L) ? ft_ls_print_long(dir->head, ls, dir) :
			ft_ls_print_simple(dir, ls->flag);
		((dir->prev && ls->flag & FLAG_LO_R) || (dir->next && !(ls->flag &
				FLAG_LO_R))) ? write(1, "\n", 1): 0;
		dir = (ls->flag & FLAG_LO_R) ? dir->prev : dir->next;
		//
		ft_printf("//printing dir handle\n");
	}
}

/*
** so this should take the ls structure that contains the linked list of the
** directory (which hold linked lists for the files in them)
** and should handle the overhead for all of it
*/
void		ft_ls_printing(t_ls *ls)
{
	int		files;
	//
	files = 0;
	if (ls->files->head)
		files = (ls->files->head) ? ft_ls_print_error_files(ls, ls->files->head) : 0;
	(ls->files->head && files && ls->dirs) ? write(1, "\n", 1) : 0;
	if (ls->flag & FLAG_UP_R)
		ft_ls_recursion(ls, ls->dirs);
	else if (ls->flag & FLAG_LO_R)
		print_output_handle(ls, ls->last_dir, &ls->last_dir->prev);
	else
		print_output_handle(ls, ls->dirs, &ls->dirs->next);
	//made it here
	ft_printf("//value of error int == %d\n", files);
	ft_printf("//made end of printing\n");
	ft_printf("//%08b is flag value\n", ls->flag);
}
