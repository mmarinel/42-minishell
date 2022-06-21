/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/21 10:15:44 by mmarinel         ###   ########.fr       */
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

// ! NON CI SERVONO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	str += scan_spaces(str);
	return (scan_var(str, e_SHELL_VAR_NAME));
}

int	scan_env_var(char *str)
{
	str += scan_spaces(str);
	str += scan_invariant_quotes(str);
	if (!str || ft_strncmp(str, "export", 6 * sizeof(char)))
		return (-1);
	return (scan_var(str + 6, e_ENV_VAR_NAME));
}

int	scan_option(char *str)
{
	t_token	*token;
	char	*opt;
	int		len_opt;

	if (!str || *str != '-')
		return (-1);
	opt = str + 1;
	len_opt = 0;
	while (e_false == bash_control_character(opt[len_opt]))
		len_opt++;
	if (len_opt == 0)
		return (-1);
	opt = ft_strcpy(opt, str, len_opt);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_OPT;
	token->token_val = opt;
	lexer(token, e_STORE_NXT_TOK);
	return (len_opt);
}

int	scan_inout_file(char *str, t_token_id in_out_)
{
	t_token	*token;
	size_t	len_file_name;

	if (*str != '<')
		return (-1);
	// REMOVING SPACES
	str += scan_spaces(str);
	if (!(*str))
		return (-1);
	// TAKING FILE NAME
	len_file_name = 0;
	while (e_false == bash_control_character(str[len_file_name])
		&& str[len_file_name])
		len_file_name++;
	if (len_file_name == 0)
		return (-1);
	// TOKEN RECOGNIZED !
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = in_out_;
	token->token_val = ft_strcpy(NULL, str, len_file_name);
	lexer(token, e_STORE_NXT_TOK);
	return (len_file_name);
}

/**
 * @brief ASF to recognize &&, ||, | only
 * 
 * @param str 
 * @return int 
 */
int	scan_operator(char *str)
{
	t_token	*token;

	if (!str)
		return (-1);
	str = scan_spaces(str);
	if (*str = '|' || *str != '&')
		return (-1);
	if (*str == '&' && *(str + 1) != '&')
		return (-1);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_OPERATOR;
	if (*str == '&')
		token->token_val = "&&";
	if (*str == '|' && *str != '|')
		token->token_val = "|";
	else
		token->token_val = "||";
	lexer(token, e_STORE_NXT_TOK);
	return (ft_strlen((char *)token->token_val));
}
