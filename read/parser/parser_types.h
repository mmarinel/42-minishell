/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:48:27 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 12:03:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

# include "../tokenizer/tok_types.h"

# define SIMPL_CMD 0
# define ENV_STATEMENT 1
# define OPERATOR 2
# define REDIR 3

typedef enum e_operator
{
	e_PIPE,
	e_OR,
	e_AND
}	t_operator;

typedef struct s_operator_node
{
	t_operator	operator;
}	t_operator_node;

typedef struct s_simple_command_node
{
	char	*cmd_name;
	char	*cmd_args;
}	t_simple_command_node;

// typedef struct s_bindings
// {
// 	t_bool				concat;
// 	char				*var_name;
// 	char				*var_val;
// 	struct s_bindings	*next;
// }	t_bindings;

typedef struct s_env_decl_node
{
	t_bool		set;
	t_bindings	*bindings;
}	t_env_decl_node;

typedef	struct s_node_content
{
	t_redirection			in_redir;
	t_redirection			out_redir;
	short					content_type;
	t_simple_command_node	simple_cmd;
	t_env_decl_node			env_decl;
	t_operator_node			operator_node;
}	t_node_content;

typedef struct s_redirection
{
	char	*file_name;
	t_bool	append_mode;
}	t_redirection;

typedef struct s_tree_node
{
	t_node_content		*content;
	t_bool				launch_subshell;
	void				(*to_string)(struct s_tree_node *node);
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_groupings
{
	size_t	quotes;
	size_t	double_qquotes;
	size_t	parenthesis;
}	t_groupings;

typedef struct parser_status
{
	t_status	status;
	t_groupings	open;
}	t_parser_status;

#endif
