/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:52:55 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/05 11:36:50 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			**args;
	char			**raw;
	char			*path;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
}					t_cmd;

int					execute_builtin(t_cmd *cmd, char ***local_env,
						t_cmd *first);
void				free_cmds(t_cmd *cmd);

char				*write_prompt(void);
void				wait_and_update_status(pid_t last_pid, int *g_status);
int					is_builtin(char *arg);
void				smartclose(t_cmd *cmd);
char				**copy_env(char **env);

char				*get_env_val(char *var, char **env);

char				*ft_readline_no_tty(void);
char				*get_heredoc_prompt(void);

int					is_valid_exec(char *path);
void				close_standard(t_cmd *cmd);
void				free_and_exit(int exit_code, t_cmd *first, char **env);
pid_t				exec_cmd_loop(t_cmd *cmd, char ***env, int *status);
int					set_env_var(char ***env, char *key, char *value);
int					redirect(char *flag, char *file, char **env, int status);
t_cmd				*parse(char *str, char **env, int status);
void				parsefunc(t_cmd *cmd, char **env, int status);
void				ft_toargs(t_cmd *cmd, char *str, int i);
void				ft_raw_to_args(t_cmd *cmd, char **env, int status);
void				ft_toraw(t_cmd *cmd, char *str);
int					is_quote(char c, int quote);
int					is_var(char *str, int i, int q);
char				*extract_var_name(char *str, int *i);
int					loop_count(t_cmd *cmd, int *i, int *count);
void				link_cmd(t_cmd *cmd, int k, char **env, int status);
void				raw_to_args_loop(t_cmd *cmd, int status, char **env);
t_cmd				*process_parsing(int *exit_status, char *input,
						char **l_env);
void				mask_str(char *str);
void				unmask_str(char *str);

void				free_cmds_loop(t_cmd *cmd, int *i, int *is_first);
void				print_free(char *line, int *fd);

char				*putspace(char *str);
int					countspace(char *str);

int					heredoc_event_hook(void);

char				*remove_quotes(char *str);
char				*expand_variables(char *str, char **env, int status, int q);
void				expand_args(t_cmd *cmd, char **env, int status);

char				*get_env_path_from_env(char **env);
char				*get_env_path(t_cmd *cmd, char **env, char **paths);
char				*get_env_val(char *var, char **env);

char				*get_path(void);
int					change_path(t_cmd *cmd, char ***env);

void				new_prompt(int sig);
void				sig_child(int sig);
void				sig_heredoc(int sig);

int					ft_echo(t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					ft_env(t_cmd *cmd, char **env);
void				ft_exit(t_cmd *cmd, char ***env, t_cmd *first);
int					ft_unset(t_cmd *cmd, char ***env);
int					ft_export(t_cmd *cmd, char ***env);

int					check_syntax_error(char **raw);

void				ft_free_tab(char **tab_);
void				free_cmds(t_cmd *cmd);

#endif
