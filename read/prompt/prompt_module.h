/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_module.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:29:25 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 18:20:31 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_MODULE_H
# define PROMPT_MODULE_H

// * user defined types //
# include "../../types.h"
# include "prompt_types.h"

// ! non empty means NO CHAR present except '\0'
// ! (i.e.: a string full of spaces is not considered empty!)
/**
 * @brief This function tries to read a line until a non-empty/non-pending 
 * one is entered or ctr + D is hit.
 * Here_Doc is managed too.
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @param free_prompt true iff prompt needs to be freed after use
 * @return char* the next line read
 * (except here_doc content which is put in a hidden file for later use)
 */
char	*ft_read_command(char *main_prompt);

/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
char	*get_current_working_directory(void);

// * WE NEED TO EXPOSE this prototype so that the relative sig-handler
// *in 'signals' module can access it asking to clean memory
// *with appropriate opcode !
void	line_continuation_prompt(t_prompt_behav opcode, char *initial_prompt,
			int line_channel[2], int line_size_channel[2]);

#endif