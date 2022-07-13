/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:52:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 12:15:35 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "../env.h"

char		**bindings_list_to_array(t_bindings *head);
void		binding_add_new(t_bindings **head, t_bindings *new_binding,
				t_bool in_order);
void		binding_remove(t_bindings **head, char *var_name);
t_bool		binding_exist(t_bindings *head, t_bindings *binding);
size_t		bindings_len(t_bindings *head);
void		copy_env(char **envp);
void		free_env(t_bindings *head);
/**
 * @brief this function returns the current value for the environment variable 'name'
 * 
 * @param head the head of the environment list
 * @param name the name to search
 * @return char* (always malloc-ed !) if variable is defined, its value is returned, otherwise an empty string is returned
 */
char		*binding_get_value(t_bindings *head, char *name);
t_bindings	*get_new_binding(char *var_name, char *var_val, t_bool concat_mode);
void		free_binding(t_bindings *binding);
t_bindings	*binding_over_write(t_bindings *head, t_bindings *binding);
void		binding_add_front(t_bindings **head, t_bindings *new_binding);
void		binding_add_back(t_bindings **head, t_bindings *new_binding);
void		binding_add_in_order(t_bindings **head, t_bindings *new_binding);

#endif