/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:49:32 by earendil          #+#    #+#             */
/*   Updated: 2022/08/10 16:52:05 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_cases.h"

static void		dollar_exp_split(char *next_segment,
					char **var_name_ref,
					char **exp_post_ref);
static size_t	str_member(char *str, char c);
//* end of static declarations

char	*expand_dollar_segment(char *next_segment,
				char containing_sequence)
{
	char	*expansion;
	char	*var_name;
	char	*exp_post;

	if (!next_segment)
		return (NULL);
	dollar_exp_split(next_segment, &var_name, &exp_post);
	if (containing_sequence != '\'')
	{
		if (var_name[0] == '$' && var_name[1] == '\0')
			expansion = ft_strdup("$");
		else if (var_name[0] != '$')
			expansion = ft_strdup(var_name);
		else if (var_name[0] == '$' && var_name[1] == '$')
			expansion = ft_itoa(g_env.pid);
		else if (var_name[0] == '$' && var_name[1] == '?')
			expansion = ft_itoa(g_env.last_executed_cmd_exit_status);
		else
			expansion = env_handler(BINDING_GET_VALUE, var_name + 1);
	}
	else
	{
		expansion = ft_strdup(var_name);
	}
	return (ft_strjoin(expansion, exp_post, e_true, e_true));
}

static void	dollar_exp_split(char *next_segment,
				char **var_name_ref,
				char **exp_post_ref)
{
	size_t	next_star_occ_offset;
	size_t	seg_len;

	seg_len = ft_strlen(next_segment);
	if (seg_len == 2
		|| ft_is_quote(next_segment[0])
		|| e_true == ft_isspace(next_segment[0]))
	{
		*var_name_ref = ft_strdup(next_segment);
		*exp_post_ref = NULL;
	}
	else
	{
		next_star_occ_offset = str_member(next_segment, '*');
		*var_name_ref = ft_strcpy(NULL,
							next_segment,
							next_star_occ_offset);
		*exp_post_ref = ft_strcpy(NULL,
							next_segment + next_star_occ_offset,
							seg_len - next_star_occ_offset + 1);
	}
	free(next_segment);
}

static size_t	str_member(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}
