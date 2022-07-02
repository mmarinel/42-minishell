/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:00:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 10:05:05 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

/**
 * @brief this function adds 'command' to the history of commands 
 * iff it's not an empty string or already present.
 * 
 * @param command a quote balanced command string
 * @return char** the address of the last stored entry in the history.
 */
char	**ft_add_history(char *command)
{
	static char	*last = NULL;

	if (command)
	{
		if (str_not_empty(command)
			&& (!last || ft_strncmp(command, last, ft_strlen(last)))
		)
		{
			add_history(command);
			ft_free(last);
			last = NULL;
			last = ft_strcpy(last, command, ft_strlen(command));
		}
	}
	return (&last);
}
