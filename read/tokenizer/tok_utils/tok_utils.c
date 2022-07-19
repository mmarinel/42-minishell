/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 12:20:42 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

static void	free_tok_list_rec(t_token *token);

size_t	bash_next_quoted_seq(char *command_line, size_t offset, char quote);

// * end of declarations //


/**
 * @brief this function adds the given token to the end of the current
 * list of tokens (circular list only on prev pointers)
 * 
 * @param token_list the address of the first element in the list
 * @param token the next token to store or NULL to close the list
 */
void	tok_add_back(t_token **token_list, t_token *token)
{
	static t_token	*tail = NULL;

	// if (token->token_id != e_OUT_FILE_APPEND)
		// printf("added token: %s\n", tok_to_string(token));
	if (!(*token_list))
	{
		*token_list = token;
		tail = *token_list;
	}
	else
	{
		tail->next = token;
		tail = tail->next;
	}
	tail->next = NULL;
	// token->to_string = tok_to_string;
}

void	free_tok_list(t_token **token_list)
{
	if (*token_list)
	{
		free_tok_list_rec(*token_list);
		*token_list = NULL;
	}
}

static void	free_tok_list_rec(t_token *token)
{
	if (token->next)
		free_tok_list_rec(token->next);
	free(token);
}

char *tok_to_string(t_token *token)
{
	if (token->token_id == e_CMD_NAME)
		return ("CMD_NAME");//(token->token_val);
	if (token->token_id == e_CMD_ARG)
		return ("CMD_ARG");
	if (token->token_id == e_IN_FILE_TRUNC)
		return ("IN_FILE_TRUNC");
	if (token->token_id == e_HERE_DOC)
		return ("HERE_DOC");
	if (token->token_id == e_OUT_FILE_TRUNC)
		return ("OUT_FILE_TRUNC");
	if (token->token_id == e_OUT_FILE_APPEND)
		return ("OUT_FILE_APPEND");
	if (token->token_id == e_OPERATOR)
		return ("OPERATOR");
	if (token->token_id == e_ENV_VAR_DECL)
		return ("ENV_VAR_DECL");
	if (token->token_id == e_ENV_VAR_UNSET)
		return ("ENV_VAR_UNSET");
	if (token->token_id == e_PARENTHESIS)
		return ("PARENTHESIS");
	return (NULL);
}

