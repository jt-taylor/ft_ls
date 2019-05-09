/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:48:14 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/08 20:26:11 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define FLAG_L 0x01
# define FLAG_A 0x02
# define FLAG_R 0x04
# define FLAG_UP_R 0x08
# define FLAG_T 0x10
# define FLAG_N 0x20
# define FLAG_G 0x40
# define FLAG_D 0x80

/*
** the flags should function the same as they do for ls
** 		-l	long format
** 		-a	include '.' files
** 		-r	reverse the sort order
** 		-R	search dirs recursivly
** 		-t	sort by time;
** 		-n	display user and group id's numerically rather than converting
** 		-g	display the group name , not sure if i'm going to implement it
** 		-d	directories are listed as plain files and not searched recursively
*/

# define FT_LS_MALLOC_ERROR 1;

typedef struct				s_ft_ls_info
{
	char				*name_file;
	char				*pwd;
	char				*name_group;
	char				*name_user;
	char				fail_file : 1;
	char				mode[12];
	char				data[25];
	nlink_t				nlinks;
	dev_t				rdev;
	off_t				size;
	uid_t				uid;
	gid_t				gid;
	time_t				mtime;
	struct passwd		*pwuid;
	struct group		*group;
	struct s_ft_ls_info	*next;
	struct s_ft_ls_info	*prev;
}							t_ft_ls_info;

typedef struct				s_ft_ls_dir
{
	char				*name;
	char				close : 1;
	size_t				total;
	t_ft_ls_info		*head;
	t_ft_ls_info		*last_file;
	size_t				s_name;
	size_t				s_group;
	size_t				s_size;
	size_t				s_link;
	struct s_ft_ls_dir	*next;
	struct s_ft_ls_dir	*prev;
}							t_ft_ls_dir;

typedef struct				s_ft_ls
{
	DIR					*fd_dir;
	struct dirent		*file;
	struct stat			stat;
	unsigned char		flag;
	t_ft_ls_dir			*files;
	t_ft_ls_dir			*dirs;
	t_ft_ls_dir			*last_dir;
}							t_ft_ls;

/*
** Prototypes
*/

void						ft_ls_read_info(t_ft_ls *ls, char *argv);
void						ft_ls_error_msg(const char flag);
t_ft_ls_info				*ft_ls_new_file_elem(t_ft_ls_dir *dir);
void		ft_ls_sort_list_elem(t_ft_ls *ls, t_ft_ls_dir *dir);
void			ft_ls_check_file_mode(t_ft_ls_info *file, unsigned int mode,
		char *permfile);
void				ft_ls_error_msg(const char flag);
char					*ft_ls_strjoin_dir(const char *s1, const char *s2);
void					ft_ls_read_dir_info(t_ft_ls *ls, const char *name);
void					ft_ls_check_if_dir(t_ft_ls *ls, t_ft_ls_info *file);

#endif
