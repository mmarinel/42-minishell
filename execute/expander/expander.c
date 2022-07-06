/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/06 18:55:42 by mmarinel         ###   ########.fr       */
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

	expanded = NULL;
	expression = ft_strcpy(NULL, str + start, end - start + 1);
	if (expression[0] == '$')
		;// expanded = expand_dollar_exp(exp, end - start + 1);
	if (expression[0] == '*')
		expanded = ft_strjoin(
						ft_strjoin(
							get_pre(str, start, end),
							expand_star_exp(expression, end - start + 1),
							e_true, e_true),
						get_post(str, end),
						e_true, e_true);
	free(str);
	free(expression);
	return (expanded);
}

char	*star_exp_expansion(char *str, size_t start, size_t end)
{
	int		prefix_start;
	size_t	next_star_pos;
	char	**results;
	size_t	i;

	results = NULL;
	prefix_start = -1;
	next_star_pos = start;
	i = start;
	while (str[i])
	{
		if (str[i] == '*')
		{
			next_star_pos = i;
			results = filter_cwd_entries(&results, str, prefix_start, next_star_pos);
			prefix_start = -1;
		}
		else if (prefix_start == -1)
			prefix_start = i;
		i++;
	}
	results = clean_results(results);
	return (split_merge(results));
}

char	**filter_cwd_entries(char *str,
			int prefix_start, size_t next_star_pos)
{
	static char		**results = NULL;
	static size_t	len_results = 0;
	char			**filtered;
	size_t			i;

	if (!results)
	{
		results = ft_split(match_everything(), ' ');
		len_results = split_len(results);
		return (results); 
	}
	else
	{
		if (prefix_start == -1)
			return (results);
		i = 0;
		while (i < len_results)
		{
			if (e_false == match_prefix(results[i], str, prefix_start, next_star_pos))
			{
				free(results[i]);
				results[i] = NULL;
			}
			i++;
		}
		return (results);
	}
}

char	*get_pre(char *str, size_t start, size_t end)
{
	char	*pre;

	pre = ft_strcpy(NULL, str, start);
	return (pre);
}

char	*get_post(char *str, size_t end)
{
	char	*post;

	post = ft_strcpy(NULL, str + end + 1, ft_strlen(str) - (end + 1));
	return (post);
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
		expanded = match_suffix(post);
	else if (!post)
		expanded = match_prefix(pre);
	else
		expanded = match_superstr(pre, post);
	free(pre);
	free(post);
	return (expanded);
}

char	*match_superstr(char *prefix, char *suffix)
{
	char			*expansion;
	DIR				*cwd;
	struct dirent	*cwd_entry;
	size_t			len_suffix;

	len_suffix = ft_strlen(suffix);
	expansion = NULL;
	cwd = opendir(".");
	if (cwd)
	{
		while (e_true)
		{
			cwd_entry = readdir(cwd);
			if (cwd_entry == NULL)
				break ;
			if (0 == ft_strncmp(cwd_entry->d_name, prefix, ft_strlen(prefix))
				&& 0 == ft_strcmp(normalize_cwd_entry_name_to_suffix_len(
								cwd_entry->d_name, len_suffix), suffix))
				expansion = ft_strjoin(
					ft_strjoin(expansion, " ", e_true, e_false),
					cwd_entry->d_name,
					e_true, e_false
				);
		}
		closedir(cwd);
	}
	return (expansion);
}

char	*match_prefix(char *prefix)
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
			if (0 == ft_strncmp(cwd_entry->d_name, prefix, ft_strlen(prefix)))
				expansion = ft_strjoin(
					ft_strjoin(expansion, " ", e_true, e_false),
					cwd_entry->d_name,
					e_true, e_false
				);
		}
		closedir(cwd);
	}
	return (expansion);
}

char	*match_suffix(char *suffix)
{
	char			*expansion;
	DIR				*cwd;
	struct dirent	*cwd_entry;
	size_t			len_suffix;

	len_suffix = ft_strlen(suffix);
	expansion = NULL;
	cwd = opendir(".");
	if (cwd)
	{
		while (e_true)
		{
			cwd_entry = readdir(cwd);
			if (cwd_entry == NULL)
				break ;
			if (0 == ft_strcmp(normalize_cwd_entry_name_to_suffix_len(
								cwd_entry->d_name, len_suffix), suffix))
				expansion = ft_strjoin(
					ft_strjoin(expansion, " ", e_true, e_false),
					cwd_entry->d_name,
					e_true, e_false
				);
		}
		closedir(cwd);
	}
	return (expansion);
}

char	*normalize_cwd_entry_name_to_suffix_len(char *entry_name, size_t len_suffix)
{
	size_t	len_entry_name;

	if (ft_strlen(entry_name) < len_suffix)
		return (entry_name);
	return (entry_name + len_entry_name - len_suffix);
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
