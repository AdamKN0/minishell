/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:54:38 by kadam             #+#    #+#             */
/*   Updated: 2024/07/11 19:27:30 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_lstnew_parser(t_command *command, char *PIPE,
		t_redirection *redirection)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (NULL);
	new->command = command;
	if (command)
		new->type = COMMAND_e;
	if (PIPE)
	{
		new->pipe = ft_strdup(PIPE);
		new->type = PIPE_e;
	}
	else
		new->pipe = NULL;
	new->redirection = redirection;
	if (redirection)
		new->type = REDIRECTION_e;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_parser(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

static void	clear_command(t_command *command)
{
	int	i;

	i = 0;
	if (command)
	{
		free(command->command);
		if (command->args)
		{
			while (command->args[i] != NULL)
				free(command->args[i++]);
			free(command->args);
		}
		free(command);
	}
}

static void	clear_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	if (redirection)
	{
		free(redirection->redirection);
		if (redirection->file)
		{
			while (redirection->file[i] != NULL)
				free(redirection->file[i++]);
			free(redirection->file);
		}
		free(redirection);
	}
}

void	ft_lstclear_parser(t_parser **parser_x)
{
	t_parser	*tmp;

	while (*parser_x)
	{
		tmp = *parser_x;
		*parser_x = (*parser_x)->next;
		if (tmp->command)
			clear_command(tmp->command);
		if (tmp->redirection)
			clear_redirection(tmp->redirection);
		if (tmp->pipe)
			free(tmp->pipe);
		free(tmp);
	}
}
