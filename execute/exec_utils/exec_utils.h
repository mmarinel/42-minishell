/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:43:28 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 16:35:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "../executor.h"
# include "../../env/env_module.h"

t_bool	is_path_name(char *cmd);
char	*ft_get_cmd_name(char *cmd);
char	*ft_get_pathname(char *cmd);
t_bool	is_builtin_command(t_tree_node *root);

#endif
