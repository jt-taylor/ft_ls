/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_check_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:09:47 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 14:48:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** learned about continue here
** -	it skips to the next iteration in a loop
** -	in for loops it runs the increment code
** -	and in while loops it goes to the next conditional test in the loop
*/

static void	ft_ls_read_dir_info(t_ft_ls *ls, const char *dir_name)
{
	t_ft_ls_dir_info	*dir;
	t_ft_ls_base_info	*file;

	dir = ft_ls_new_dir(ls, dir_name);
	if ((ls->fd_dir = opendir(dir_name)) <= 0)
	{
		dir->close = 1;
		return ;
	}
	while ((ls->file = readdir(ls->fd_dir)))
	{
		if (!(ls->flag & FLAG_A) && ls->file->d_name[0] == '.')
			continue ;
		file = ft_ls_new_file(dir);
		file->name_file = ft_strdup(ls->file->d_name);
		file->pwd = //ft_strjoin_dir(dir_name, file->name_file);
		if (ls->flag)
			//read_file_info;
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}

void		ft_ls_check_dir(t_ft_ls *ls, t_ft_ls_base_info *file)
{
	while (file)
	{
		if (file->mode[0] == 'd' && !(ls->flag & FLAG_D))
			//read_dir_info(ls, file->name_file);
		file = file->next;
	}
}
