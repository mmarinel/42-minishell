/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_module.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:13:40 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/11 17:41:19 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_MODULE_H
# define EXIT_MODULE_H

# include "../types.h"

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, t_bool explicit_exit);

// void	exit_command_subshell(int exit_status, char *message);

#endif