void	print_token(t_token *token)
{
	char	*id;

	id = "NONE";
	if (token->token_id == e_NONE)
		id = "NONE";
	if (token->token_id == e_CMD_NAME)
	{
		id = BOLDGREEN "CMD_NAME" RESET;
		printf("%s ", id);
		printf("var_name: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_CMD_ARG)
	{
		id = BOLDYELLOW "CMD_ARG" RESET;
		printf("%s ", id);
		printf("var_arg: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_IN_FILE_TRUNC)
	{
		id = BOLDBLUE "IN_FILE_TRUNC" RESET;
		printf("%s ", id);
		printf("in file: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_HERE_DOC)
	{
		id = BOLDBLUE "HERE_DOC" RESET;
		printf("%s ", id);
		printf("in file: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_OUT_FILE_APPEND)
	{
		id = BOLDBLUE "OUT_FILE_APPEND" RESET;
		printf("%s ", id);
		printf("out file: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_OUT_FILE_TRUNC)
	{
		id = BOLDBLUE "OUT_FILE_TRUNC" RESET;
		printf("%s ", id);
		printf("out file: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_OPERATOR)
	{
		id = BOLDRED "OPERATOR" RESET;
		printf("%s ", id);
		printf("operator: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	if (token->token_id == e_ENV_VAR_DECL)
	{
		id = BOLDMAGENTA "ENV_VAR_DECL" RESET;
		printf("%s ", id);
		t_bindings	*var_cont;

		var_cont = (t_bindings *)token->token_val;
		printf("\n");
		while (var_cont)
		{
			printf("var name: %s\tvar val: %s\tconcat_mode: %d\n", var_cont->var_name, var_cont->var_val, (int)(var_cont->concat_mode));
			printf("len_name: %zu; len_val: %zu\n", ft_strlen(var_cont->var_name), ft_strlen(var_cont->var_val));
			var_cont = var_cont->next;
		}
	}
	if (token->token_id == e_ENV_VAR_UNSET)
	{
		id = BOLDMAGENTA "ENV_VAR_UNSET" RESET;
		printf("%s ", id);
		t_bindings	*var_cont;

		var_cont = (t_bindings *)token->token_val;
		printf("\n");
		while (var_cont)
		{
			printf("var name: %s\tvar val: %s\tconcat_mode: %d\n", var_cont->var_name, var_cont->var_val, (int)(var_cont->concat_mode));
			printf("len_name: %zu; len_val: %zu\n", ft_strlen(var_cont->var_name), ft_strlen(var_cont->var_val));
			var_cont = var_cont->next;
		}
	}
	if (token->token_id == e_PARENTHESIS)
	{
		id = BOLDCYAN "PARENTHESIS" RESET;
		printf("%s ", id);
		printf("parenthesis: %s; len %zu\n", (char *)token->token_val, ft_strlen((char *)token->token_val));
	}
	// printf("%s ", id);
}

// /**
//  * @brief this function scan the next word delimited by invariant chars
//  * (i.e.: consecutive spaces optionally followed by empty quotes)
//  * and consisting of contiguous quoted sequences
//  * ending with a bash control character. 
//  * (i.e.: a quoted sequence is a sequence of chars delimited by quotes
//  * or a single word delimited by bash control characters except quotes)
//  * 
//  * @param command_line 
//  * @param offset current offste inside command line
//  * @return size_t the lenght of the next bash word
//  */
// size_t	bash_next_word_len(char *command_line, size_t offset)
// {
// 	size_t	len_word;
// 	size_t	invariant_chars;

// 	// invariant_chars = scan_invariants(command_line, offset);
// 	invariant_chars = skip_consecutive_chars(command_line, offset, ' ', +1);
// 	// offset = scan_invariants(command_line, offset);
// 	// invariant_chars = offset;
// 	// while (ft_is_quote(command_line[offset]))
// 	// 	offset = skip_past_char(command_line, offset + 1, command_line[offset],
// 	// 				+1);
// 	{
// 		// len_word = offset - invariant_chars;
// 		len_word = 0;
// 		while (command_line[invariant_chars + len_word])
// 		{
// 			while (ft_is_quote(command_line[invariant_chars + len_word]))
// 					len_word = skip_past_char(
// 						command_line + invariant_chars,
// 						len_word + 1,
// 						command_line[invariant_chars + len_word],
// 						+1);
// 			if (e_true == bash_control_character(
// 							command_line[invariant_chars + len_word]))
// 				break ;
// 			len_word++;
// 		}
// 		return (len_word);
// 	}
//}

size_t	bash_next_quoted_seq(char *command_line, size_t offset, char quote) //* next_quote_sequence_len
{
	size_t	idx;

	idx = offset;
	while (command_line[idx])
	{
		if (command_line[idx] == quote)
		{
			return (1 + (idx - offset + 1));
		}
		idx++;
	}
	return (0);
}

t_bool	is_env_statement(char *command_line, size_t offset)
{
	size_t	i;
	size_t	len_command_line;

	offset = scan_invariants(command_line, offset);
	i = offset;
	while (command_line[i]
			&& e_false == bash_control_character(command_line[i]))
	{
		if (command_line[i] == '=')
			return (e_true);
		i += 1;
	}
	len_command_line = ft_strlen(command_line + offset);
	if ((ft_strncmp(command_line + offset, "export", 6) == 0
			&& len_command_line >= 6
			&& e_true == ft_isspace(command_line[offset + 6]))
		|| (ft_strncmp(command_line + offset, "unset", 5) == 0
			&& len_command_line >= 5
			&& e_true == ft_isspace(command_line[offset + 5])))
		return (e_true);
	return (e_false);
}
