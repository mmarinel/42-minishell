/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_module.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:29:25 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 16:32:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_MODULE_H
# define PROMPT_MODULE_H

# include "../../types.h"

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


/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
char	*get_current_working_directory(void);

#endif