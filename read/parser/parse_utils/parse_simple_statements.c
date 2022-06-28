/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_statements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:55:41 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 13:06:03 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

t_node_content	*parse_operator(t_token *token)
{
	t_node_content	*new;

	new = (t_node_content *) malloc(sizeof(t_node_content));
	new->content_type = OPERATOR;
	new->infile = NULL;
	new->outfile = NULL;
	if (*((char *)token->token_val) == '|')
	{
		if (*((char *)token->token_val + 1) == '|')
			new->operator_node.operator = e_OR;
		else
			new->operator_node.operator = e_PIPE;
	}
	else
		new->operator_node.operator = e_AND;
	return (new);
}

t_node_content	*parse_simple_command(t_token *token, t_node_content *node_content)
{

	node_content->content_type = SIMPL_CMD;
	if (token->token_id == e_CMD_ARG)
	{
		node_content->simple_cmd.cmd_args = ft_strcpy(NULL, token->token_val,
			ft_strlen(token->token_val));
		token = next_token();
	}
	node_content->simple_cmd.cmd_name = ft_strcpy(NULL, token->token_val,
			ft_strlen(token->token_val));
	return (node_content);
}

t_node_content	*parse_env_statement(t_token *token, t_node_content *node_content)
{
	node_content->content_type = ENV_STATEMENT;
	node_content->env_decl.set = (token->token_id == e_ENV_VAR_DECL);
	node_content->env_decl.bindings = (t_bindings *)token->token_val;
	token->token_val = NULL;
	return (node_content);
}

void	parse_redir(t_node_content *node_content, char *file_name, t_token_id in_out)
{
	if (in_out == e_IN_FILE)
	{
		ft_free(node_content->infile);
		node_content->infile = ft_strcpy(NULL, file_name,
								ft_strlen(file_name));
	}
	if (in_out == e_OUT_FILE)
	{
		ft_free(node_content->outfile);
		node_content->outfile = ft_strcpy(NULL, file_name,
								ft_strlen(file_name));
	}
}
