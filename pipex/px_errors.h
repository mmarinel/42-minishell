/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:15:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/13 11:47:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_ERRORS_H
# define PX_ERRORS_H

# include <errno.h>

# define ARGC_ERROR "not enough arguments!"
# define PIPE_ERROR "pipe call failed"
# define CMD_NOT_FOUND "zsh"
# define FILE_NOT_FOUND "zsh"

typedef enum e_error_statuses
{
	ARGC_ERROR_STATUS,
	PIPE_ERROR_STATUS,
	CMD_NOT_FOUND_STATUS,
	FILE_NOT_FOUND_STATUS,
	SYS_ERROR_STATUS,
	DUP_ERROR_STATUS,
	MALLOC_ERROR
}	t_error_statuses;

#endif