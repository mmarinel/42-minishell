/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/06 16:14:37 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	expander_quotes_handling(char *string, size_t offset,
					t_bool *in_double_quotes_ref);

// * end of static declarations //


char	*expander(char *args)
{
	size_t	expansion_start;
	size_t	expansion_end;
	size_t	cur_offset;

	cur_offset = 0;
	while (e_true == is_expandable(args + cur_offset,
			&expansion_start,
			&expansion_end)
	)
	{
		args = expand(args, expansion_start, expansion_end);
		cur_offset = expansion_end + 1;
		if (args[cur_offset] == '\0')
			break ;
	}
	return (args);
}

t_bool	is_expandable(char *string,
			size_t *start_ref,
			size_t *end_ref)
{
	size_t	i;
	t_bool	in_double_quotes;

	if (!string)
		return (e_false);
	in_double_quotes = e_false;
	i = 0;
	while (string[i])
	{
		i = expander_quotes_handling(string, i, &in_double_quotes);
		if (string[i] == '*' || string[i] == '$')
		{
			if (string[i] == '*' && e_false == in_double_quotes)
				if (star_case(string, &i, start_ref, end_ref))
					return (e_true);
			if (string[i] == '$')
				if (dollar_case(string, &i, start_ref, end_ref))
					return (e_true);
		}
		else
			i++;
	}
	*end_ref = i;
	return (e_false);
}


static size_t	expander_quotes_handling(char *string, size_t offset,
					t_bool *in_double_quotes_ref)
{
	if (string[offset] == '"')
	{
		offset = skip_consecutive_quotes(string, offset, '"');
		flip(in_double_quotes_ref);
	}
	else if (string[offset] == '\'' && e_false == *in_double_quotes_ref)
	{
		offset = skip_consecutive_quotes(string, offset, '\'');
		offset = skip_past_last_quote(string, offset, '\'', +1);
	}
	return (offset);
}

char	*expand(char *str, size_t start, size_t end)
{
	char	*expression;
	char	*expanded;

	expression = ft_strcpy(NULL, str + start, end - start + 1);
	if (expression[0] == '$')
		;// expanded = expand_dollar_exp(exp, end - start + 1);
	if (expression[0] == '*')
		expanded = expand_star_exp(expression, end - start + 1);
	free(str);
	free(expression);
	return (expanded);
}

char	*expand_star_exp(char *exp, size_t len_exp)
{
	char	*expanded;
	char	*pre;
	char	*post;
	size_t	star_pos;

	star_pos = take_star_pos(exp);
	pre = take_star_exp_prefix(exp, star_pos);
	post = take_star_exp_suffix(exp, star_pos);
	if (!pre && !post)
		expanded = match_everything();
	else if (!pre)
		expanded = match_suffix(exp, post);
	else if (!post)
		expanded = match_prefix(exp, pre);
	else
		expanded = match_supstr(exp, pre, post);
	free(pre);
	free(post);
	return (expanded);
}

char	*match_everything(void)
{
	char			*expansion;
	DIR				*cwd;
	struct dirent	*cwd_entry;

	expansion = NULL;
	cwd = opendir(".");
	if (cwd)
	{
		while (e_true)
		{
			cwd_entry = readdir(cwd);
			if (cwd_entry == NULL)
				break ;
			expansion = ft_strjoin(
				ft_strjoin(expansion, " ", e_true, e_false),
				cwd_entry->d_name,
				e_true, e_false
			); // (pre, post, sep)
		}
		closedir(cwd);
	}
	return (expansion);
}
