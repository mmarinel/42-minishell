/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/10 16:33:09 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*expand_rec(char *args,
				char containing_quotes);
static char	*expand_segment(char *segment, char containing_quotes);
static char	*expand_quoted_sequence(char *pre, char *post,
				char seg_enclosing_quote,
				char containing_quote);
static char	*expand_segment_preserve_quotes(char *segment,
				char seg_enclosing_quote,
				char containing_quote);
//* end of static declarations

char	*expand(char *args)
{
	if (!args || !(*args))
		return (args);
	return (expand_rec(args, '\0'));
}

static char	*expand_rec(char *args,
				char containing_quotes)
{
	char	*next_segment;
	char	*args_post;

	if (NULL == args || args[0] == 0)
		return (NULL);
	expansion_split(args, &next_segment, &args_post);
	printf("next_seg: %s\targs_post: %s\n", next_segment, args_post);
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
	char	*pre;
	char	*post;

	seg_enclosing_quote = get_seg_enclosing_quote(segment, &pre, &post);
	if (seg_enclosing_quote)
	{
		return (expand_quoted_sequence(pre, post,
			seg_enclosing_quote,
			containing_quote));
	}
	else
	{
		segment = expand_dollar_segment(segment, containing_quote);
		segment = expand_star_segment(segment, containing_quote);
		return (segment);
	}
}

static char	*expand_quoted_sequence(char *pre, char *post,
				char seg_enclosing_quote,
				char containing_quote)
{
	char	*expansion;

	if (seg_enclosing_quote == containing_quote || 0 == containing_quote)
	{
		expansion = expand_rec(pre, seg_enclosing_quote);
		if (post)
			return (expand_star_segment(
				ft_strjoin(expansion, post, e_true, e_true),
				containing_quote));
		else
			return (expansion);
	}
	else
		expansion = (expand_segment_preserve_quotes(pre,
			seg_enclosing_quote,
			containing_quote));
	return (expansion);
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
