/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:56:49 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 18:03:55 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

void	cmd_expand(t_simple_command_node *simple_cmd)
{
	char	**splitting;

	simple_cmd->cmd_name = expand(simple_cmd->cmd_name);
	simple_cmd->cmd_args = expand(simple_cmd->cmd_args);
	while (e_true)
	{
		if (NULL == simple_cmd->cmd_name
			&& simple_cmd->cmd_args)
		{
			splitting = ft_split(simple_cmd->cmd_args, ' ');
			simple_cmd->cmd_name = expand(ft_strdup(splitting[0]));
			ft_str_replace(&simple_cmd->cmd_args, splitting[1]);
			simple_cmd->cmd_args = expand(simple_cmd->cmd_args);
			ft_splitclear(splitting);
		}
		else
			break ;
	}
}
