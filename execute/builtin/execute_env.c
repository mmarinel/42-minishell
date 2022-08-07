/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 11:30:34 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 17:13:37 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	env_invalid_arguments_handling(char *arguments,
			t_env_decl_node *bindings_node, t_simple_command_node *cmd_node);
static t_status	env_set_bindings_and_utility(char **split,
					t_simple_command_node *cmd_node,
					t_env_decl_node *bindings_node);
static t_status	env_set_utility(char **split, t_simple_command_node *cmd_node);
//* end of static declarations

void	execute_env(char *arguments)
{
	if (arguments)
		;
	// t_bindings				*env;
	// t_env_decl_node			bindings_node;
	// t_simple_command_node	cmd_node;
	// t_bindings				*bindings;

	// cmd_node.cmd_name = NULL;
	// if (ERROR == env_invalid_arguments_handling(arguments,
	// 				&bindings_node, &cmd_node))
	// 	put_error(ENV_OPT_ERR, EXIT_FAILURE, NULL);
	// else
	// {
	// 	if (NULL == arguments)
	// 	{
	// 		env = (t_bindings *) env_handler(EXPORT_RETURN, NULL);
	// 		while (env)
	// 		{
	// 			if (env->var_val)
	// 			{
	// 				ft_printf("%s=%s\n", env->var_name, env->var_val);
	// 			}
	// 			env = env->next;
	// 		}
	// 		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	// 	}
	// 	else
	// 	{
	// 		if (cmd_node.cmd_name)
	// 		{
	// 			execute_env_statement(bindings_node);
	// 			// execute_rec()
	// 		}
	// 		else
	// 		{
	// 			bindings = bindings_node.bindings;
	// 			execute_env(NULL);
	// 			while (bindings)
	// 			{
	// 				if (bindings->var_val)
	// 				{
	// 					ft_printf("%s=%s\n", bindings->var_name, bindings->var_val);
	// 				}
	// 				bindings = bindings->next;
	// 			}
	// 		}
	// 	}
	// }
}

// static t_status	env_invalid_arguments_handling(char *arguments,
// 			t_env_decl_node *bindings_node, t_simple_command_node *cmd_node)
// {
// 	t_status				outcome;
// 	char					**split;

// 	if (arguments)
// 	{
// 		split = ft_split(arguments, ' ');
// 		if (OK == env_set_bindings_and_utility(split, &cmd_node, &bindings_node))
// 		{
// 			outcome = OK;
// 		}
// 		else
// 			outcome = ERROR;
// 		ft_splitclear(split);
// 		return (outcome);
// 	}
// 	else
// 		return (OK);
// }

// static t_status	env_set_bindings_and_utility(char **split,
// 					t_simple_command_node *cmd_node,
// 					t_env_decl_node *bindings_node)
// {
// 	char		**pair;
// 	t_bindings	*new_binding;
// 	size_t		split_ln;
// 	size_t		i;

// 	split_ln = split_len(split);
// 	bindings_node->set = e_true;
// 	i = 0;
// 	while (e_true)
// 	{
// 		pair = ft_split(split[i], '=');
// 		if (split_len(pair) > 2
// 			|| (pair && e_false == ft_is_alpha_string(pair[0])))
// 		{
// 			ft_splitclear(pair);
// 			if (i == split_ln - 1)
// 				break ;
// 			return (ERROR);
// 		}
// 		new_binding = get_new_binding(pair[0], pair[1], e_false);
// 		if (e_true == binding_exist(bindings_node->bindings, new_binding))
// 			binding_over_write(bindings_node->bindings, new_binding);
// 		else
// 			binding_add_new(bindings_node->bindings, new_binding, e_false);
// 		ft_splitclear(pair);
// 		i++;
// 		if (i == split_ln)
// 			return (OK);
// 	}
// 	return (env_set_utility(split, cmd_node));
// }

// static t_status	env_set_utility(char **split, t_simple_command_node *cmd_node)
// {
// 	char	**cmd_word;
// 	size_t	split_ln;

// 	split_ln = split_len(split);
// 	cmd_word = ft_split(split[split_ln - 1], ' ');
// 	cmd_node->cmd_name = cmd_word[0];
// 	cmd_node->cmd_args = split_merge(cmd_word + 1, ' ', e_false);
// 	ft_splitclear(cmd_word);
// 	return (OK);
// }