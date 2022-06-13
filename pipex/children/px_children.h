/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_children.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:39:32 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 16:40:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_CHILDREN_H
# define PX_CHILDREN_H

# include <unistd.h>
# include <fcntl.h>
# include "../utils/px_utils.h"
# include "../px_types.h"

# define PX_FIRST 1
# define PX_MIDDLE 2
# define PX_LAST 3

void	px_get_cmds(t_cmd **cmd, int argc, char const *argv[]);
pid_t	px_child(int mode, t_cmd *current,
			char *const envp[], t_boolean append);
void	px_redirections(int mode, t_cmd *current, t_boolean append);
void	px_close_pipes(t_cmd *current);

#endif
