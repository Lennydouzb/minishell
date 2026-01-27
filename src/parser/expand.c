#include "../../includes/minishell.h"

static char	*extract_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*expand_variables(char *str, char **env, int status)
{
	int		i;
	int		q;
	char	*new;
	char	*tmp;

	i = 0;
	q = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && q == 0)
			q = 1;
		else if (str[i] == '\'' && q == 1)
			q = 0;
		else if (str[i] == '"' && q == 0)
			q = 2;
		else if (str[i] == '"' && q == 2)
			q = 0;
		if (str[i] == '$' && q != 1 && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '_'))
		{
			if (str[i + 1] == '?')
			{
				tmp = ft_itoa(status);
				new = ft_straddback(new, tmp);
				i += 2;
			}
			else
			{
				tmp = extract_var_name(str, &i);
				new = ft_straddback(new, get_env_val(tmp, env));
			}
			// Attention: libère bien tmp et le retour de get_env_val si nécessaire
			free(tmp);
			continue ;
		}
		tmp = ft_substr(str, i++, 1);
		new = ft_straddback(new, tmp);
		free(tmp);
	}
	free(str);
	return (new);
}
