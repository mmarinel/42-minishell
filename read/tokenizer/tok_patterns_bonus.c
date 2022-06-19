/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 20:56:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	scan_arg(char **str)
{
}

int	scan_name(char **str, t_op_code	*possible_names)
{
	int	new_offset;

	if (*possible_names == e_NONE)
		return (-1);
	new_offset = scan(&str, *possible_names);
	if (new_offset == -1)
		return (scan_name(str, possible_names + 1));
	else
		return (new_offset);
}

/**
 * @brief this function scans the input string for the next
 * shell variable token and feeds it to the lexer if it is found.
 * 
 * @param str the (eventually shifted) pointer to the line inputted
 * to the prompt
 * @return int the updated offset inside the given input string
 * if the token is found, -1 otherwise
 */
int	scan_shell_var(char *str)
{
	return (scan_var(str, e_SHELL_VAR_NAME));
}

int	scan_env_var(char *str)
{
	if (!str || ft_strncmp(str, "export", 6 * sizeof(char)))
		return (-1);
	return (scan_var(str + 6, e_ENV_VAR_NAME));
}
