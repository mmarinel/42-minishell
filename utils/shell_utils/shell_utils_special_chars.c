/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_special_chars.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:26:37 by mmarinel         ###   ########.fr       */
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

t_bool	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

t_bool	ft_is_alpha(char c)
{
	return (
		(c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
	);
}
