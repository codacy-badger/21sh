/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:42:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	parse_args(t_sh *shell, int argc, char **argv)
{
	int		fd;

	if (argc > 0)
	{
		if ((fd = open(argv[0], O_RDONLY)) == -1)
		{
			write(STDERR_FILENO, "21sh: Could not open file\n", 26);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		return (0);
	}
	shell->input.interactive = true;
	return (0);
}

int			init(t_sh *shell, int argc, char **argv)
{
	extern char	**environ;

	if (!isatty(STDIN_FILENO))
		exit(1);
	ft_bzero(shell, sizeof(*shell));
	parse_args(shell, argc, argv);
	if (shell->input.interactive)
	{
		init_sig(shell);
		init_term(&shell->term);
	}
	init_input(&shell->input, &shell->term);
	init_lexer(&shell->lexer, &shell->input);
	shell->env = env_dup(environ);
	return (0);
}
