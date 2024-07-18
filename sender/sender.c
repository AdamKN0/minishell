/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:25:33 by kadam             #+#    #+#             */
/*   Updated: 2024/07/13 20:48:37 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_redirection_cmd(t_parser *pars, t_out **out, t_in **in)
{
	char	*file; 

	file = NULL;
	if (pars->redirection->file != NULL)
		file = pars->redirection->file[0];
	if (pars->redirection->type == REDIRECT_OUT_e)
		add_back_out(out, creat_node_out(file, RD_OUT,
				pars->redirection->ambiguous));
	else if (pars->redirection->type == APPEND_OUT_e)
		add_back_out(out, creat_node_out(file, AP_OUT,
				pars->redirection->ambiguous));
	else if (pars->redirection->type == REDIRECT_IN_e)
		add_back_in(in, creat_node_in(file, RD_IN,
				pars->redirection->ambiguous));
	else if (pars->redirection->type == HEREDOC_e)
		add_back_in(in, creat_node_in(file, H_IN,
				pars->redirection->ambiguous));
}

static char	**copy_command_args(t_parser *pars)
{
	char	**arg;
	int		i;
	int		j;

	arg = (char **)malloc(sizeof(char *) * 
			(cout_2d_array(pars->command->args) + 2));
	if (arg == NULL)
		return (NULL);
	arg[0] = ft_strdup(pars->command->command);
	i = 1;
	j = 0;
	while (pars->command->args && pars->command->args[j])
		arg[i++] = ft_strdup(pars->command->args[j++]);
	arg[i] = NULL;
	return (arg);
}

void	sender(t_cmd **cmd, t_parser *pars, char **arg)
{
	t_in	*in;
	t_out	*out;

	in = NULL;
	out = NULL;
	while (pars)
	{
		if (pars->type == COMMAND_e)
		{
			arg = copy_command_args(pars);
			if (arg == NULL)
				return ;
		}
		else if (pars->type == REDIRECTION_e)
			handle_redirection_cmd(pars, &out, &in);
		if (pars->type == PIPE_e || pars->next == NULL)
		{
			add_cmd_back(cmd, ft_lstnew_cmd(arg, in, out));
			arg = NULL;
			in = NULL;
			out = NULL;
		}
		pars = pars->next;
	}
}
