/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:45:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/16 18:29:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static char	take_starting_quote(char *str);

t_bool	ft_isspace(char c)
{
	return (c == 32 || (c >= '\t' && c <= '\r'));
}

/**
 * @brief this function checks wether the number of occurrences
 * of the first quote occurring in the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_quote_occurrence_balanced(char *str)
{
	char	quote;
	int		occurrences;

	if (!str)
		return (e_true);
	quote = take_starting_quote(str);
	if (quote != '"' && quote != '\'')
		return (e_true);
	occurrences = 0;
	while (*str)
	{
		if (*str == quote)
			occurrences += 1;
		str++;
	}
	return (occurrences % 2 == 0);
}

static char	take_starting_quote(char *str)
{
	while (*str)
	{
		if (*str == '"')
			return ('"');
		if (*str == '\'')
			return ('\'');
		str++;
	}
	return ('\0');
}

// static t_bool	dels_member(char c, int delimiters[])
// {
// 	int	i;

// 	i = -1;
// 	while (delimiters[++i] != -1)
// 		if (c == (char)delimiters[i])
// 			return (e_true);
// 	return (e_false);
// }

// void	ft_lst_multi_split(char *s, int substr_len, t_list **cur, int delimiters[])
// {
// 	char	*substr;

// 	if (!(*s))
// 		return ;
// 	if (dels_member(*s, delimiters))
// 	{
// 		if (substr_len == 0)
// 			ft_lst_multi_split(s + 1, substr_len + 1, cur, delimiters);
// 		else
// 		{
// 			substr = (char *) malloc((substr_len + 1) * sizeof(char));
// 			ft_strcpy(substr, s, substr_len);
// 			substr[substr_len] = '\0';
// 			substr_len = 0;
// 			*cur = (t_list *) malloc(sizeof(t_list));
// 			(*cur)->content = substr;
// 			(*cur)->next = NULL;
// 			ft_lst_multi_split(s + 1, 0, &((*cur)->next), delimiters);
// 		}
// 	}
// 	else
// 		ft_lst_multi_split(s + 1, substr_len + 1, cur, delimiters);
// }

// t_list	*ft_lst_multi_split(char *s, int delimiters[])
// {
// 	t_list	*ret;
// 	char	*substr;
// 	int		substr_len;

// 	if (!s)
// 		return (NULL);
// 	ret = NULL;
// 	substr_len = 0;
// 	while (*s)
// 	{
// 		if (dels_member(*s, delimiters))
// 		{
// 			if (substr_len > 0)
// 			{
// 				substr = (char *) malloc((substr_len + 1) * sizeof(char));
// 				ft_strcpy(substr, s, substr_len);
// 				substr[substr_len] = '\0';
// 				substr_len = 0;
// 			}
// 		}
// 		else if
// 			substr_len++;
// 	}
// }
