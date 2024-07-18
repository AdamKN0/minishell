CC = cc 
CFLAGS =  -Wall -Wextra -Werror -I/goinfre/aaskal/homebrew/Cellar/readline/8.2.10/include
LIBS = -lreadline -L/goinfre/aaskal/homebrew/Cellar/readline/8.2.10/lib 
RM = rm -f

SRCS =	exec/Signals.c exec/access_in_out.c exec/exec.c exec/fork.c exec/ft_error.c exec/get_full_path.c exec/here_doc.c exec/here_doc_function.c exec/in_out.c\
		exec/builtins/exec_builtins.c exec/builtins/exec_cd.c exec/builtins/exec_echo.c exec/builtins/exec_env.c exec/builtins/exec_exit.c exec/builtins/exec_export.c exec/builtins/exec_pwd.c exec/builtins/exec_unset.c\
		expander/change_node.c expander/expander.c expander/expander_utils1.c \
		lexer/check_error.c lexer/check_error_utils.c lexer/handel1.c lexer/handel2.c lexer/handle_env_herdoc.c lexer/lexer.c lexer/lexer_utils.c\
		parser/count_node.c parser/handle_amb.c parser/is_wildcard.c parser/modifications_args.c parser/parser_token_utils1.c parser/parsing.c parser/process_args_parser.c parser/expand_wildcard.c parser/handle_env_pars.c parser/join_cmd_af_file.c parser/parse_tokens.c parser/parser_token_utils2.c parser/parsing_utils.c\
		sender/sender.c sender/sender_utils1.c sender/sender_utils2.c\
		libft/cout_2d_array.c libft/ft_atoi.c libft/ft_isalpha.c libft/ft_itoa.c libft/ft_putstr_fd.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_strtrim.c libft/get_next_line.c libft/join_2d_array.c libft/free_2d_array.c libft/ft_isalnum.c libft/ft_isdigit.c libft/ft_memcpy.c libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strnstr.c libft/ft_substr.c libft/is_number.c\
		ft_readline.c main.c main_utils.c 

NAME = minishell
OBJS = $(SRCS:.c=.o)

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m 

all: $(NAME) 
$(NAME): $(OBJS) minishell.h
	@$(CC) $(CFLAGS)  $(SRCS) $(LIBS)  -o $(NAME) 
	@echo "$(GREEN)Compilation of $(NAME) successful!$(NC)"

%.o: %.c minishell.h
	@$(CC)    $(CFLAGS) -c $< -o $@
clean:
	@$(RM) $(OBJS)
	@echo "$(RED)Clean of objects successful!$(NC)"

fclean: clean

	@$(RM) $(NAME)
	@echo "$(RED)Clean of $(NAME) successful!$(NC)"

re: fclean all

42: 
	@echo "$(GREEN)Running 42 rule...$(NC)"
	@make; make clean ; clear ; ./minishell
	@echo "$(GREEN)42 rule successful!$(NC)"

.PHONY: all clean fclean re