/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:52:55 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/15 16:03:17 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
void				parsefunc(t_cmd *cmd, char **env);
int					redirectin(char *str);
int					redirectout(char *str);
t_cmd				*parse(char *str, char **env);
void				ft_toargs(t_cmd *cmd, char *str, int i);
void				ft_raw_to_args(t_cmd *cmd, char **env);
void				ft_toraw(t_cmd *cmd, char *str);

char				*remove_quotes(char *str);
char				*expand_variables(char *str, char **env);

char				*get_PATH_from_env(char **env);
char				*get_PATH(t_cmd *cmd, char **env);
char				*get_env_val(char *var, char **env);

char				*get_path(void);
void				change_path(t_cmd *cmd);

void				new_prompt(int sig);

void				ft_echo(t_cmd *cmd);
void				ft_pwd(t_cmd *cmd);
void				ft_env(t_cmd *cmd, char **env);
void				ft_exit(t_cmd *cmd);
void				ft_unset(t_cmd *cmd, char ***env);
void				ft_export(t_cmd *cmd, char ***env);

#endif
