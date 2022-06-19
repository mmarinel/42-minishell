/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 18:21:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../includes.h"

// * string utils

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *buf, char *src, int copy_len);
char	*ft_strjoin(char *pre, char *post, t_bool free_pre, t_bool free_post);
char	*ft_itoa(int nbr);
int		ft_atoi(const char *str);
t_bool	ft_is_alpha(char c);
t_bool	ft_isspace(char c);
t_bool	char_is_alpha(char c);
t_bool	char_is_digit(char c);
char	*take_substr(char *str, char *substr);
/**
 * @brief this function takes the next word
 * (i.e.: anything except isspace characters)
 * starting from the current position of char pointer 'str'
 * 
 * @param str 
 * @return char* 
 */
char	*take_next_word(char *str);
/**
 * @brief this function checks wether the number of occurrences
 * of the quote at the beginning of the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_quote_occurrence_balanced(char *str);
char	take_starting_quote(char *str);
char	*string_strip(char *str, char c, t_bool free_input);
int		str_number_occurrences(char *str, char c);
t_bool	str_not_empty(char *str);

// * math utils

unsigned int	ft_pow(unsigned int m, unsigned int e);

// * memory utils

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

// * shell utils

t_bool	bash_control_character(char c);
t_bool	asked_for_termination(char	*command);
void	close_pipe(int pipe_[]);

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
int		range_spill(int point, int right_edge,
			int left_spill_val, int right_spill_val);

#endif