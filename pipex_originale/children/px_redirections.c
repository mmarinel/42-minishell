/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:39:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 16:52:09 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_children.h"

static void	px_infile_outpipe(char *infile, int out_fd, t_boolean append);
static void	px_inpipe_outfile(int in_fd, char *outfile, t_boolean append);
static void	px_inpipe_outpipe(int in_fd, int out_fd);

void	px_redirections(int mode, t_cmd *current, t_boolean append)
{
	if (mode == PX_FIRST)
		px_infile_outpipe(current->file, current->outpipe[1], append);
	else if (mode == PX_LAST)
		px_inpipe_outfile(current->prev->outpipe[0], current->file, append);
	else
		px_inpipe_outpipe(current->prev->outpipe[0], current->outpipe[1]);
}

static void	px_infile_outpipe(char *infile, int out_fd, t_boolean append)
{
	int	fd;

	if (append)
		fd = open(".here_doc", O_RDONLY);
	else
		fd = open(infile, O_RDONLY);
	if (-1 == fd)
		px_error_handler(0, infile, e_false);
	if (-1 == dup2(fd, STDIN_FILENO))
		px_error_handler(0, NULL, e_false);
	close(fd);
	if (-1 == dup2(out_fd, STDOUT_FILENO))
		px_error_handler(0, NULL, e_false);
}

static void	px_inpipe_outfile(int in_fd, char *outfile, t_boolean append)
{
	int	fd;

	if (append)
		fd = open(outfile, O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (-1 == fd)
		px_error_handler(0, outfile, e_false);
	if (-1 == dup2(fd, STDOUT_FILENO))
		px_error_handler(0, NULL, e_false);
	close(fd);
	if (-1 == dup2(in_fd, STDIN_FILENO))
		px_error_handler(0, NULL, e_false);
}

static void	px_inpipe_outpipe(int in_fd, int out_fd)
{
	if (-1 == dup2(in_fd, STDIN_FILENO))
		px_error_handler(0, NULL, e_false);
	if (-1 == dup2(out_fd, STDOUT_FILENO))
		px_error_handler(0, NULL, e_false);
}
