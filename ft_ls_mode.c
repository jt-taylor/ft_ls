/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:57:09 by jtaylor           #+#    #+#             */
/*   Updated: 2019/04/30 22:35:42 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this checks the filetype with the S_IS** macros defined in
** the system header <sys/stat.h>
** the S_IS** macros return non zero if the filetype matches
** S_ISDIR checks if directory
** S_ISBLK checks if block special file (disk ?)
** S_ISCHR checks if char. special file (ie a terminal)
** S_ISLNK checks if symbolic link (symlinks)
** S_ISFIFO checks if fifo special file (or a pipe)
** S_ISSOCK checks if socket
**
** we assume S_ISREG if the others don't pass
**
** If you really want you can use bitmasks for non-POSIX machines
** ie [S_ISCHR (mode)] === [((mode & S_IFMT) == S_IFCHR)]
**
** GNU's 14.9.3 testing filetype
** https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
*/
static inline void	ft_ls_check_type(const unsigned int *mode, char *permfile)
{
	if (S_ISDIR(*mode))
		permfile[0] = 'd';
	else if (S_ISBLK(*mode))
		permfile[0] = 'b';
	else if (S_ISCHR(*mode))
		permfile[0] = 'c';
	else if (S_ISLNK(*mode))
		permfile[0] = 'l';
	else if (S_ISFIFO(*mode))
		permfile[0] = 'p';
	else if (S_ISSOCK(*mode))
		permfile[0] = 's';
	else
		permfile[0] = '-';
}


/*
** we xattr takes precidence over ACL , we don't do anything with the data just
** check if it exists to display the '@' / '+' / ' '
**
** some notes on ACL
** so here we are using acl_get_link_np which is non portable version of 
** acl_get_file but it doesn't follow symlinks
** the man says that memopry may be allocated --> so free after
** here is a (partial ?) list of the ACL
**  ACL_TYPE_ACCESS	    POSIX.1e access ACL
**  ACL_TYPE_DEFAULT    POSIX.1e default ACL
**  ACL_TYPE_NFS4	    NFSv4 ACL
**
**  From the man 
** If	any of the following conditions	occur, the acl_get_fd()	function shall
**   return a value of (acl_t)NULL and set errno to the	corresponding value:
**
**   [EACCES]		Search permission is denied for	a component of the
**  		path prefix, or	the object exists and the process does
**  		not have appropriate access rights.
**
**   [EBADF]		The fd argument	is not a valid file descriptor.
**
**   [EINVAL]		The ACL	type passed is invalid for this	file object.
**
**   [ENAMETOOLONG]	A component of a pathname exceeded 255 characters, or
**  		an entire path name exceeded 1023 characters.
**
**   [ENOENT]		The named object does not exist, or the	path_p argu-
**  		ment points to an empty	string.
**
**   [ENOMEM]		Insufficient memory available to fulfill request.
**
**   [EOPNOTSUPP]	The file system	does not support ACL retrieval.
*/
static inline void	ft_ls_check_acl_and_xattr(t_ft_ls_base_info *file,
		char *permfile)
{
	acl_t		acl;
	acl_entry_t	buf;

	acl = acl_get_link_np(file->pwd, ACL_TYPE_EXTENDED);
	if (listxattr(filr->pwd, NULL, 0, XATTR_NOFOLLOW) > 0)
		permfile[10] = '@';
	else if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &buf) != -1)
		permfile[10] = '+';
	else
		permfile[10] = ' ';
	acl_free(acl);
}

/*
** calls ft_ls_check_type to get filetype
** gets permissions for the file
** for more info see Gnu's page on testing file permissions
** https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html#Permission-Bits
** 
** stores the filtype and the permissions in the string permfile
** then checks extended attributes
*/

void				ft_ls_check_mode(t_ft_ls_base_info *file, unsigned int mode,
		char *permfile)
{
	ft_ls_check_type((const unsigned int *)&mode, permfile);
	permfile[1] = (char *)((mode & S_IRUSR) ? 'r' : '-');
	permfile[2] = (char *)((mode & S_IWUSR) ? 'w' : '-');
	permfile[3] = (char *)((mode & S_IXUSR) ? 'x' : '-');
	permfile[4] = (char *)((mode & S_IRGRP) ? 'r' : '-');
	permfile[5] = (char *)((mode & S_IWGRP) ? 'w' : '-');
	permfile[6] = (char *)((mode & S_IXGRP) ? 'x' : '-');
	permfile[7] = (char *)((mode & S_IROTH) ? 'r' : '-');
	permfile[8] = (char *)((mode & S_IWOTH) ? 'w' : '-');
	permfile[9] = (char *)((mode & S_IXOTH) ? 'x' : '-');
	if (mode & S_ISUID)
		permfile[3] = (char)((mode & S_IXUSR) ? 's' : 'S');
	if (mode & S_ISGID)
		permfile[6] = (char)((mode & S_IXGRP) ? 's' : 'S');
	if (mode & S_IXOTH)
		permfile[6] = (char)((mode & S_IXOTH) ? 't' : 'T');
	ft_ls_check_acl_and_xattr(file, permfile);
}
