/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:11:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/07 17:55:31 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** if the the file was modified more than six months ago or
** if the files last modify time is future dated
** 		we could do this later but ls switches from the time to the year
** 		this won't work exactly the same as ls but works logically so this is
** 		how it's gonna work
*/

static inline void		ft_ls_check_time(t_ft_ls *file)
{
	time_t	current;
	char	*str;

	current = time(NULL);
	ft_strncpy(&file->data[0], ctime(&file->mtime), 24);
	if (current - file->mtime > 15778463 || current < file->mtime)
	{
		str = ft_strdup(file->data);
		ft_bzero(file->data, 25);
		ft_strncpy(&file->data, str, 10);
		file->data[10] = ' ';
		ft_strncpy(&file->data[11], &str[19], 5);
		free(str);
	}
}

static inline void		ft_ls_read_link(t_ft_ls_info *file)
{
	char	*alt;
	ssize_t	size;

	alt = malloc(PATH_MAX);
	ft_bzero*(alt, PATH_MAX);
	if (file->pwd)
		size = readlink(file->pwd, alt, PATH_MAX);
	else
		size = readlink(file->name_file, buf, PATH_MAX);
	alt[size] = '\0';
	file->name_file = ft_strjoin(file->name_file, " -> ");
	file->name_file = ft_strjoin(file->name_file, alt);;
	free(alt);
}

static inline void		ft_ls_read_file_info(t_ft_ls *ls, t_ft_ls_dir *dir,
		t_ft_ls_info *file)
{
	size_t		n;

	lstat(file->pwd, &ls->ls->stat);
	file->nlinks = ls->stat.st_nlinks;
	file->uid = ls->stat.st_uid;
	file->gid = ls->stat.st_gid;
	file->group = getgrgid(file->gid);
	file->pwuid = getpwuid(file->uid);
	(file->group) ? file->name_group = ft_strdup(file->group->gr_name) : 0;
	(file->pwuid) ? file->name_user = ft_strdup(file->pwuid->pw_name) : 0;
	file->rdev = ls->stat.st_rdev;
	file->size = ls->stat.st_size;
	file->mtime = (size_t)ls->stat.st_mtime;
	ft_ls_check_file_mode(file, ls->stat.st_mode, &file->mode[0]);
	(file->mode[0] == 'l') ? ft_ls_find_link(file) : 0;
	(file->mode[0] == 'c') ? dir->s_size = 8 : 0;
	n = (file->group) ? ft_strlen(file->group->gr_name) + 1 : 0;
	(n > dir->s_group) ? dir->s_group = n : 0;
	n = (file->pwuid) ? ft_strlen(file->pwuid->pw_name) + 1 : 0;
	(n > dir->s_name) ? dir->s_name = n : 0;
	n = ft_count(file->size, 10);
	(n > dir->s_size) ? dir->s_size = n : 0;
	n = ft_count(file->nlinks, 10);
	(n > dir->s_link) ? dir->s_link = n : 0;
	ft_ls_check_time(file);
}



/*
** so basically we are calling lstat and copyin all of the data into
** 		our info struct
** this is kind of a roundabout way of doing it but should make printing easier
*/
void					ft_ls_read_info(t_ft_ls *ls, char *argv)
{
	t_ft_ls_info		*info_file;
	int					num;

	num = lstat(argv, &ls->stat);
	file = ft_ls_new_file_elem(ls->files);
	file->name_file = ft_strdup(argv);
	if (num >= 0)
		ft_ls_read_file_info(ls, ls->files, file);
	ft_bzero(&ls->stat, sizeof(ls->stat));
}
