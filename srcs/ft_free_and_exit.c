/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:08:18 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:52:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
	tab = 0;
}

void	ft_free_lst(t_envp *envp)
{
	t_envp	*temp;

	while (envp)
	{
		ft_strdel(&envp->name);
		ft_strdel(&envp->value);
		temp = envp->next;
		free(envp);
		envp = temp;
	}
}

void	ft_free_data(t_data *data)
{
	if (data && data->input)
		ft_free_tab(data->input);
	ft_free_lst(data->envp);
}
