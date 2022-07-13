/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:02:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 16:51:35 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MODULE_H
# define ENV_MODULE_H

# include "env_types.h"

// *main exposed function//
void	*env_handler(t_env_handl_opcode opcode, void *argument);

// *utils //
t_bindings	*get_new_binding(char *var_name, char *var_val, t_bool concat_mode);
char		**bindings_list_to_array(t_bindings *head);

#endif