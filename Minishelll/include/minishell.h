/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:05:34 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 13:04:42 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define BLUE "\033[34m"
# define RESET "\033[0m"
# define FAILURE -1
# define HASH_TABLE_SIZE 7

typedef enum e_signals
{
	S_HEREDOC = 1,
	S_CTRL_C = 2
}						t_signals;

extern int				g_signals;

typedef struct s_dyn_arr
{
	void				*data;
	size_t				elem_size;
	size_t				curr_size;
	size_t				max_size;
	size_t				front;
}						t_dyn_arr;

typedef t_dyn_arr		t_token_list;

typedef enum e_cmd_status_type
{
	BUILTIN = 1,
	EXTERNAL
}						t_cmd_status_type;

typedef struct s_cmd_status
{
	int					type;
	union
	{
		int				status;
		int				pid;
	} u_value;
}						t_cmd_status;

typedef enum e_pipe_flags
{
	NONE,
	LEFT = 1
}						t_pipe_flags;

// use power of 2 for flags
typedef enum e_redir_flags
{
	// NONE = 0,
	IN = 1,
	OUT = 2,
	IN_REDIR = 4,
	OUT_REDIR = 8
}						t_redir_flags;

// use power of 2 for flags
typedef enum e_flags
{
	QUOTE = 1,
	D_QUOTE = 2,
	HAS_VAR = 4,
	WILDCARD = 8
}						t_flags;

typedef enum e_terminal
{
	UNKNOWN = 0,
	IDENTIFIER,
	L_REDIR,
	R_REDIR,
	APPEND,
	HEREDOC,
	PIPE,
	OR,
	AND,
	L_PAREN,
	R_PAREN,
	EXPORT,
	EXIT,
	ENV,
	ECHO,
	PWD,
	CD,
	UNSET
}						t_terminal;

typedef enum e_node_type
{
	// AND,
	// OR,
	// PIPE,
	// L_REDIR,
	// R_REDIR,
	// APPEND,
	// HEREDOC,
	CMD = 30,
	ARG
}						t_node_type;

typedef enum e_lex_errs
{
	UNKNOWN_SYMBOL = 1,
	QUOTE_ERR,
	DYN_ARR_ERR,
	NO_TOKENS
}						t_lex_errs;

/*
* this is not an error, just a signal to stop the list traversal
*/
typedef enum e_parse_errs
{
	PARSE_ERR = 5,
	NODE_ERR,
	TRAVERSE_ERR,
	LIST_STOP
}						t_parse_errs;

typedef enum e_exec_errs
{
	EXEC_ERR = 9,
	MALLOC_ERR,
	STATUS_DYN_ARR_ERR,
	FORK_ERR,
	AMBIGUOUS_REDIRECT
}						t_exec_errs;

typedef struct s_token
{
	int					type;
	const char			*attr;
	size_t				attr_len;
	int					flags;
}						t_token;

typedef struct s_table_pair
{
	const char			*key;
	int					value;
}						t_table_pair;

//typedef t_list			*t_hash_table[HASH_TABLE_SIZE];

typedef struct s_tree_node
{
	struct s_tree_node	**children;
	int					type;
	size_t				nr_children;
	void				*data;
}						t_tree_node;

typedef struct s_lexer
{
	t_token_list		*list;
	//t_hash_table		*keyword_table;
	char				*input;
	char				*err_occurence;
	int					err;
}						t_lexer;

typedef struct s_parser
{
	t_tree_node			*tree;
	t_token_list		*tokens;
	size_t				current;
	size_t				err_occurence;
	int					err;
}						t_parser;

typedef struct s_context
{
	t_dyn_arr			*args;
	t_dyn_arr			*pids;
	char				**argv;
	t_dyn_arr			*envp;
	int					last_exit_status;
	int					std_fds[2];
	int					pipe_fds[2];
	int					tmp_fd;
	int					redir_flag;
	int					pipe_flag;
	int					cmd_flag;
	t_token_list		*tokens;
	t_tree_node			*ast;
	char				*input;
}						t_context;

void					print_ast(t_tree_node *node, size_t depth);

t_dyn_arr				*new_dyn_arr(size_t start_size, size_t elem_size);
size_t					get_real_index(t_dyn_arr *arr, size_t i);
int						enlarge_array(t_dyn_arr *arr, int mult);
void					*get_val(t_dyn_arr *arr, size_t i);
int						replace(t_dyn_arr *arr, void *elem, size_t index,
							void (*destroy_elem)(void *));
int						push_back(t_dyn_arr *arr, void *elem);
void					*pop_front(t_dyn_arr *arr);
void					clear_dyn_arr(t_dyn_arr *arr,
							void (*destroy_elem)(void *));
void					destroy_dyn_arr(t_dyn_arr *arr,
							void (*destroy_elem)(void *));
void					*get_val_by_key(t_dyn_arr *arr, char *str);
int						get_index(t_dyn_arr *arr, char *str);
void					insert(t_dyn_arr *arr, size_t i, void *elem);

/*
t_hash_table			*new_keyword_table(void);
int						search_table(t_hash_table *table, const char *key);
void					free_keyword_table(t_hash_table *table);
*/

