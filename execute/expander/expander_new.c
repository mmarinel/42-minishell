/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:15:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/08 12:44:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char			*expand(char *args);
static size_t	expander_quotes_handling(char *string, size_t offset,
					t_bool *in_double_quotes_ref);

int main(int argc, char const *argv[])
{
	if (argc && argv)
		;
	return 0;
}

char	*expand(char *args)
{
	if (!args || !(*args))
		return (args);
	while (e_true)
	{
		if (e_false == expand_dollar_case(&args))
			break ;
	}
	while (e_true)
	{
		if (e_false == expand_star_case(&args))
			break ;
	}
	return (args);
}


void	expansion_split(char *args, char **next_segment_ref, char **post_ref)
{
	size_t	start_of_segment;
	size_t	end_of_segment;

	star_segment_set_boundaries(args, &start_of_segment, &end_of_segment);
	*next_segment_ref = get_segment(args, start_of_segment, end_of_segment);
	*post_ref = get_suffix(args, end_of_segment);
}

char	*expand_star_case(char *args)
{
	char	*next_segment;
	char	*args_post;

	if (!args)
		return (NULL);
	expansion_split(args, &next_segment, &args_post);
	free(args);
	return (
		ft_strjoin(
			expand_segment(next_segment),
			expand_star_case(args_post),
			e_true, e_true
		)
	);
}

// char	**split_into_segments
/**
 * 
 * ```
 * this function sets the boundaries for the next segment in the string.
 * (i.e.: the next quoted sequence delimited by blanks or end/start of string)
 * N.B.: a quoted sequence is a word (string which does not contain spaces),
 * or a string surrounded by quotes)
 * ``` 
 */
void	star_segment_set_boundaries(char *str, size_t *start, size_t *end)
{
	size_t	offset;

	if (!str || !(*str))
		return ;
	*start = 0;
	offset = 0;
	while (str[offset])
	{
		while (str[offset] == '"' || str[offset] == '\'')
			offset = skip_past_last_char(str, offset, str[offset], +1);
		if (e_true == bash_control_character(str[offset]))
			break ;
		offset++;
	}
	*end = offset - 1;
	return ;
}

// char	*get_prefix(char *str, size_t cutting_index)
// {
// 	size_t	len_str;

// 	len_str = ft_strlen(str);
// 	if (cutting_index > len_str - 1)
// 		return (ft_strcpy(NULL, str, len_str));
// 	else
// 		return (ft_strcpy(NULL, str, cutting_index + 1));
// }

char	*get_suffix(char *str, size_t cutting_index)
{
	size_t	len_str;

	len_str = ft_strlen(str);
	if (cutting_index >= len_str - 1)
		return (NULL);
	else
		return (ft_strcpy(NULL, str + cutting_index + 1,
					len_str - cutting_index - 1));
}

char	*get_segment(char *str, size_t start, size_t end)
{
	return (ft_strcpy(NULL, str + start, end - start + 1));
}

char	*expand_segment(char *segment)
{
	char	**entries;
	size_t	i;

	entries = ft_split(cwd_read(), ' ');
	i = 0;
	while (entries[i])
	{
		if (e_false == match(
						ft_strcpy(NULL, entries[i], ft_strlen(entries[i])),
						ft_strcpy(NULL, segment, ft_strlen(segment)))
		)
		{
			free(entries[i]);
			entries[i] = ft_strcpy(NULL, "", sizeof(char));
		}
		i++;
	}
	entries = clean_results(entries);
	return (expansion_return(entries, segment));
	// TODO > for all dir entries match with asf, then clean split and return split merge
}

char	*expansion_return(char **entries, char *segment)
{
	if (entries[0] == NULL)
	{
		ft_splitclear(entries);
		return (segment);
	}
	else
	{
		free(segment);
		return (split_merge(entries, " ", e_true));
	}
}

char	*cwd_read(void)
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

