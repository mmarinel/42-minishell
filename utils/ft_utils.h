/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/09 18:49:00 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../types.h"

// useful macros
# include <limits.h>
// # include <linux/limits.h>

// read, write, file handling ...
# include <unistd.h>
# include <fcntl.h>

// std libs
# include <stdlib.h>
# include <stdio.h>


// * string utils

size_t			skip_past_last_char(char *str, size_t offset,
					char to_skip, int direction);
size_t			skip_consecutive_chars(char *string, size_t offset,
					char to_skip, int direction);
size_t			ft_strlcpy(char **dst, const char *src, size_t dstsize);
void			ft_str_replace(char **str, char *new_);
size_t			ft_strlen(const char *str);
char			*split_merge(char	**split, char *const sep,
					t_bool free_split);
void			*ft_splitclear(char **split);
char			**ft_split(char const *string, char delimiter);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *buf, char *src, int copy_len);
char			*ft_strjoin(char *pre, char *post,
					t_bool free_pre, t_bool free_post);
char			*ft_itoa(int nbr);
int				ft_atoi(const char *str);
t_bool			ft_is_alpha(char c);
t_bool			ft_isspace(char c);
t_bool			char_is_alpha(char c);
t_bool			char_is_digit(char c);
//char			*ft_multi_substr(char *str, char *delimiters);
char			*ft_substr(char *str, char delimiter);
char			*take_substr(char *str, char *substr);
/**
 * @brief this function takes the next word
 * (i.e.: anything except isspace characters)
 * starting from the current position of char pointer 'str'
 * 
 * @param str 
 * @return char* 
 */
char			*take_next_word(char *str);
/**
 * @brief this function checks wether the number of occurrences
 * of the quote at the beginning of the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool			ft_quote_occurrence_balanced(char *str);
char			take_starting_quote(char *str);
char			*str_strip_spaces(char *str);
char			*string_strip(char *str, char c, t_bool free_input);
int				str_number_occurrences(char *str, char c);
t_bool			str_not_empty(char *str);

// * math utils

unsigned int	ft_pow(unsigned int m, unsigned int e);
void			flip(t_bool *value);

// * memory utils

void			*ft_malloc(size_t size);
void			ft_free(void *ptr);

// * shell utils

void			set_error(t_status *status);
t_bool			ft_pending_pipe(char *command);
t_bool			ft_pending_logical_op(char *command);
t_bool			bash_control_character(char c);
t_bool			ft_is_quote(char c);
t_bool			bash_cmd_separator(char c);
t_bool			redirect_char(char c);
t_bool			asked_for_termination(char	*command);
void			close_pipe(int pipe_[]);

// * misc utils

/**
 * @brief This function maps points outside range [0, right_edge)
 * to points chosen as arguments.
 * 
 * @param point the point to map
 * @param right_edge the right edge of interval [0, right_edge)
 * @param left_spill_val the point where to map inputs that fall behind 0
 * @param right_spill_val the point where to map inputs that
 * fall "above" (>=) right_edge
 * @return int the mapped point
 */
int				range_spill(int point, int right_edge,
					int left_spill_val, int right_spill_val);

#endif