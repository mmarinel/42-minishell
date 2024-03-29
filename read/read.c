/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:51:54 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:08:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "../colors.h"

static char	*read_next_command(void);
//* end of static declarations

t_tree_node	*shell_read(void)
{
	char	*command;

	command = read_next_command();
	if (command_is_empty(command))
	{
		ft_free(command);
		return (NULL);
	}
	else
	{
		tokenizer_feed_input(command);
		free(command);
		return (parse());
	}
}

static char	*read_next_command(void)
{
	printf("\1");
	return (
		ft_read_command(
			ft_strjoin(
				get_current_working_directory(),
				ft_strjoin(RESET, "\2", e_false, e_false),
				e_true, e_true)
		)
	);
}
