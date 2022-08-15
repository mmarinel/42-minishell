/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:07:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:44:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

//* system libraries //
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>

//* readline library
# include <readline/readline.h>
# include <readline/history.h>

//* user defined module //
# include "../../../signals/signal_module.h"
# include "../../../utils/ft_utils.h"
# include "../../../execute/expander/expander_module.h"

//* user defined types //
# include "../../../types.h"
# include "../../../global.h"
# include "here_doc_types.h"

//* prompt

void	here_doc_prompt(t_hdoc_prompt_behav opcode, char enclosing_quote,
			char *delimiter,
			char *hdoc_file_name);
//* utils

size_t	here_docs_count(char *command);
char	**here_doc_take_delimiters(char *command);
t_bool	here_doc_line(char *command);

#endif