#include "./LIB/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*command;
	t_token	*head;
	t_env	*env;

	(void)ac;
	(void)av;
	(void)envp;
	head = NULL;
	env = NULL;
	while (1)
	{
		command = readline("minishell$> ");
		add_history(command);
		ft_first_split(command, &head, 0, 0);
		printstr(head);
	}
	ft_free_list(&head);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*command;
// 	t_token	*head;
// 	t_env	*env;

// 	(void)ac;
// 	(void)av;
// 	head = NULL;
// 	env = NULL;
// 	while (1)
// 	{
// 		command = readline("minishell$> ");
// 		add_history(command);
// 		ft_split_test(command, &head, 0, 0);
// 		assign_type(&head);
// 		ft_check_syntax_error(&head);
// 		printstr(head);
// 		env_parser(envp, &env, 0);
// 		// expand_default(&head, &env, 0, DEFAULT);
// 		// expand_single(&head, DEFAULT, -1, NULL);
// 		printstr(head);
// //		if (ft_strncmp(command, "echo", 4) == 0)
// //			ft_echo(av, 1);
// 		if (ft_strncmp(command, "pwd", 3) == 0)
// 			ft_pwd(1);
// 		if (ft_strncmp(command, "env", 3) == 0)
// 			ft_env(env, 1, envp);
// 	}
// 	free(command);
// 	free(head);
// }
