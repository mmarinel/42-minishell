/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 23:36:32 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/20 10:05:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include "utils/px_utils.h"
# include "children/px_children.h"

# define PIPE_ERROR "pipex: pipe failed: "
# define FORK_ERROR "pipex: fork failed: "
# define DUP_ERROR "pipex: dup failed: "
# define EXECVE_FAIELD "pipex: execve failed: "

void	px_pipex(int pids, t_cmd *current,
			char *const envp[], t_boolean append);

#endif