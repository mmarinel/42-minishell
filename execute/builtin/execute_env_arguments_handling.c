/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_arguments_handling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:01:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 19:12:38 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	exec_env_add_binding(char *word,
			t_env_decl_node *bindings_node);
static t_status	exec_env_set_utility(char **split,
					t_simple_command_node *cmd_node,
					int utility_split_index);
static t_bool	exec_env_illegal_body_el(char **pair);
//* end of static declarations

t_status	env_set_bindings_and_utility(char **split,
					t_simple_command_node *cmd_node,
					t_env_decl_node *bindings_node)
{
	t_status	outcome;
	size_t		split_ln;
	size_t		i;

	outcome = OK;
	split_ln = split_len(split);
	i = 0;
	while (i < split_ln && outcome)
	{
		if (NULL != ft_get_pathname(split[i])
			|| 0 == ft_strcmp(split[i], "export")
			|| 0 == ft_strcmp(split[i], "unset")
			|| 0 == ft_strcmp(split[i], "exit"))
		{
			outcome = exec_env_set_utility(split, cmd_node, i);
			break ;
		}
		else
			outcome = exec_env_add_binding(split[i], bindings_node);
		i++;
	}
	return (outcome);
}

static t_status	exec_env_add_binding(char *word,
			t_env_decl_node *bindings_node)
{
	t_status	outcome;
	char		**pair;
	t_bindings	*new_binding;

	pair = ft_split(word, '=');
	if (exec_env_illegal_body_el(pair))
		outcome = ERROR;
	else
	{
		outcome = OK;
		new_binding = get_new_binding(pair[0], pair[1], e_false);
		if (e_true == binding_exist(bindings_node->bindings, new_binding))
			binding_over_write(bindings_node->bindings, new_binding);
		else
			binding_add_new(&(bindings_node->bindings), new_binding, e_false);
	}
	ft_splitclear(pair);
	return (outcome);
}

static t_status	exec_env_set_utility(char **split,
					t_simple_command_node *cmd_node,
					int utility_split_index)
{
	t_status	outcome;
	char		**cmd_word;

	cmd_word = ft_split(split[utility_split_index], ' ');
	cmd_node->cmd_name = ft_strdup(cmd_word[0]);
	cmd_node->cmd_args = split_merge(split + utility_split_index + 1, " ", e_false);
	if (0 == ft_strcmp("export", cmd_node->cmd_name)
		|| 0 == ft_strcmp("unset", cmd_node->cmd_name)
		|| 0 == ft_strcmp("exit", cmd_node->cmd_name)
	)
		outcome = ERROR;
	else
		outcome = OK;
	ft_splitclear(cmd_word);
	return (outcome);
}

static t_bool	exec_env_illegal_body_el(char **pair)
{
	return (
		pair &&
		(
			split_len(pair) > 2
			|| e_false == is_env_var_name(pair[0])
		)
	);
}
