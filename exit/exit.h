/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:11:39 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:23:34 by mmarinel         ###   ########.fr       */
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

void	exit_shell(int exit_status);
void	rl_clear_history(void);

#endif