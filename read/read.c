/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:51:54 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 11:37:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "prompt/prompt.h"

// TODO :-> put error where exit_shell is (put error will also use exit_shell)
t_tree_node	*shell_read(void)
{
	char	*command;

	printf("\1");
	command = ft_readline
		(
			ft_strjoin(
				get_current_working_directory(),
				ft_strjoin(RESET, "\2", e_false, e_false),
				e_true, e_true),
			e_true
			);
	// printf("line read: %s\n", command);
	tokenizer_feed_input(command);
	// t_token	*token;
	// while (e_true)
	// {
	// 	token =  next_token();
	// 	if (!token)
	// 		break ;
	// 	// print_token(token);
	// 	printf("%s ", tok_to_string(token));
	// }
	// printf("\n");

	return (parse());
	// return (command);
	// if (envp)
	// 	;
}

	// t_token	*token;
	// while (e_true)
	// {
	// 	token =  next_token();
	// 	if (!token)
	// 		break ;
	// 	token->to_string(token);
	// }
	// printf("\n");