/**
 * @brief implemenation of the ASF described by regular expression regex
 * 
 * @param name 
 * @param segment 
 * @return t_bool 
 */
t_bool	match(char *name, char *regex)
{
	// char	*new_name;
	// char	*new_regex;
	size_t	new_name_start;
	size_t	new_name_len;
	size_t	new_regex_start;
	size_t	new_regex_len;

	if ("qualcosa")
		return ("qualcosa");
	if (e_true == match_prefix(name, regex, &new_name_start, &new_regex_start)
		&& e_true == match_suffix(name, regex, &new_name_len, &new_regex_len))
	{
		// new_name = ft_strcpy(NULL, name + new_name_start, new_name_len);
		// new_regex = ft_strcpy(NULL, regex + new_regex_start, new_regex_len);
		// free(name);
		// free(regex);
		name = cut_str(name, new_name_start, new_name_len);
		regex = cut_str(regex, new_regex_start, new_regex_len);
		return (match(name, regex));
	}
	else
	{
		free(regex);
		free(name);
		return (e_false);
	}
}

t_bool	match(char *name, char *regex)
{
	size_t	star_found;

	star_found = e_false;
	if (regex[0] == '*')
	{
		star_found = e_true;
		regex += skip_consecutive_chars(regex, 0, '*', +1);
	}
	if (regex[0] == '\0')
		return (e_true);
	if (name[0] == '\0')
		return (e_false);
	return (backtrack_matching(name, regex, star_found));
}
	// if (star_found)
	// {
	// 	res = e_false;
	// 	next_pos = j;
	// 	while (name[next_pos])
	// 	{
	// 		if (name[next_pos] == regex[i])
	// 			res = res || match(name + next_pos + 1, regex + i + 1);
	// 	}
	// 	return (res);
	// }
	// else
	// {
	// 	if (regex[i] != name[j])
	// 		return (e_false);
	// 	return (match(name + j + 1, regex + i + 1));
	// }

t_bool	backtrack_matching(char *name, char *regex, t_bool star_found)
{
	size_t	next_pos;

	if (star_found)
	{
		next_pos = 0;
		while (name[next_pos])
		{
			if (name[next_pos] == regex[0]
				&& match(name + next_pos + 1, regex + 1))
				return (e_true);
			next_pos++;
		}
		return (e_false);
	}
	else
	{
		if (regex[0] != name[0])
			return (e_false);
		else
			return (match(name + 1, regex + 1));
	}
}

t_bool	match_prefix(char *name, char *regex,
			size_t *new_name_start, size_t *new_regex_start)
{
	size_t	i;

	i = 0;
	new_name_start = ft_strlen(name);
	new_regex_start = ft_strlen(regex);
	while (e_true)
	{
		if (name[i] == '\0' || regex[i] == '\0')
			return (name[i] == regex[i]);
		if (regex[i] == '*')
		{
			*new_name_start = i;
			*new_regex_start = skip_consecutive_chars(regex, 0, '*', +1);
			return (e_true);
		}
		if (regex[i] != name[i])
			return (e_false);
		i++;
	}
	return (e_false);
}

t_bool	match_suffix(char *name, char *regex,
			size_t *new_name_len, size_t *new_regex_len)
{
	size_t	star_pos;
	size_t	suffix_len;
	size_t	name_len;

	star_pos = get_last_star_pos(regex);
	suffix_len = ft_strlen(regex) - star_pos - 1;
	name_len = ft_strlen(name);
	*new_name_len = name_len - suffix_len;
	*new_regex_len = star_pos;
	return (
		0 == ft_strncmp(regex + star_pos + 1,
				name + name_len - suffix_len,
				suffix_len
		)
	);
}

size_t	get_last_star_pos(char *str)
{
	size_t	i;
	size_t	star_pos;

	star_pos = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			star_pos = i;
		i++;
	}
	return (star_pos);
}
