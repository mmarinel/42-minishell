/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/09 19:56:36 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
//!													Forse non usare cotaining_sequence gia da qui
static char	*expand_rec(char *args,
				char containing_quotes);
static char	*expand_segment(char *segment, char containing_quotes);
static char	*expand_segment_preserve_quotes(char *segment,
				char seg_enclosing_quote,
				char containing_quote);
//* end of static declarations

char	*expand(char *args)
{
	if (!args || !(*args))
		return (args);
	printf("args: %s\tlen: %zu\n", args, ft_strlen(args));
	char	*s = expand_rec(args, '\0');
	printf("final expansion: %s\tlen: %zu\n", s, ft_strlen(s));
	return (s);
}

static char	*expand_rec(char *args,
				char containing_quotes)
{
	char	*next_segment;
	char	*args_post;

	// printf("HERE\n");
	if (NULL == args || args[0] == 0)
		return (NULL);
	expansion_split(args, &next_segment, &args_post);
	printf("next seg: %s\targs_post: %s\n", next_segment, args_post);
	free(args);
	return (
		ft_strjoin(
			expand_segment(next_segment, containing_quotes),
			expand_rec(args_post, containing_quotes),
			e_true, e_true
		)
	);
}

static char	*expand_segment(char *segment, char containing_quote)
{
	char	seg_enclosing_quote;

	seg_enclosing_quote = get_seg_enclosing_quote(segment);
	if (seg_enclosing_quote)
	{
		ft_str_replace(&segment,
					ft_strcpy(NULL, segment + 1, ft_strlen(segment) - 2)
		);
		printf("jcckljskljck--------0 %s\tlen is: %zu\n", segment, ft_strlen(segment));
		if (seg_enclosing_quote == containing_quote
			|| 0 == containing_quote)
		{
			printf("AQUIIIII\n");
			return (expand_rec(segment, seg_enclosing_quote));
		}
		else
			return (expand_segment_preserve_quotes(segment,
				seg_enclosing_quote,
				containing_quote));
	}
	else
	{
		segment = expand_dollar_segment(segment, containing_quote);
		if (segment)
			printf("segment is %s\tlen is: %zu\n", segment, ft_strlen(segment));
		// segment = expand_star_case(segment, containing_quotes);
	}
	return (segment);
}

static char	*expand_segment_preserve_quotes(char *segment,
				char seg_enclosing_quote,
				char containing_quote)
{
	char	*quote;

	if (seg_enclosing_quote == '\'')
		quote = "\'";
	else
		quote = "\"";
	{
		return (
			ft_strjoin(
				quote,
				ft_strjoin(
					expand_rec(segment, containing_quote),
					quote,
					e_true, e_false
				),
				e_false, e_true
			)
		);
	}
}
