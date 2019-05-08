/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:57:43 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/08 00:13:12 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char					*ft_ls_strjoin_dir(const char *s1, const char *s2)
{
	char	*d;
	char	*begin;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	begin = d;
	if (d == NULL)
		return (NULL);
	ftbzero(d, (t_strlen(s1) + ft_strlen(s2) + 1));
	while (*s1 != '\0')
		*d++ = *s1++;
	if (*(s1 - 1) != '/')
		*d++ = '/';
	while (*s2 != '\0')
		*d++ = *s2++;
	*d = '\0';
	return (begin);
}

void					ft_ls_read_dir_info(t_ft_ls *ls, const char *name)
{
	t_ft_ls_dir		*dir;
	t_ft_ls_info	*file;

	dir = ft_ls_new_dir_elem(ls, name);
	if ((ls->fd_dir = opendir(name)) <= 0)
	{
		dir->close = 1;
		return ;
	}
	while (ls->file = readdir(ls->fd_dir))
	{
		if (!(ls->flag & FLAG_A) && ls->file->d_name[0] == '.')
			continue ;
		file = ft_ls_new_file(dir);
		file->name_file = ft_strdup(ls->file->d_name);
		file->pwd = ft_ls_strjoin_dir(dir_name, file->name_file);
		if (ls->flag & FLAG_L || ls->flag & FLAG_N || ls->flag & FLAG_T
				|| ls->flag & FLAG_G || ls->flag & FLAG_UP_R)
			ft_ls_read_file_info(ls, dir, file);
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}

/*
** this is just that the file is a directory and that recursion is allowed
*/

void					ft_ls_check_if_dir(t_ft_ls *ls, t_ft_ls_info *file)
{
	while (file)
	{
		if (file->mode[0] = 'd' && !(ls->flag & FLAG_D))
			ft_ls_read_dir_info(ls, file->name_file);
		file = file->next;
	}
}