int						peek(char *str, char p);
int						match(char **str, char m);
void					print_lexer_err(t_lexer *lexer);
void					set_lexer_err(t_lexer *lexer, int err);

int						is_whitespace(char c);
int						is_identifier_char(char c, int flags);
int						is_reserved_symbol(char c);

void					init_token(t_token *token, int type, const char *attr,
							size_t attr_len);
int						add_word_token(const char *start, const char *curr,
							int flags, t_lexer *lexer);
int						add_symbol_token(int type, const char *start,
							const char *curr, t_lexer *lexer);

int						match_keywords(char **start, t_lexer *lexer);
int						match_symbols(char **start, t_lexer *lexer);

t_token_list			*scan_input(char *str);

void					print_parser_err(t_parser *parser);
void					set_parse_err(t_parser *parser, int err);
t_token					*peek_token(t_parser *parser, int type);
t_token					*match_token(t_parser *parser, int type);

t_tree_node				*create_id_node(t_parser *parser, int type);
t_tree_node				*create_redirect_node(t_parser *parser, int op);
t_tree_node				*create_op_node(t_tree_node *first, t_tree_node *second,
							int op);

t_tree_node				*link_basic_cmd_nodes(t_tree_node *root,
							t_tree_node *new);

t_tree_node				*list(t_parser *parser);
t_tree_node				*pipeline(t_parser *parser);
t_tree_node				*command(t_parser *parser);
t_tree_node				*basic_cmd(t_parser *parser);
t_tree_node				*redirect(t_parser *parser);

void					destroy_ast(t_tree_node *node,
							void (*destroy_data)(void *));
t_tree_node				*generate_ast(t_token_list *tokens);

int						traverse_pipe(t_tree_node *node,
							int (*exec)(void *, void *), void *context);
int						traverse_logical_op(t_tree_node *node,
							int (*exec)(void *, void *), void *context);
int						traverse_tree(t_tree_node *node, int (*exec)(void *,
								void *), void *context);

int						exec_args(void *data, t_context *ctx);
void					set_fds(t_context *ctx);
int						exec_cmd(void *data, t_context *ctx);
int						exec_list(void *data, t_context *ctx);
int						exec_pipe(void *data, t_context *ctx);
void					print_eof_warning(const char *delim, const size_t len);
int						redirect_file(char *file, int flags, t_tree_node *node,
							t_context *ctx);
char					*get_heredoc_identifier(void);
int						exec_redir(void *data, t_context *ctx);

int						exec_node(void *data, void *context);
int						execute(t_tree_node *ast, t_context *context);

void					reset_context(t_context *context);
int						handle_cmd_status(t_context *context);
int						is_builtin(char *cmd);
int						builtin(void *data, t_context *context);
int						exec_cd(void *arg);
int						exec_pwd(void);
int						exec_echo(void *arg);
int						exec_export(t_context *context, void *arg);
int						exec_unset(t_dyn_arr *envp, void *arg);
int						exec_env(char **envp, char *arg);
int						get_status(char **arg);
int						exec_cat(char *path);
int						is_valid_identifier(char *key);
void					handle_sigint(int signum);
void					handle_sigquit(int signum);
void					setup_signals(void);
void					handle_ctrl_d(char *line, t_context *context);
int						external_command(void *data, t_context *context);
int						add_path(char **cmd, char *envp[]);
void					ignore_signals_in_parent(void);
void					reset_signals_in_child(void);
int						handle_child_process(char **data, t_context *ctx);
int						find_env_var(t_dyn_arr *envp, char *arg);
int						insert_new_env(char *value, t_dyn_arr *envp);
int						set_env_value(char *key, char *new_value,
							t_dyn_arr *envp);
int						ft_setenv(char *arg, t_context *ctx);
int						valid_arg(char *arg);
void					set_context(t_context *context, char **envp);
void					destroy_context(t_context *context);
void					free_envp(char **envp);
void					*create_duplicate_envp(char **envp);
int						wildcard_match(const char *pattern, const char *str);
char					*expand_token(t_token *token, t_context *context);
char					*get_wildcard_path(char *cmd, char **wildcard);
char					*get_var_val(const char **var, char **envp,
							t_context *context);
char					*expand_wildcard(char *cmd);
char					*expand_token_loop(t_token *token, t_context *context);
char					*append_var_to_result(char *res, char *var);
char					*append_to_result(char *res, t_token *token,
							const char *curr, char *var);
char					*finalize_expansion(char *res, const char *curr,
							t_token *token);
char					*append_result(char *result, char *full_entry);
char					*join_paths(char *path, char *entry_name);
char					*process_directory_entries(DIR *dir, char *path,
							char *wildcard);
char					*get_var_val_inside(char *envp, const char **var);
int						has_multiple_assigns(char *envp);
void					print_echo(char **arg, int newline, int i);
int						set_shell_var(t_context *ctx);
int						increment_shlvl(t_context *ctx);
char					*get_prompt(char *str);
void					consume_var_chars(const char **var, size_t	i);
int						is_var_char(char c, size_t i);

#endif // MINISHELL_H
