/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:34:41 by jtaylor           #+#    #+#             */
/*   Updated: 2019/06/26 22:27:10 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>
# include "libft.h"

/*
** Flags
**	mandatory :
**		long format
**		include '.' dirs turns on -l
**		reverse the output order
**		resursively search dirs
**		sort by time modified
**
**	optional :
**		
*/
# define FLAG_LO_L 0x01
# define FLAG_LO_A 0x02
# define FLAG_LO_R 0x04
# define FLAG_UP_R 0x08
# define FLAG_LO_T 0x10

/*
** most of the examples that I looked at are using 3 structs
** 	1) for each actaul file
** 	2) for each directory
** 	3) the main ls struct that holds the dirs
*/

typedef struct		s_file_info
{
	char		*name_file;
	char		*pwd;
	char		*name_group;
	char		*name_user;
	int			failure;
	char		mode[12];
	char		data[25];
	nlink_t		nlinks;
	dev_t		rdev;
	off_t		size;
	uid_t		uid;
	gid_t		gid;
	time_t		mtime;
	struct passwd	*pwuid;
	struct group	*group;
	struct s_file_info	*next;
	struct s_file_info	*prev;
}					t_file_info;

typedef struct		s_dir_info
{
	char			*name;
	char			close : 1;
	size_t			total;
	t_file_info			*head;
	t_file_info			*last_file;
	size_t			s_name;
	size_t			s_group;
	size_t			s_size;
	size_t			s_link;
	struct s_dir_info	*next;
	struct s_dir_info	*prev;
}					t_dir_info;

typedef struct		s_ls
{
	DIR				*fd_dir;
	struct dirent	*file;
	struct stat		stat;
	unsigned char	flag;
	t_dir_info		*files;
	t_dir_info		*dirs;
	t_dir_info		*last_dir;
}					t_ls;

/*
** ft_list_handle.c
*/
t_dir_info		*new_dir_elem(t_ls *ls, const char *name);
t_file_info		*new_file_elem(t_dir_info *dir);
/*
** ft_sl_get_mode.c
*/
void		check_mode(unsigned int mode, char *str);
/*
** ft_ls_read_info.c
*/
void	ft_ls_read_info(t_ls *ls, char *argv);
void	ft_ls_read_dir_info(t_ls *ls, const char *dir_name);
/*
** ft_ls_sorting.c
*/
void		ft_ls_sort_lists(t_ls *ls, t_dir_info *dir);
/*
** ft_ls_misc.c
*/
void		validate_dir(t_ls *ls, t_file_info *file);
char	*ft_join_dir(const char *s1, const char *s2);
size_t		ft_nbrlen(intmax_t num, uint8_t base);
void		ft_ls_error(char *str, char witch);

/*
** ft_ls_recursion
*/
void	ft_ls_recursion(t_ls *ls, t_dir_info *dir);

/*
** ft_ls_printing.c
*/
void		ft_ls_printing(t_ls *ls);
void		print_output_handle(t_ls *ls, t_dir_info *dir, t_dir_info **point);
void		ft_ls_print_long(t_file_info *file, t_ls *ls, t_dir_info *dir);
void		ft_ls_print_simple(t_dir_info *dir, char flag);

#endif
