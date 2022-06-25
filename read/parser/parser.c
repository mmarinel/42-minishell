/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/25 12:43:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tree_node	*parse_cm_list(void);

t_tree_node	*parse(void)
{
	return (parse_cm_list());
}

static t_tree_node	*parse_cm_list(void)
{
	t_tree_node	*sub_tree;
	t_token		*cur_token;

	while (e_true)
	{
		cur_token = next_token();
		if (!cur_token)
			break ;
		if (cur_token->token_id == e_PARENTHESIS)
		{
			if (*((char *)cur_token->token_id) == ')')
				return (NULL);
			else
				sub_tree = parse_cm_list();
		}
		sub_tree = (t_tree_node *) malloc(sizeof(t_tree_node));
		// while loop scan infile
	}
}
