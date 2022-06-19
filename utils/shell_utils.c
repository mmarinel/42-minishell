/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 12:19:38 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

/**
 * @brief this function returns true iff command is exit or ctrl + D was hit
 * 
 * @param command 
 * @return t_bool 
 */
t_bool	asked_for_termination(char	*command)
{
	if (!command)
		return (e_true);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (e_true);
	return (e_false);
}

void	close_pipe(int pipe_[])
{
	close(pipe_[0]);
	close(pipe_[1]);
}
