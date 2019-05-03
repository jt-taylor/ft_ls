/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:04:32 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/03 14:48:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stats.h>
# include <sys/acl.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"
# include "ft_printf.h"

/*
** Flag Values
*/

# define FLAG_L 0x01
# define FLAG_A 0x02
# define FLAG_R 0x04
# define FLAG_RR 0x08
# define FLAG_T 0x10

/*
** return codes
*/
# define SUCCESS 0
# define FT_MALLOC_ERROR_CODE 1

/*
** dir specific info
*/

typedef struct			s_ft_ls_dir_info
{
	char			*name;
	char			close : 1;
	size_t			total;
	t_ft_ls_base_info			*head;
	t_ft_ls_base_info			*last_file;
	size_t			s_name;
	size_t			s_group;
	size_t			s_size;
	size_t			s_link;
	struct s_dir	*next;
	struct s_dir	*prev;
}						t_ft_ls_dir_info;

/*
** basic info
*/

typedef struct			t_ft_ls_base_info;
{
	char						*name_of_file;
	char						*pwd;
	char						*name_group;
	char						*name_user;
	char						fail_file : 1;
	char						mode[12];
	char						data[25];
	nlink_t						nlinks;
	dev_t						dev;
	off_t						size;
	uid_t						uid;
	gid_t						gid;
	time_t						mtime;
	struct passwd				*pwuid;
	struct group				*group;
	struct s_ft_ls_base_info	*next;
	struct s_ft_ls_base_info	*prev;
}						t_ft_ls_base_info;

/*
** base structure
*/

typedef struct			s_ft_ls
{
	DIR					*fd_dir;
	struct dirent		*file;
	struct stat			stat;
	unsigned char		flag;
	t_dir				*files;
	t_dir				*dirs:
	t_dir				*last_dir;

}						t_ft_ls;

/*
** Prototypes
*/

void						ft_ls_read_info(t_ls *ls, char *argv);
t_info		*ft_ls_new_file(t_ft_ls_dir_info *dir);
size_t		ft_ls_count(intmax_t n, short int base);
t_ft_ls_dir_info		*ls(t_ft_ls *ls, const char *name);
size_t		ft_ls_count(intmax_t n, short int base);

#endif
