/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:35:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 16:35:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

t_bool	is_builtin_command(t_tree_node *root)
{
	t_bool	is_builtin;
	char	*simple_name;

	if (root->content->content_type != SIMPL_CMD)
		return (e_true);
	simple_name = ft_get_cmd_name(root->content->simple_cmd.cmd_name);
	if (0 == ft_strcmp(simple_name, "cd")
		|| 0 == ft_strcmp(simple_name, "exit")
		|| 0 == ft_strcmp(simple_name, "echo")
		|| 0 == ft_strcmp(simple_name, "pwd")
		|| 0 == ft_strcmp(simple_name, "export")
		|| 0 == ft_strcmp(simple_name, "unset")
		|| 0 == ft_strcmp(simple_name, "env")
	)
		is_builtin = e_true;
	else
		is_builtin = e_false;
	free(simple_name);
	return (is_builtin);
}
