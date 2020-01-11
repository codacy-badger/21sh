/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:00:39 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/07 20:19:08 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

//int				set_redirections(t_node *cmd, int stdin_fd, int stdout_fd);
int				exec_pipe(t_node *ast, t_env *env, t_lexer *lexer);
int				exec_with_io(t_node *cmd, t_env *env, int stdin_fd, 
				int stdout_fd);
int				exec_command(t_node *cmd, t_env *env, t_lexer *lexer);
int				set_redirections(t_node *cmd, t_lexer *lexer);
void			get_and_output_heredoc(t_lexer *lexer, t_node *op_node);
char			**get_argv(t_node *cmd, t_env *env);

#endif
