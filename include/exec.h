/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:00:39 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 15:03:01 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

int				set_redirections(t_node *cmd, int stdin_fd, int stdout_fd);
int				exec_pipe(t_node *ast, t_env *env, int input_fd);
int				exec_with_io(t_node *cmd, t_env *env, int stdin_fd, 
				int stdout_fd);
int				exec_command(char **argv, t_env *env);

#endif
