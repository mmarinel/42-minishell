/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:52:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 14:53:45 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "../env.h"

char		**bindings_list_to_array(t_bindings *head);
void		add_new_binding(t_bindings **head, t_bindings *new_binding,
				t_bool in_order);
void		binding_remove(t_bindings **head, char *var_name);
t_bool		binding_exist(t_bindings *head, t_bindings *binding);
size_t		bindings_len(t_bindings *head);
void		copy_env(t_bindings **head, char **envp, t_bool in_order);
void		free_env(t_bindings *head);
t_bindings	*get_new_binding(char *var_name, char *var_val, t_bool concat_mode);
t_bindings	*over_write_binding(t_bindings *head, t_bindings *binding);
void		binding_add_front(t_bindings **head, t_bindings *new_binding);
void		binding_add_back(t_bindings **head, t_bindings *new_binding);
void		binding_add_in_order(t_bindings **head, t_bindings *new_binding);

#endif