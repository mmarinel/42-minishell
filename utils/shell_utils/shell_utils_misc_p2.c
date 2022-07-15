/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:19:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 10:06:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

int	ft_open_file(char *file, unsigned long long flags, int mode)
{
	int	std_fd;

	if (!file)
		return (-1);
	std_fd = ft_atoi(file + 1);
	if (file[0] == '&'
		&& (
			std_fd == STDIN_FILENO
			|| std_fd == STDOUT_FILENO
			|| std_fd == STDERR_FILENO
		)
		&& file[2] == '\0')
		return (std_fd);
	else
	{
		return (open(file, flags, mode));
	}
}
