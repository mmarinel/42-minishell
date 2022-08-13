/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:16:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 16:25:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief this function takes the next word
 * (i.e.: anything except isspace characters)
 * starting from the current position of char pointer 'str'
 * 
 * @param str 
 * @return char* 
 */
char	*take_next_word(char *str)
{
	char	*word;
	int		i;
	int		word_len;

	i = 0;
	while (e_false == ft_isspace(str[i])
		&& str[i])
		i++;
	word_len = i;
	word = (char *) malloc((word_len + 1) * sizeof(char));
	// printf(YELLOW "malloc in ft_string_utils_4.c line 35: %p\n" RESET, word);
	// fflush(stdout);
	word[word_len] = '\0';
	ft_strcpy(word, str, word_len);
	return (word);
}

t_bool	char_is_alpha(char c)
{
	return (
		(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	);
}

t_bool	char_is_digit(char c)
{
	return (
		c >= '0' && c <= '9'
	);
}

/**
 * @brief this function returns a new allocated string
 * corresponding to the portion [0, delim_index) of string 'str',
 * where 'delim_index' stands for the index of the first occurrence of
 * char 'delimiter' inside string 'str'.
 * (If no occurrences are found, a duplicate of string
 * 'str' is stored in the new string)
 * 
 * @param str 
 * @param delimiter 
 * @return char* the new allocated string.
 */
char	*ft_substr(char *str, char delimiter)
{
	char	*substr;
	size_t	len_substr;

	substr = NULL;
	len_substr = 0;
	while (str[len_substr])
	{
		if (str[len_substr] == delimiter)
			break ;
		len_substr++;
	}
	if (len_substr == 0)
		return (NULL);
	substr = ft_strcpy(substr, str, len_substr);
	return (substr);
}

char	*str_strip_spaces(char *str)
{
	char	*stripped;

	stripped = string_strip(str, ' ', e_false);
	stripped = string_strip(stripped, '\t', e_true);
	stripped = string_strip(stripped, '\n', e_true);
	stripped = string_strip(stripped, '\v', e_true);
	stripped = string_strip(stripped, '\f', e_true);
	stripped = string_strip(stripped, '\r', e_true);
	return (stripped);
}
