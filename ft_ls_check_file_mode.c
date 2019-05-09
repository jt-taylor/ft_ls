/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_check_file_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:56:09 by jtaylor           #+#    #+#             */
/*   Updated: 2019/05/08 20:13:09 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** here is a link for testing filetype
** https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
** paraphrased {
** S_ISDIR		-> This macro returns non-zero if the file is a directory.
** S_ISCHR		-> This macro returns non-zero if the file is a character
** 				special file (a device like a terminal).
** S_ISBLK		-> This macro returns non-zero if the file is a block special
** 				file (a device like a disk).
** S_ISREG		-> This macro returns non-zero if the file is a regular file.
** S_ISFIFO		-> This macro returns non-zero if the file is a FIFO special
** 				file, or a pipe. See Pipes and FIFOs.
** S_ISLNK		-> This macro returns non-zero if the file is a symbolic link.
** 				See Symbolic Links.
** S_ISSOCK		-> This macro returns non-zero if the file is a socket
**
**
** S_IFMT		->This is a bit mask used to extract the file type code from a mode value.
**		 S_ISCHR (mode)
**		 is equivalent to:
**		 ((mode & S_IFMT) == S_IFCHR)
*/
static inline void	ft_ls_check_file_type(const unsigned int *mode,
		char *permfile)
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
** this basically does the same thing as above but with the permission  bits
**		instead of the filetype
** for a better explanation , mostly because i don't feel like copying it over
** 		see			https://www.gnu.org/software/libc/manual/html_node/
** 		Permission-Bits.html#Permission-Bits
** 		gotta split the link cause of norm :{
** 		
** 		file is unused right now -- would be used to check for ACL and xattr
** 			if i go back and put those in
*/

void			ft_ls_check_file_mode(t_ft_ls_info *file, unsigned int mode,
		char *permfile)
{
	(file) ? 0 : 0;
	ft_ls_check_file_type((const unsigned int *)&mode, permfile);
	permfile[1] = (char)((mode & S_IRUSR) ? 'r' : '-');
	permfile[2] = (char)((mode & S_IWUSR) ? 'w' : '-');
	permfile[3] = (char)((mode & S_IXUSR) ? 'x' : '-');
	permfile[4] = (char)((mode & S_IRGRP) ? 'r' : '-');
	permfile[5] = (char)((mode & S_IWGRP) ? 'w' : '-');
	permfile[6] = (char)((mode & S_IXGRP) ? 'x' : '-');
	permfile[7] = (char)((mode & S_IROTH) ? 'r' : '-');
	permfile[8] = (char)((mode & S_IWOTH) ? 'w' : '-');
	permfile[9] = (char)((mode & S_IXOTH) ? 'x' : '-');
	if (mode & S_ISUID)
		permfile[3] = (char)((mode & S_IXUSR) ? 's' : 'S');
	if (mode & S_ISGID)
		permfile[6] = (char)((mode & S_IXGRP) ? 's' : 'S');
	if (mode & S_ISVTX)
		permfile[9] = (char)((mode & S_IXOTH) ? 't' : 'T');
}
