/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_module.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:04:02 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 19:06:13 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_MODULE
# define HERE_DOC_MODULE

//* user defined types
# include "../../../types.h"
# include "here_doc_types.h"

# include <unistd.h>


//* entry point

t_status	here_doc_read(char *command);

//* prompt

void	here_doc_prompt(t_hdoc_prompt_behav opcode, char *delimiter,
			char *hdoc_file_name);

//* utils

t_bool	here_doc_line(char *command);;

#endif