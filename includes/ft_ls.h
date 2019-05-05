/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:48:14 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/05 12:49:42 by jtaylor          ###   ########.fr       */
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

# define MALLOC_ERROR 1;

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
	dev_t				dev;
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
	t_info				*head;
	t_info				*last_file;
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


#endif
