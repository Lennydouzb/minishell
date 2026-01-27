/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:52:55 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/28 00:08:06 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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

int					execute_builtin(t_cmd *cmd, char **local_env);

int					redirect(char *flag, char *file, char **env, int status);
t_cmd				*parse(char *str, char **env, int status);
void				parsefunc(t_cmd *cmd, char **env, int status);
void				ft_toargs(t_cmd *cmd, char *str, int i);
void				ft_raw_to_args(t_cmd *cmd, char **env, int status);
void				ft_toraw(t_cmd *cmd, char *str);

char				*remove_quotes(char *str);
char				*expand_variables(char *str, char **env, int status);

char				*get_PATH_from_env(char **env);
char				*get_PATH(t_cmd *cmd, char **env);
char				*get_env_val(char *var, char **env);

char				*get_path(void);
int					change_path(t_cmd *cmd);

void				new_prompt(int sig);
void				sig_child(int sig);
void				sig_heredoc(int sig);

int					ft_echo(t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					ft_env(t_cmd *cmd, char **env);
void				ft_exit(t_cmd *cmd);
int					ft_unset(t_cmd *cmd, char ***env);
int					ft_export(t_cmd *cmd, char ***env);

#endif
