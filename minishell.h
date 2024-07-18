/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:14:11 by kadam             #+#    #+#             */
/*   Updated: 2024/07/18 16:37:20 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# define UNIQCHAR 1

int						g_status;

// ----------------------------STRUCTURES_ENUMS LEXER------------------
typedef enum s_type
{
	WORD,
	SPACE_X,
	DOLLAR_ENV,
	EXIT_STATUS,
	PIPE,
	REDIRECT_OUT,
	R_OUT_AMB,
	REDIRECT_IN,
	R_IN_AMB,
	APPEND_OUT,
	A_OUT_AMB,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	COMMAND,
	ARGUMENT,
	FILENAME,
}						t_type;

typedef enum s_quote
{
	SINGLE,
	DOUBLE,
	NO_QUOTE,
}						t_quote;

typedef enum s_inside
{
	INSIDE_SINGLE,
	INSIDE_DOUBLE,
	NO_INSIDE,
}						t_inside;

typedef struct s_nor1
{
	int					*i;
	int					x;
	int					y;
}						t_nor1;

typedef struct s_lexer
{
	char				*content;
	t_type				type;
	t_quote				quote;
	t_inside			inside;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

// ----------------------------STRUCTURES EXPANDER--------------------
typedef struct s_env
{
	char				*before_equal;
	char				*after_equal;
	struct s_env		*next;
	struct s_env		*prev;
	int					export;
}						t_env;

// ----------------------------STRUCTURES_ENUMS PARSER1------------------
typedef enum s_space
{
	Y_SPACE,
	NO_SPACE,
}						t_space;

typedef enum s_status
{
	keep_it,
	remove_it,
	join_it,
	delete_it,
	break_it,
}						t_status;

typedef enum s_wildcard
{
	NO_WILDCARD,
	WILDCARD,
}						t_wildcard;

typedef struct s_pars
{
	char				*content;
	t_type				type;
	t_space				space;
	t_status			status;
	t_wildcard			wildcard;
	struct s_pars		*next;
	struct s_pars		*prev;
}						t_pars;

// ----------------------------STRUCTURES_ENUMS PARSER2------------------
typedef enum s_type_parser
{
	COMMAND_e,
	PIPE_e,
	REDIRECTION_e,
}						t_type_parser;

typedef enum s_type_redirection
{
	REDIRECT_OUT_e,
	REDIRECT_IN_e,
	APPEND_OUT_e,
	HEREDOC_e,
}						t_type_redirection;

typedef struct s_command
{
	char				*command;
	char				**args;
}						t_command;

typedef enum s_amibguous
{
	NO_AMBIGUOUS,
	AMBIGUOUS,
}						t_amibguous;

typedef struct s_redirection
{
	char				*redirection;
	char				**file;
	t_type_redirection	type;
	t_amibguous			ambiguous;

}						t_redirection;

typedef struct s_parser
{
	t_command			*command;
	t_redirection		*redirection;
	char				*pipe;
	t_type_parser		type;
	struct s_parser		*next;
	struct s_parser		*prev;
}						t_parser;

// ----------------------------STRUCTURES_ENUMS SENDER------------------
typedef enum s_in_type
{
	RD_IN,
	H_IN,
}						t_in_type;
typedef enum s_out_type
{
	RD_OUT,
	AP_OUT,
}						t_out_type;
typedef struct s_in
{
	char				*input;
	t_amibguous			ambiguous;
	t_in_type			type;
	struct s_in			*next;
	struct s_in			*prev;
}						t_in;
typedef struct s_out
{
	char				*output;
	t_amibguous			ambiguous;
	t_out_type			type;
	struct s_out		*next;
	struct s_out		*prev;
}						t_out;
typedef struct s_cmd
{
	char				**cmd;
	t_in				*in;
	t_out				*out;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	int					fd;
}						t_cmd;

//---------------  executors  -----------------//

typedef struct s_env_v
{
	int					i;
	char				*key;
	char				*value;
	int					check;
	int					j;
	t_env				*tmp;
}						t_env_v;

typedef struct s_args
{
	int					count;
	int					n_pipe[2];
	int					o_pipe[2];
	int					fd;
	pid_t				pid[ARG_MAX];
	int					f;
}						t_args;

typedef struct s_exec
{
	t_cmd				*cmd;
	int					i;
	t_args				args;
	t_in				*in;
	t_out				*out;
}						t_exec;
// ----------------------------STRUCTURE_MAIN-------------------------------
typedef struct norm2
{
	char				*line;
	t_lexer				*lexer_x;
	t_env				*expander_x;
	t_pars				*parser_x;
	t_parser			*parser;
	t_cmd				*cmd;
	char				*message;
	int					i;
	int					x;
	t_cmd				*tmp;
	t_in				*in;
	t_exec				exec_x;
}						t_norm2;

// ----------------------------MAIN----------------------------
int						ft_readline(char **line, int x, int y);
void					initiliaze_struct(t_norm2 *norm2);
void					clear_all(t_norm2 *norm2, int x, int y);
int						syntax_error_herdoc(t_norm2 *norm2);
int						process_and_free_norm2(t_norm2 *norm2);
void					lexer_norm2_x(t_norm2 *norm2);

// ----------------------------LEXER----------------------------------
t_lexer					*ft_lstnew_lex(char *content, t_type type,
							t_quote quote, t_inside inside);
void					ft_lstadd_back_lex(t_lexer **head, t_lexer *new);
void					ft_lstclear_lex(t_lexer **head);
int						ft_is_space(char c);
int						ft_is_not_special(char c);
void					handel_w_p(char *line, int *i, t_quote *quote,
							t_lexer **lexer);
void					handle_s_d_quote(char *line, int *i, t_quote *quote,
							t_lexer **lexer);
void					handle_redirection(char *line, int *i, t_quote *quote,
							t_lexer **lexer);
void					handle_dollar(char *line, t_quote *quote,
							t_lexer **lexer, t_nor1 x);
int						handle_env_herdoc(t_lexer **lexer);
int						lexer(char *line, t_lexer **lexer, int x, int i);

// ----------------------------CHECK_ERROR----------------------------
int						check_pipe(t_lexer *ptr, t_lexer *prev, t_lexer *next);
int						check_redirection(t_lexer *ptr, t_lexer *next, int *z);
void					validate_heredoc(t_lexer *ptr, int *x, int *y);
int						check_and_validate_redirection(t_lexer **ptr,
							t_nor1 nor, char **message);
int						check_and_validate_pipe(t_lexer **ptr, t_nor1 nor,
							char **message);
int						check_is_error(char **message, int *i, t_lexer *ptr,
							int zz);

// ----------------------------EXPANDER-------------------------------
t_env					*lstnew_env(char *before_equal, char *after_equal,
							int x);
void					lstadd_back_env(t_env **head, t_env *new);
void					ft_lstclear_env(t_env **head);
int						find_and_replace_content(t_lexer *lex_tmp,
							t_env **expander, int found);
void					change_node(t_lexer **lexer, t_env **expander);
void					expander(t_env **expander, char **envp);

// ----------------------------PARSER1---------------------------------
t_pars					*ft_lstnew_pars(char *content, t_type type,
							t_space space, int i);
void					ft_lstadd_back_pars(t_pars **head, t_pars *new);
void					ft_lstclear_pars(t_pars **head);
void					parse_tokens(t_pars **x_parser, t_lexer *ptr);
void					handle_ambiguous_redirection(t_pars **x_parser);
void					handle_env_pars(t_pars **x_parser, t_pars *next,
							t_pars *prev, t_pars *new_node);
int						skip_it_pars(t_pars *tmp);
void					parse_types(t_pars **x_parser);
void					process_args_parser(t_pars **x_parser, t_pars *next,
							t_pars *tmp);
void					remove_node(t_pars **x_parser, t_pars *prev,
							t_pars *tmp, t_pars *next);
void					join_arg(t_pars *next, t_pars *tmp, char *new_content);
void					check_prev_export(t_pars *prev, t_pars *ptr,
							int export_flag);
char					**list_files_in_directory(int i, int j);
char					**is_wildcard(char *line, char **files, int i, int j);
void					expand_wildcard(t_pars **x_parser, t_pars *tmp,
							char **files, t_pars *next);

// ----------------------------PARSER2--------------------------------
t_parser				*ft_lstnew_parser(t_command *command, char *pipe,
							t_redirection *redirection);
void					ft_lstadd_back_parser(t_parser **lst, t_parser *new);
void					ft_lstclear_parser(t_parser **parser_x);
int						count_node(t_pars *pars, int type);
void					join_cmd_af_file(t_parser **parser_x, t_parser *next,
							t_parser *prev, t_parser *tmp);
void					parsing(t_pars *pars, t_parser **parser_x,
							t_command *command, t_redirection *redirection);

// ----------------------------SENDER--------------------------------
t_cmd					*ft_lstnew_cmd(char **cmd, t_in *in, t_out *out);
void					add_cmd_back(t_cmd **lst, t_cmd *new);
void					ft_lstclear_sender(t_cmd **lst);
t_in					*creat_node_in(char *input, t_in_type type,
							t_amibguous ambiguous);
void					add_back_in(t_in **lst, t_in *new);
t_out					*creat_node_out(char *output, t_out_type type,
							t_amibguous ambiguous);
void					add_back_out(t_out **lst, t_out *new);
void					sender(t_cmd **cmd, t_parser *pars, char **arg);

//---------------  executors  -----------------//
int						handle_here_doc(char *limiter, t_env *env, int x);
int						change_content(t_lexer **lex_tmp, t_env **expander);
void					processtmp(int x, t_env *env, t_lexer *lexer_x);
void					exec(t_cmd **cmd, t_env **env, int x, t_exec *exec);
void					exec_builtins(t_cmd *cmd, t_env **env, t_args *args);
int						is_builting(char *str);
char					*get_full_path(char *cmd, t_env *env);
void					execute_command(char **cmd, t_env **env);
void					handle_in(t_cmd p_cmd, t_args *args);
int						handle_out(t_cmd p_cmd, t_args *args);
void					get_herdoc(t_cmd **p_cmd, t_env *env, int x);
void					handle_pipe_dup(t_cmd *p_cmd, t_args *args);
void					wait_for_child_processes(t_args **args);
int						command_with_fork(t_cmd *cmd, t_env *env, t_args *a,
							int i);
int						check_ambiguous(t_in *in, t_out *out);
char					**env_variables(t_env *env);
//---------------  builtins  -----------------//
void					exec_exit(t_cmd *cmd, int f);
void					exec_cd(t_cmd *cmd, int f, t_env *env);
void					exec_pwd(t_cmd *cmd, int f);
void					exec_echo(t_cmd *cmd);
void					exec_env(t_cmd *cmd, t_env *env, int f);
void					exec_export(t_cmd *cmd, t_env **env);
void					exec_unset(t_cmd *cmd, t_env **env);
void					exec_exit(t_cmd *cmd, int f);

//---------------  helpers  -----------------//
void					update_env(t_env **env, char *key, char *value);
void					add_env(t_env **env, char *key, char *value);
void					print_env(t_env *env);
int						check_isvalid(char *str);
void					close_pipe(t_args *args);
void					*__path(t_env *env);

//---------------  Errors  -----------------//
void					ft_error(char *message, int exit, int f);
void					my_perror(char *cmd, char *arg, int exit, int f);
void					post_error(char *cmd, char *arg, int exit, int f);
void					_error(char *cmd, char *message);
void					ft_nonvalid(char *cmd, char *args, char *message);
int						check_access_in(t_in *in);
int						check_access_out(t_out *out);

//---------------  Signals  -----------------//

void					handle_signals(void);
void					handle_sigint(int sig);
void					handle_eof(int sig);
void					handle_sigquit(int sig);
void					herdoc_sig(int sig);

#endif