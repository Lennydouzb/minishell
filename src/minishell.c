/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/06 19:29:41 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	//char	*input;
	char	*args[] = {"cat", "<", "caca", NULL};
	//int		pid;
	(void)(ac);
	(void)av;

	//while (1)
	//{
	//	input = readline("minishell : ");
	//	parse(input);
	//}
	execve("/bin/cat", args, env);
	return (0);
}
