/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_arguments_handling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:01:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 10:17:55 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	env_set_body(
					char *word,
					t_env_decl_node *bindings_node,
					t_bool	*unset_export_found_ref);
static t_status	env_set_utility(char **split,
					t_simple_command_node *cmd_node,
					int utility_split_index);
static t_bool	illegal_body_el(char **pair);
//* end of static declarations

t_status	env_set_bindings_and_utility(char **split,
					t_simple_command_node *cmd_node,
					t_env_decl_node *bindings_node)
{
	size_t		split_ln;
	size_t		i;
	t_bool		unset_export_found;

	unset_export_found = e_false;
	split_ln = split_len(split);
	i = 0;
	while (e_true)
	{
		if (ERROR == env_set_body(split[i], bindings_node,
				&unset_export_found))
		{
			
			if (i == split_ln - 1
				|| unset_export_found)
				break ;
			else
				return (ERROR);
		}
		i++;
		if (i == split_ln)
			return (OK);
	}
	return (env_set_utility(split, cmd_node, i));
}

static t_status	env_set_body(
					char *word,
					t_env_decl_node *bindings_node,
					t_bool	*unset_export_found_ref)
{
	t_status	outcome;
	char		**pair;
	t_bindings	*new_binding;

	pair = ft_split(word, '=');
	if (illegal_body_el(pair))
	{
		if (0 == ft_strcmp("export", pair[0])
			|| 0 == ft_strcmp("unset", pair[0]))
			*unset_export_found_ref = e_true;
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

static t_status	env_set_utility(char **split,
					t_simple_command_node *cmd_node,
					int utility_split_index)
{
	t_status	outcome;
	char		**cmd_word;

	cmd_word = ft_split(split[utility_split_index], ' ');
	cmd_node->cmd_name = ft_strdup(cmd_word[0]);
	cmd_node->cmd_args = split_merge(cmd_word + 1, " ", e_false);
	if (0 == ft_strcmp("export", cmd_node->cmd_name)
		|| 0 == ft_strcmp("unset", cmd_node->cmd_name))
		outcome = ERROR;
	else
		outcome = OK;
	ft_splitclear(cmd_word);
	return (outcome);
}

static t_bool	illegal_body_el(char **pair)
{
	return (
		pair &&
		(
			split_len(pair) > 2
			|| e_false == ft_is_alpha_string(pair[0])
			|| 0 == ft_strcmp("export", pair[0])
			|| 0 == ft_strcmp("unset", pair[0])
		)
	);
}
