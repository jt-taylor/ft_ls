/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:11:34 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/20 22:59:48 by jtaylor          ###   ########.fr       */
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

static inline void		ft_ls_check_time(t_ft_ls_info *file)
{
	time_t	current;
	char	*str;

	current = time(NULL);
	ft_strncpy(&file->data[0], ctime(&file->mtime), 24);
	if (current - file->mtime > 15778463 || current < file->mtime)
	{
		str = ft_strdup(file->data);
		ft_bzero(file->data, 25);
		ft_strncpy(&file->data[0], str, 10);
		file->data[10] = ' ';
		ft_strncpy(&file->data[11], &str[19], 5);
		free(str);
	}
}

/*
** this function calls readlink , heres the man for readlink
**
** Description
** The readlink() function shall place the contents of the symbolic link 
** referred to by path in the buffer buf which has size bufsize. If the number
** of bytes in the symbolic link is less than bufsize, the contents of the
** remainder of buf are unspecified. If the buf argument is not large enough to
** contain the link content, the first bufsize bytes shall be placed in buf.
**
** If the value of bufsize is greater than {SSIZE_MAX}, the result is
** implementation-defined.
**
** Return Value
** Upon successful completion, readlink() shall return the count of bytes placed in the buffer. Otherwise, it shall return a value of -1, leave the buffer unchanged, and set errno to indicate the error.
**
*/

static inline void		ft_ls_read_link(t_ft_ls_info *file)
{
	char	*alt;
	ssize_t	size;

	alt = malloc(PATH_MAX);
	ft_bzero(alt, PATH_MAX);
	if (file->pwd)
		size = readlink(file->pwd, alt, PATH_MAX);
	else
		size = readlink(file->name_file, alt, PATH_MAX);
	alt[size] = '\0';
	file->name_file = ft_strjoin(file->name_file, " -> ");
	file->name_file = ft_strjoin(file->name_file, alt);;
	free(alt);
}

void		ft_ls_read_file_info(t_ft_ls *ls, t_ft_ls_dir *dir,
		t_ft_ls_info *file)
{
	size_t		n;

	lstat(file->pwd, &ls->stat);
	file->nlinks = ls->stat.st_nlink;
	file->uid = ls->stat.st_uid;
	file->gid = ls->stat.st_gid;
	file->group = getgrgid(file->gid);
	file->pwuid = getpwuid(file->uid);
	(file->group) ? file->name_group = ft_strdup(file->group->gr_name) : 0;
	(file->pwuid) ? file->name_user = ft_strdup(file->pwuid->pw_name) : 0;
	file->rdev = ls->stat.st_rdev;
	file->size = ls->stat.st_size;
	file->mtime = (size_t)ls->stat.st_mtime;
	ft_ls_check_file_mode(ls->stat.st_mode, &file->mode[0]);
	(file->mode[0] == 'l') ? ft_ls_read_link(file) : 0;
	(file->mode[0] == 'c') ? dir->s_size = 8 : 0;
	n = (file->group) ? ft_strlen(file->group->gr_name) + 1 : 0;
	(n > dir->s_group) ? dir->s_group = n : 0;
	n = (file->pwuid) ? ft_strlen(file->pwuid->pw_name) + 1 : 0;
	(n > dir->s_name) ? dir->s_name = n : 0;
	n = ft_count_num_len(file->size, 10);
	(n > dir->s_size) ? dir->s_size = n : 0;
	n = ft_count_num_len(file->nlinks, 10);
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
	info_file = ft_ls_new_file_elem(ls->files);
	info_file->name_file = ft_strdup(argv);
	(num < 0) ? info_file->fail = 1 : 0;
	if (num >= 0)
		ft_ls_read_file_info(ls, ls->files, info_file);
	ft_bzero(&ls->stat, sizeof(ls->stat));
}
