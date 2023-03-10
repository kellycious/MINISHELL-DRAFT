#include "../LIB/minishell.h"

/*int	nb_env(char **envp)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (envp[i++])
		count++;
	return (count);
}

char **extract_env(char **envp)
{
	int		count;
	int		i;
	char	**copy;

	i = 0;
	count = nb_env(envp);
	copy = malloc(sizeof(char *) * count);
	if (!copy)
		return (0);
	while (envp[i])	
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(copy[i], envp[i], ft_strlen(envp[i]) + 1);
//		printf("%s\n", copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}*/

t_env	*create_env(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

int	insert_env(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*temp;

	new = create_env(name, value);
	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	env_parser(char **envp, t_env **head, int i)
{
	int		j;
	bool	equal;
	char	*name;
	char	*value;

	while (envp[i])
	{
		j = 0;
		equal = false;
		while (envp[i][j])
		{
			if (envp[i][j] == '=' && equal == false)
			{
				equal = true;
				name = ft_substr(envp[i], 0, j);
				if (!name)
					return (free(name), 1);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
				break ;
			}
			j++;
		}
		if (insert_env(head, name, value) == 1)
			return (1);
		free(name);
		free(value);
		i++;
	}
	return (0);
}
/*
void	printstr(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		printf("%s=", temp->name);
		printf("    %s\n", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*env;
	
	env = NULL;
	env_parser(envp, &env, 0);
	printstr(env);
}*/
