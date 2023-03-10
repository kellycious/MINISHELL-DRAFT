/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwong <fwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:41 by khuynh            #+#    #+#             */
/*   Updated: 2023/02/28 15:27:19 by fwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_token	*create(char *str, int start, int end)
{
	t_token	*yo;
	int		x;

	x = 0;
	yo = ft_calloc(1, sizeof(t_token));
	yo->value = ft_calloc((end + 1), sizeof(char));
	while (x <= end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->value[x] = '\0';
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert(t_token **head, char *str, int start, int end)
{
	t_token	*new;
	t_token	*temp;

	new = create(str, start, end);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	printstr(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("node:%s+ ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

int	ft_store_state(char c, int state)
{
	if (state == DEFAULT)
	{
		if (c == '\'')
			state = SINGLE;
		else if (c == '\"')
			state = DOUBLE;
	}
	else if (state == SINGLE)
	{
		if (c == '\'')
			state = DEFAULT;
	}
	else if (state == DOUBLE)
	{
		if (c == '\"')
			state = DEFAULT;
	}
	return (state);
}

void    ft_split_test(char *cmd, t_token **head)
{
    int state;
    int end;
    int start;
    int i;

    i = 0;
    end = ft_strlen(cmd);
    start = 0;
    state = DEFAULT;
    if (end == 1)
    {
        insert(head, cmd, start, end);
        return ;
    }
    while (cmd[i])
    {
        state = ft_get_state(cmd[i], state);

        if (state == DEFAULT && i < end && (cmd[i] == 32 || is_separator(cmd[i])))
        {
            while (cmd[i] == 32)
                i++;
            start = i;
            if (is_separator(cmd[i]))
            {
                if (state == DEFAULT && (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|'))
                {
                    if ((cmd[i] == '>' && cmd[i + 1] != '>') || (cmd[i] == '<' && cmd[i + 1] != '<') || cmd[i] == '|')
                        insert_sep(head, cmd, start, 1);
                    else if ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' && cmd[i + 1] == '<'))
                        insert_sep(head, cmd, start, 2);
                }
                i = skip_separator(i, cmd[i], cmd[i + 1]);
                start = i;
            }
        }
        else
            i++;
        if (state == DEFAULT && ((cmd[i] == 32 && !is_separator(cmd[i - 1])) || (is_separator(cmd[i]) && !is_separator(cmd[i - 1]))))
        {
            insert(head, cmd, start, i - start - 1);
            start = i + 1;
        }
        // if (state == DEFAULT && (cmd[i] == 32 || cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|'))
        // {
        //  insert(head, cmd, start, i - start - 1);
        //  start = i + 1;
        // }
        // else if (state == DEFAULT && is_separator(cmd[i - 1]) && is_separator(cmd[i]) && cmd[i])
        // {
        //  insert(head, cmd, start, i - start);
        //  start = i + 1;
        // }
        else if (i == end && cmd[i - 1] != '<' && cmd[i - 1] != '>' && cmd[i - 1] != '|')
            insert(head, cmd, start, i - start);
    }
}