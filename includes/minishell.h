/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:52:55 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 19:39:28 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>

# include <termios.h>
# include <term.h>
# include <curses.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char			**args;
	char			**raw;
	char			*path;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
}	t_cmd;
t_cmd	*parsefunc(char *str);
int		redirectin(char *str, int i);
int		redirectout(char *str, int i);
t_cmd	*parse(char *str);
void	ft_toargs(t_cmd *cmd, char *str, int i);
#endif
