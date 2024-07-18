/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_af_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:29:24 by kadam             #+#    #+#             */
/*   Updated: 2024/07/12 10:11:50 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	merge_commands(t_parser **prev, t_parser **next, int i, int j)
{
	char	**new_args;
	char	**join_arg;

	new_args = malloc(sizeof(char *)
			* cout_2d_array((*next)->redirection->file));
	if (!new_args)
		return ;
	while ((*next)->redirection->file[i])
		new_args[j++] = ft_strdup((*next)->redirection->file[i++]);
	new_args[j] = NULL;
	join_arg = join_2d_array((*prev)->command->args, new_args, 0, 0);
	if ((*prev)->command->args)
	{
		free_2d_array((*prev)->command->args, 0);
		(*prev)->command->args = NULL;
	}
	if ((*next)->redirection->file)
		free_2d_array((*next)->redirection->file, 1);
	(*prev)->command->args = join_arg;
}

static t_parser	*merge_redire(int i, int j, t_parser *tmp)
{
	char		**new_args;
	char		**join_arg;
	t_command	*new_command;
	t_parser	*new_node;

	new_command = malloc(sizeof(t_command));
	new_command->args = NULL;
	new_command->command = ft_strdup(tmp->redirection->file[1]);
	if (cout_2d_array(tmp->redirection->file) != 2)
	{
		new_args = malloc(sizeof(char *)
				* (cout_2d_array(tmp->redirection->file) - 1));
		if (!new_args)
			return (NULL);
		while (tmp->redirection->file[i])
			new_args[j++] = ft_strdup(tmp->redirection->file[i++]);
		new_args[j] = NULL;
		join_arg = join_2d_array(new_command->args, new_args, 0, 0);
		new_command->args = join_arg;
		new_args = NULL;
	}
	new_node = ft_lstnew_parser(new_command, NULL, NULL);
	new_command = NULL;
	return (new_node);
}

static void	process_nodes(t_parser **parser_x, t_parser **prev, t_parser **tmp,
		t_parser **next)
{
	t_parser	*new_node;

	new_node = merge_redire(2, 0, *tmp);
	if ((*tmp)->redirection->file)
		free_2d_array((*tmp)->redirection->file, 1);
	if (*prev == NULL)
	{
		*parser_x = new_node;
		new_node->next = *tmp;
		(*tmp)->prev = new_node;
		*next = new_node;
	}
	else
	{
		(*prev)->next = new_node;
		new_node->prev = *prev;
		new_node->next = *tmp;
		(*tmp)->prev = new_node;
		*next = new_node;
	}
}

void	join_cmd_af_file(t_parser **parser_x, t_parser *next, t_parser *prev,
		t_parser *tmp)
{
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == COMMAND_e)
		{
			prev = tmp;
			while (next && next->type == REDIRECTION_e)
			{
				if (next->redirection->file
					&& cout_2d_array(next->redirection->file) >= 2)
					merge_commands(&prev, &next, 1, 0);
				next = next->next;
			}
		}
		else if (tmp->type == REDIRECTION_e)
		{
			prev = tmp->prev;
			if (tmp->redirection->file
				&& cout_2d_array(tmp->redirection->file) >= 2)
				process_nodes(parser_x, &prev, &tmp, &next);
		}
		tmp = next;
	}
}
