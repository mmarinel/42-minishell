/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_arguments_handling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:01:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 19:27:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	env_set_body(
					char *word,
					t_env_decl_node *bindings_node);
static t_status	env_set_utility(char **split, t_simple_command_node *cmd_node);
//* end of static declarations

t_status	env_set_bindings_and_utility(char **split,
					t_simple_command_node *cmd_node,
					t_env_decl_node *bindings_node)
{
	size_t		split_ln;
	size_t		i;

	split_ln = split_len(split);
	i = 0;
	while (e_true)
	{
		if (ERROR == env_set_body(split[i], bindings_node))
		{
			
			if (i == split_ln - 1)
				break ;
			else
				return (ERROR);
		}
		i++;
		if (i == split_ln)
			return (OK);
	}
	return (env_set_utility(split, cmd_node));
}

static t_status	env_set_body(
					char *word,
					t_env_decl_node *bindings_node)
{
	t_status	outcome;
	char		**pair;
	t_bindings	*new_binding;

	pair = ft_split(word, '=');
	if (split_len(pair) > 2
		|| (pair && e_false == ft_is_alpha_string(pair[0])))
	{
		outcome = ERROR;
	}
	else
	{
		new_binding = get_new_binding(pair[0], pair[1], e_false);
		if (e_true == binding_exist(bindings_node->bindings, new_binding))
			binding_over_write(bindings_node->bindings, new_binding);
		else
			binding_add_new(&(bindings_node->bindings), new_binding, e_false);
		outcome = OK;
	}
	ft_splitclear(pair);
	return (outcome);
}

static t_status	env_set_utility(char **split, t_simple_command_node *cmd_node)
{
	char	**cmd_word;
	size_t	split_ln;

	split_ln = split_len(split);
	cmd_word = ft_split(split[split_ln - 1], ' ');
	cmd_node->cmd_name = ft_strdup(cmd_word[0]);
	cmd_node->cmd_args = split_merge(cmd_word + 1, " ", e_false);
	ft_splitclear(cmd_word);
	return (OK);
}
