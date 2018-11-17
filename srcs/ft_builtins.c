/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:45:14 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:07:33 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(t_data *data)
{
	ft_putendl("exit");
	ft_free_data(data);
	exit(EXIT_SUCCESS);
}

void		ft_setenv(t_data *data)
{
	t_envp	*start;
	t_envp	*envl;

	start = data->envp;
	if (!data->input[1] || !data->input[2])
		return ;
	if ((envl = ft_env_var_exist(data->input[1], data)))
	{
		free(envl->value);
		if (!(envl->value = ft_strdup(data->input[2])))
			ft_err_exit(data);
	}
	else
	{
		while (data->envp->next)
			data->envp = data->envp->next;
		if (!(data->envp->next = (t_envp *)ft_memalloc(sizeof(t_envp))))
			ft_err_exit(data);
		if (!(data->envp->next->name = ft_strdup(data->input[1])))
			ft_err_exit(data);
		if (!(data->envp->next->value = ft_strdup(data->input[2])))
			ft_err_exit(data);
		data->envp->next->next = 0;
		data->envp = start;
	}
}

void		ft_unsetenv(t_data *data)
{
	t_envp	*start;
	t_envp	*prev;

	if (!data->input[1])
		return ;
	prev = 0;
	start = data->envp;
	while (data->envp && !ft_strequ(data->envp->name, data->input[1]))
	{
		prev = data->envp;
		data->envp = data->envp->next;
	}
	if (data->envp)
	{
		if (prev)
			prev->next = data->envp->next;
		else
			start = data->envp->next;
		free(data->envp->name);
		free(data->envp->value);
		free(data->envp);
	}
	data->envp = start;
}

void		ft_display_env(t_data *data)
{
	t_envp	*start;

	start = data->envp;
	while (data->envp)
	{
		ft_putstr(data->envp->name);
		ft_putchar('=');
		ft_putendl(data->envp->value);
		data->envp = data->envp->next;
	}
	data->envp = start;
}

void		ft_echo(t_data *data)
{
	int		i;

	i = 1;
	while (data->input[i])
	{
		ft_putstr(data->input[i]);
		if (data->input[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
