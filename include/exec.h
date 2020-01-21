/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:00:39 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/14 12:00:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

typedef struct	s_fd_backup
{
	int			backup;
	int			orig_number;
}				t_fd_backup;

int				exec_pipe(t_node *ast, t_env *env);
int				exec_with_io(t_node *cmd, t_env *env, int stdin_fd, 
				int stdout_fd);
int				exec_command(t_node *cmd, t_env *env);
int				exec_command_argv(char **argv, t_env *env);
int				exec_builtin(char **argv, t_env *env, t_node *cmd);

int				set_redirections(t_node *cmd, bool backup);
bool			is_valid_fd(int fd);
void			move_fd(int *fd);
int				dup2_and_backup(int fildes1, int fildes2, bool backup);
int				restore_fds(void);

char			**get_argv(t_node *cmd, t_env *env);
bool			str_is_nbr(const char *str);

#endif
