/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/14 18:59:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*expand_rec(char *args,
				char containing_quotes);
static char	*expand_segment(char *segment, char containing_quotes);
static char	*expand_quoted_sequence(char *pre, char *post,
				char seg_enclosing_quote,
				char containing_quote);
//* end of static declarations

char	*expand(char *args)
{
	char	*expansion;

	expansion = expand_rec(args, '\0');
	if (command_is_empty(expansion))
	{
		free(expansion);
		return (NULL);
	}
	else
		return (expansion);
}

static char	*expand_rec(char *args,
				char containing_quotes)
{
	char	*next_segment;
	char	*args_post;

	if (NULL == args || args[0] == 0)
	{
		ft_free(args);
		return (NULL);
	}
	expansion_split(args, &next_segment, &args_post);
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

	seg_enclosing_quote = split_quoted_sequence(segment, &pre, &post);
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
	char	*enclosing_quote_as_string;

	enclosing_quote_as_string = quote_as_string(seg_enclosing_quote);
	if (seg_enclosing_quote == containing_quote || 0 == containing_quote)
	{
		expansion = expand_rec(pre, seg_enclosing_quote);
		if (post)
			return (
				expand_star_segment(
					ft_strjoin(expansion, post, e_true, e_true),
					containing_quote));
		else
			return (expansion);
	}
	else
	{
		expansion = expand_rec(pre, containing_quote);
		expansion = ft_strjoin(
				enclosing_quote_as_string,
				ft_strjoin(expansion, enclosing_quote_as_string,
					e_true, e_false),
				e_false, e_true);
	}
	return (expansion);
}
