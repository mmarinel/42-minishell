/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:01:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 16:44:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//* user defined modules //
# include "../executor.h"
#include "../../libft/simple_printf/ft_printf_module.h"

void	_execute_env_statement(t_env_decl_node env_statement);
void	execute_export(void);
void	execute_env(void);
void	execute_unset(void);

void	execute_exit(t_simple_command_node cmd);
void	execute_pwd(t_simple_command_node cmd);
void	execute_cd(t_simple_command_node cmd);
void	execute_echo(t_simple_command_node cmd);

#endif