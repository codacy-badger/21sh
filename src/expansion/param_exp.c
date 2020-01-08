/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:36:33 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/08 18:18:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_var_name(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (NULL);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		return (NULL);
	return (ft_strsub(str, 0, i));
}

static bool	should_expand(char *str, int i, char quote_status)
{
	if (str[i] != '$')
		return (false);
	if (quote_status == SQUOTE)
		return (false);
	if (i != 0 && str[i - 1] == BSLASH)
		return (false);
	return (true);
}

int			param_expand(t_dstr *str, int start, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		i;
	char	quote_status;

	i = 0;
	quote_status = NONE;
	while (str->str[++i])
	{
		if (is_quote_stop(str->str, i, quote_status))
			quote_status = NONE;
		else if (is_quote_start(str->str, i, quote_status))
			quote_status = str->str[i];
		if (should_expand(str->str, i, quote_status)
				&& (var_name = get_var_name(str->str + i + 1)))
		{
			var_value = get_env_var(var_name, env);
			ft_dstr_remove(str, i, ft_strlen(var_name) + 1);
			ft_dstr_insert(str, i, var_value, ft_strlen(var_value));
			i += ft_strlen(var_value) - 1;
			free(var_name);
		}
		i++;
	}
	return (0);
}
