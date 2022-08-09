/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:49:32 by earendil          #+#    #+#             */
/*   Updated: 2022/08/09 19:39:26 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_cases.h"

char	*expand_dollar_segment(char *next_segment,
				char containing_sequence)
{
	char	*expansion;

	printf("HERE");
	if (!next_segment)
		return (NULL);
	if (containing_sequence != '\'')
	{
		if (next_segment[0] != '$')
			expansion = ft_strdup(next_segment);
		else if (next_segment[0] == '$' && next_segment[1] == '$')
			expansion = ft_itoa(g_env.pid);
		else if (next_segment[0] == '$' && next_segment[1] == '?')
			expansion = ft_itoa(g_env.last_executed_cmd_exit_status);
		else
			expansion = env_handler(BINDING_GET_VALUE, next_segment + 1);
	}
	else
	{
		expansion = ft_strdup(next_segment);
	}
	free(next_segment);
	printf("expansion is %s\tlen is: %zu\n", expansion, ft_strlen(expansion));
	return (expansion);
}
