/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:11:39 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 16:13:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

// * stadard libraries //
# include <readline/readline.h>
# include <readline/history.h>

// * user defined modules //
# include "../signals/signal_module.h"
# include "../read/prompt/prompt_utils/prompt_utils.h"
# include "../env/env_module.h"

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status);

void rl_clear_history (void);

// void	exit_command_subshell(int exit_status, t_tree_node *parse_tree);

#endif