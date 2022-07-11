/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:49:32 by earendil          #+#    #+#             */
/*   Updated: 2022/07/09 19:50:23 by earendil         ###   ########.fr       */
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

	if (next_segment[0] != '$')
		return (next_segment);
	return (next_segment);
	// expansion = env_handler(BINDING_GET_VALUE, next_segment + 1);
	// free(next_segment);
	// return (expansion);
}
