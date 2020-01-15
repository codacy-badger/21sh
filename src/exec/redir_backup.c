/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_backup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:48:51 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/15 13:51:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_list_head *g_backups = NULL;

bool	fd_used_for_backup(int fildes)
{
	t_list_head *cur;

	cur = g_backups->next;
	while (!ft_list_is_last(cur, g_backups))
	{
		if (((t_fd_backup *)cur->data)->backup == fildes)
			return (true);
		cur = cur->next;
	}
	return (((t_fd_backup *)cur->data)->backup == fildes);
}

bool	is_valid_fd(int fd)
{
	struct stat	buf;

	return (fd < 256 && !fd_used_for_backup(fd) && fstat(fd, &buf) != -1);
}

int		dup2_and_backup(int fildes1, int fildes2, bool backup)
{
	t_fd_backup *backup_store;

	if (backup == false)
		return (dup2(fildes1, fildes2));
	if (g_backups == NULL)
		g_backups = ft_list_first_head(NULL);
	backup_store = ft_xmalloc(sizeof(t_fd_backup));
	backup_store->orig_number = fildes2;
	backup_store->backup = dup(fildes2);
	ft_list_add(backup_store, g_backups);
	return (dup2(fildes1, fildes2));
}

int		restore_fds(void)
{
	t_list_head *cur;
	t_list_head *tmp;
	t_fd_backup *backup;

	if (g_backups == NULL)
		return (0);
	cur = g_backups->next;
	while (!ft_list_empty(g_backups))
	{
		backup = cur->data;
		dup2(backup->backup, backup->orig_number);
		free(cur->data);
		tmp = cur;
		cur = cur->next;
		ft_list_del(tmp);
	}
}
