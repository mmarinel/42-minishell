/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:45:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 18:59:06 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief this function checks wether the number of occurrences
 * of the first quote occurring in the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_quote_occurrence_balanced(char *str)
{
	// char	quote;
	// int		occurrences;

	return (
			str_number_occurrences(str, '\'') % 2 == 0
		&&
			str_number_occurrences(str, '"') % 2 == 0
	);
	// if (!str)
	// 	return (e_true);
	// quote = take_starting_quote(str);
	// if (quote != '"' && quote != '\'')
	// 	return (e_true);
	// occurrences = 0;
	// while (*str)
	// {
	// 	if (*str == quote)
	// 		occurrences += 1;
	// 	str++;
	// }
	// return (occurrences % 2 == 0);
}

char	take_starting_quote(char *str)
{
	if (!str)
		return ('\0');
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

char	*ft_itoa(int nbr)
{
	char	digit[2];

	if (nbr == INT_MIN)
		return (ft_strjoin(
				ft_itoa(INT_MIN / 10),
				ft_itoa((INT_MAX % 10) + 1), e_true, e_true));
	if (nbr < 0)
		return (ft_strjoin("-", ft_itoa(-nbr), e_false, e_true));
	digit[0] = (nbr % 10) + 48;
	digit[1] = '\0';
	if (nbr > 9)
		return (ft_strjoin(ft_itoa(nbr / 10), digit, e_true, e_false));
	return (ft_strjoin("", digit, e_false, e_false));
}

/**
 * @brief true iff str is a string containing
 * only digits and whitespace characters.
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_is_digit_string(char *str)
{
	size_t	offset;

	if (str == NULL)
		return (e_false);
	offset = 0;
	if (str[offset] == '+'
		|| str[offset] == '-')
		offset += 1;
	while(str[offset])
	{
		if (e_false == char_is_digit(str[offset])
			&& e_false == ft_isspace(str[offset]))
			return (e_false);
		offset += 1;
	}
	return (e_true);
}

/**
 * @brief true iff str is a string containing
 * only alphanumeric and whitespace characters.
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_is_alpha_string(char *str)
{
	size_t	offset;

	if (str == NULL)
		return (e_false);
	offset = 0;
	while(str[offset])
	{
		if (e_false == char_is_alpha(str[offset])
			&& e_false == ft_isspace(str[offset]))
			return (e_false);
		offset += 1;
	}
	return (e_true);
}

t_bool	ft_is_alphanumeric_string(char *str)
{
	size_t	offset;

	if (str == NULL)
		return (e_false);
	offset = 0;
	while(str[offset])
	{
		if (e_false == char_is_alpha(str[offset])
			&& e_false == char_is_digit(str[offset])
			&& e_false == ft_isspace(str[offset]))
			return (e_false);
		offset += 1;
	}
	return (e_true);
}
