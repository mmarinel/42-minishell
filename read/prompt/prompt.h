/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:43:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 12:30:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "../read.h"
#include "prompt_utils/prompt_utils.h"

// ! non empty means NO CHAR present except '\0'
// ! (i.e.: a string full of spaces is not considered empty!)
/**
 * @brief This function tries to read a line until a non empty-quote balanced 
 * one is entered or ctr + D is hit.
 * Here_Doc is managed too.
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @param free_prompt true iff prompt needs to be freed after use
 * @return char* the next line read
 * (except here_doc content which is put in a hidden file for later use)
 */
char	*ft_readline(char *prompt, t_bool free_prompt);

// TODO :-> return EXIT CODE 258 for ctrl + D
// TODO :-> while trying to complete line (exit/errors module)
char		*prompt_complete_line(char *command);

/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
char	*get_current_working_directory(void);

#endif