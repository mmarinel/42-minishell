/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:19:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 16:35:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

int	ft_open(char *file_name, unsigned long long flags, int mode,
		t_bool free_file_name)
{
	int	new_fd;
	int	std_fd;

	if (!file_name)
		return (-1);
	std_fd = ft_atoi(file_name + 1);
	if (file_name[0] == '&'
		&& (
			std_fd == STDIN_FILENO
			|| std_fd == STDOUT_FILENO
			|| std_fd == STDERR_FILENO
		)
		&& file_name[2] == '\0')
		new_fd =  (std_fd);
	else
		new_fd = (open(file_name, flags, mode));
	free_stuff:
	{
		printf("file_nae is: %s\n", file_name);
		if (free_file_name && file_name)
			free(file_name);
	}
	return (new_fd);
}

int	ft_unlink(char *file_name, t_bool free_file_name)
{
	int	outcome;

	outcome = unlink(file_name);
	if (free_file_name && file_name)
		free(file_name);
	return (outcome);
}
