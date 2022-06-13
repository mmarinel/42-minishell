/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_get_next_line_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:14:58 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 14:46:09 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_GET_NEXT_LINE_BONUS_H

# define PX_GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1
# define ERROR -1
# define SUCCESS_DISCARD_BUFFER 1
# define SUCCESS_KEEP_BUFFER 0

char			*get_next_line(int fd);
unsigned int	ft_get_line(char *buf, unsigned int max_len,
					int *nl_found, char **line);
char			*ft_get_line_output(char **str, char **buf, int exit_mode);
void			ft_get_line_initialize_buffer(char **buf,
					ssize_t *bytes_read, int fd);
void			ft_free(char **ptr);
char			*gnl_strjoin(char const *s1, char const *s2, size_t n);
size_t			ft_strlen(const char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);

#endif
