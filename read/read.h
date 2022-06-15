/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/15 22:12:07 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "../includes.h"

// * user defines TYPES

typedef enum e_op_code
{
	e_RETURN_TOK,
	e_STORE_NXT_TOK,
	e_STORE_STR,
	e_RETURN_CUR_STR,
	e_ADVANCE_STR
}	t_op_code;

typedef enum e_token_id
{
	CMD_LIST,
	CMD,
	IDENTIFIER
}	t_token_id;

typedef struct s_token
{
	t_token_id	token_id;
	void		*token_val;
}	t_token;

// * user defined EXPOSED FUNCTIONS

char	*shell_read( char *const envp[]);

#endif