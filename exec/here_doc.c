/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:10:57 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/18 16:30:05 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_line(char *line, int x, t_env *env, int fd)
{
	t_lexer	*lexer_x;
	t_lexer	*tmp;

	if (ft_strlen(line) != 0 && line[0] != '\n')
	{
		lexer_x = NULL;
		lexer(line, &lexer_x, 1, 0);
		processtmp(x, env, lexer_x);
		tmp = lexer_x;
		while (tmp != NULL)
		{
			if ((tmp->next == NULL && tmp->type == SPACE_X))
				break ;
			write(fd, tmp->content, ft_strlen(tmp->content));
			tmp = tmp->next;
		}
		ft_lstclear_lex(&lexer_x);
	}
}

static int	write_to_file(char *limiter_newline, int fd, t_env *env, int x)
{
	char	*line;

	while (1)
	{
		write(1, "--> ", 4);
		line = get_next_line(0);
		if (!line)
		{
			free(limiter_newline);
			break ;
		}
		if (ft_strncmp(line, limiter_newline, ft_strlen(limiter_newline)) == 0)
		{
			free(line);
			free(limiter_newline);
			break ;
		}
		process_line(line, x, env, fd);
		write(fd, "\n", 1);
		free(line);
	}
	return (fd);
}

static int	write_to_heredoc_file(int fd, char *limiter, t_env *env, int x)
{
	char	*limiter_newline;

	signal(SIGINT, herdoc_sig);
	if (limiter[0] == '\0')
	{
		limiter_newline = ft_strjoin(NULL, "\n");
		x = 1;
	}
	else
		limiter_newline = ft_strjoin(limiter, "\n");
	if (!limiter_newline)
		ft_error("ft_strjoin", 1, 0);
	fd = write_to_file(limiter_newline, fd, env, x);
	close(fd);
	open("/tmp/heredoc", O_RDONLY);
	exit(0);
}

int	handle_here_doc(char *limiter, t_env *env, int x)
{
	int		fd;
	pid_t	pid;

	fd = -1;
	pid = fork();
	fd = open("/tmp/heredocx", O_RDWR | O_CREAT | O_TRUNC, 0774);
	if (fd == -1)
		ft_error("open", 1, 0);
	if (pid == 0)
		write_to_heredoc_file(fd, limiter, env, x);
	else
		waitpid(pid, &g_status, 0);
	return (fd);
}
