/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:49:32 by earendil          #+#    #+#             */
/*   Updated: 2022/07/16 12:22:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_cases.h"


static char	*expand_dollar_segment(char *next_segment);

// * end of static declarations //


char	*expand_dollar_case(char *args)
{
	char	*next_segment;
	char	*args_post;

	if (!args)
		return (NULL);
	expansion_split(DOLLAR, args, &next_segment, &args_post);
	free(args);
	printf("arg post:%s\n", args_post);
	return (
		ft_strjoin(
			expand_dollar_segment(next_segment),
			expand_dollar_case(args_post),
			e_true, e_true
		)
	);
}

static char	*expand_dollar_segment(char *next_segment)
{
	char	*expansion;
	size_t	seg_len;

	seg_len = ft_strlen(next_segment);
	if (next_segment[0] == '"')
	{
		expansion = expand_dollar_case(
				ft_strcpy(NULL, next_segment + 1, seg_len - 2)
		);
	}
	else if (next_segment[0] == '\'')
	{
		expansion = ft_strcpy(NULL, next_segment + 1, seg_len - 2);
	}
	else if (next_segment[0] != '$')
	{
		expansion = ft_strdup(next_segment);
	}
	else
	{
		expansion = env_handler(BINDING_GET_VALUE, next_segment + 1);
	}
	free(next_segment);
	return (expansion);
}
