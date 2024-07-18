/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:46:14 by kadam             #+#    #+#             */
/*   Updated: 2024/07/16 09:15:27 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*get_next_line(int fd);
int		cout_2d_array(char **array);
void	free_2d_array(char **array, int i);
char	**join_2d_array(char **array1, char **array2, int i, int j);
int		ft_isdigit(int c);
int		is_number(char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);

int		ft_isalpha(int c);
#endif