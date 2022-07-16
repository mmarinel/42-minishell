/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:16:31 by earendil          #+#    #+#             */
/*   Updated: 2022/07/16 18:23:46 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_cases.h"


// * pattern matching //
static t_bool	match(char *name, char *uninterpreted_prefix, char *regex);
static t_bool	backtrack_matching(char *name, char *regex,
					t_bool star_found);

// * expansion of segment //

static char		*expand_star_segment(char *segment);
static char		*expansion_return(char **entries, char *segment);


// * end of static declarations //


char	*expand_star_case(char *args)
{
	char	*next_segment;
	char	*args_post;

	if (!args)// * || !(*args)
		return (NULL);
	expansion_split(STAR, args, &next_segment, &args_post);
	free(args);
	return (
		ft_strjoin(
			expand_star_segment(next_segment),
			expand_star_case(args_post),
			e_true, e_true
		)
	);
}

static char	*expand_star_segment(char *segment)
{
	char	**entries;
	char	*uninterpreted_prefix;
	size_t	offset;
	size_t	i;

	offset = parse_uninterpreted_prefix(segment, &uninterpreted_prefix);
	{
		entries = ft_split(cwd_read(), ' ');
		i = 0;
		while (entries[i])
		{
			if (e_false == match(entries[i], uninterpreted_prefix,
					segment + offset))
			{
				free(entries[i]);
				entries[i] = ft_strcpy(NULL, "", sizeof(char));
			}
			i++;
		}
		entries = clean_results(entries);
		return (expansion_return(entries, segment));
	}
}

static char	*expansion_return(char **entries, char *segment)
{
	char	*ret;
	char	*prefix_uninterpreted;
	size_t	suffix_offset;

	if (entries[0] == NULL)
	{
		ft_splitclear(entries);
		ret = ft_strdup(segment);
	}
	else
	{
		ret = (split_merge(entries, " ", e_true));
	}
	free(segment);
	return (ret);
}

	// if (entries == NULL)
	// {
	// 	suffix_offset = skip_past_char(segment, 0 + 1, segment[0], +1);
	// 	prefix_uninterpreted = string_strip(
	// 		ft_strcpy(NULL, segment, suffix_offset),
	// 		segment[0], e_true
	// 	);
	// 	ret = expand_star_segment(
	// 		ft_strjoin(,
	// 			ft_strdup(segment + suffix_offset),
	// 			e_true, e_true
	// 		)
	// 	);
	// }
static t_bool	match(char *name, char *uninterpreted_prefix, char *regex)
{
	size_t	star_found;

	star_found = e_false;
	if (uninterpreted_prefix)
		if (0 != ft_strncmp(name, uninterpreted_prefix,
				ft_strlen(uninterpreted_prefix)))
			return (e_false);
	if (regex[0] == '*')
	{
		star_found = e_true;
		regex += skip_consecutive_chars(regex, 0, '*', +1);
	}
	if ((regex[0] == '\0' && star_found)
		|| (regex[0] == '\0' && name[0] == '\0'))
		return (e_true);
	if (name[0] == '\0')
		return (e_false);
	return (backtrack_matching(name, regex, star_found));
}

static t_bool	backtrack_matching(char *name, char *regex,
					t_bool star_found)
{
	size_t	next_pos;

	if (star_found)
	{
		next_pos = 0;
		while (name[next_pos])
		{
			if (name[next_pos] == regex[0]
				&& match(name + next_pos + 1, NULL, regex + 1))
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
			return (match(name + 1, NULL, regex + 1));
	}
}
