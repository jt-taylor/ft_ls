/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_read_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:05:19 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/02 14:14:19 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** this will theck the time for a file
** copies into file->data[0]
*/
static inline void		check_time(t_file_info *file)
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
** this will handle the reading of links and append it to the file name
*/
static inline void		find_link(t_file_info *file)
{
	char	*buffer;
	ssize_t	size;

	buffer = malloc(PATH_MAX);
	ft_bzero(buffer, PATH_MAX);
	if (file->pwd)
		size = readlink(file->pwd, buffer, PATH_MAX);
	else
		size = readlink(file->name_file, buffer, PATH_MAX);
	buffer[size] = '\0';
	file->name_file = ft_strjoin(file->name_file, " -> ");
	file->name_file = ft_strjoin(file->name_file, buffer);
	free(buffer);
}

/*
** this will handle the actual reading of the data for a file
*/
static inline void		ft_ls_read_file_info(t_ls *ls, t_dir_info *dir,
		t_file_info *file)
{
	size_t	n;

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
	check_mode(ls->stat.st_mode, &file->mode[0]);
	(file->mode[0] == 'l') ? find_link(file) : 0;
	(file->mode[0] == 'c') ? dir->s_size = 8 : 0;
	n = (file->group) ? (ft_strlen(file->group->gr_name) + 1) : 0;
	(n > dir->s_group) ? dir->s_group = n : 0;
	n = (file->pwuid) ? (ft_strlen(file->pwuid->pw_name) + 1) : 0;
	(n > dir->s_name) ? dir->s_group = n : 0;
	n = ft_nbrlen(file->size, 10);
	(n > dir->s_size) ? dir->s_size = n : 0;
	n = ft_nbrlen(file->nlinks, 10);
	(n > dir->s_link) ? dir->s_link = n : 0;
	check_time(file);
}

/*
** this is the handle for directory entries , either implicit or from a given path
*/
void	ft_ls_read_dir_info(t_ls *ls, const char *dir_name)
{
	t_dir_info	*dir;
	t_file_info	*file;

	dir = new_dir_elem(ls, dir_name);
	if ((ls->fd_dir = opendir(dir_name)) <= 0)
	{
		dir->close = 1;
		return ;
	}
	while ((ls->file = readdir(ls->fd_dir)))
	{
		// this is causing problems but it it shoudn't be ???
		// -a is making it read more of the files bu still doesn'y read all of them
		if (!(ls->flag & FLAG_LO_A) && (ls->file->d_name[0] == '.'))
			//
		{
			ft_printf("// ft_ls_read_dir continue trigger d_name=%s\n", ls->file->d_name);
			continue ;
		}
		file = new_file_elem(dir);
		file->name_file = ft_strdup(ls->file->d_name);
		//
		ft_printf("value that was strdup'd == %s\n", file->name_file);
		file->pwd = ft_join_dir(dir_name, file->name_file);
		if (ls->flag & FLAG_LO_L || ls->flag & FLAG_LO_T ||
				ls->flag & FLAG_UP_R)
			ft_ls_read_file_info(ls, dir, file);
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
		//
		testing_int++;
	}
	closedir(ls->fd_dir);
	//
	ft_printf("//dir_name = %s\n\n\n", dir_name);
}

/*
** this is the handle for given files (ie ./ft_ls path_to_file_name)
** as apposed to grabbing it implicitly (ie ./ft_ls)
*/

void	ft_ls_read_info(t_ls *ls, char *argv)
{
	//
	ft_printf("//read_info\n");
	t_file_info	*file;

	file = new_file_elem(ls->files);
	file->name_file = ft_strdup(argv);
	if (lstat(argv, &ls->stat) < 0)
		//
	{
		//
		ft_printf("lstat file errror\n");
		file->failure = 1;
	}
	else
		ft_ls_read_file_info(ls, ls->files, file);
	ft_bzero(&ls->stat,sizeof(ls->stat));
}
