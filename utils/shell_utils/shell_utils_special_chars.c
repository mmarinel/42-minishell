/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_special_chars.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 16:49:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"
#include "../../read/tokenizer/tok_utils/tok_utils.h"

t_bool	bash_control_character(char c)
{
	return (
		c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '$' || c == '`' || c == '\\' || c == '"' || c == '\''
		|| ft_isspace(c)
	);
}

t_bool	mini_cmd_separator(char c)
{
	return (c == '|' || c == '&');
}

t_bool	redirect_char(char c)
{
	return (c == '>' || c == '<');
}

// ! REMOVE FROM HERE (it's in token utils)
// int	scan_alternate_invariant_spaces_quotes(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (str[idx])
// 	{
// 		// READING ALL INVARIANT QUOTES
// 		while (str[idx] == '"' || str[idx] == '\'')
// 		{
// 			if (str[idx + 1] != str[idx])
// 				break ;
// 			idx += 2;
// 		}
// 		// READING ALL FINAL SPACES
// 		while (str[idx])
// 		{
// 			if (e_false == ft_isspace(str[idx]))
// 				break ;
// 			idx++;
// 		}
// 		if (str[idx] != '"' && str[idx] != '\''
// 			&& e_false == ft_isspace(str[idx]))
// 			break ;
// 	}
// 	return (idx);
// }
