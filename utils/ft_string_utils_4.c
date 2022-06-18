/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:16:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/18 18:21:03 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

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
	word[word_len] = '\0';
	ft_strcpy(word, str, word_len);
	return (word);
}
