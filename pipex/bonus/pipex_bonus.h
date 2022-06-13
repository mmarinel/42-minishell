/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:33:41 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 16:24:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../children/px_children.h"
# include "../utils/px_utils.h"
# include "../px_errors.h"
# include "../px_types.h"
# include "../get_next_line/px_get_next_line_bonus.h"

void	px_pipex_bonus(int pids, t_cmd *current,
			char *const envp[], t_boolean append);
void	px_lstclear(t_cmd **lst, void (*del)(void *));

#endif