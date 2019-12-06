/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:37:04 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Think about interactive & non interactive mode...
** assert read line works properly when read from file

** these functions return integers
*/


static int	data_init(t_data *data)
{
	if (!(data->prompts = (char **)ft_memalloc(sizeof(char *) * 5)))
		return (ALLOC_ERROR);
	if (!(data->prompts[PS1] = ft_strdup("21sh©>> ")))
		return (ALLOC_ERROR);
	if (!(data->prompts[PS2] = ft_strdup("-> ")))
		return (ALLOC_ERROR);
	if (!(data->prompts[PS3] = ft_strdup("'> ")))
		return (ALLOC_ERROR);
	if (!(data->prompts[PS4] = ft_strdup("\"> ")))
		return (ALLOC_ERROR);
	data->prompts[4] = NULL;
	return (0);
}

int			shell_init(t_sh *shell)
{
	int		ret;

	ft_bzero(shell, sizeof(*shell));
	sig_init(shell);
	if ((ret = data_init(&shell->data)) != 0)
		return (ret);
	if ((ret = term_init(&shell->term)) != 0)
		return (ret);
	if ((ret = input_init(&shell->input, &shell->data)) != 0)
		return (ret);
	if ((ret = lexer_init(&shell->lexer)) != 0)
		return (ret);
	return (ret);
}
