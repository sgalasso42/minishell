/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:19:58 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:32:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_lst_new(char **envp, t_data *data)
{
	int		j;

	j = 0;
	if (!(data->envp = (t_envp *)ft_memalloc(sizeof(t_envp))))
		return (0);
	while (envp[0][j] && envp[0][j] != '=')
		j++;
	if (!envp[0][j] || !(data->envp->name = ft_strsub(envp[0], 0, j)))
		return (0);
	j++;
	if (!(data->envp->value = ft_strsub(envp[0], j, ft_strlen(envp[0]))))
		return (0);
	return (1);
}

int			ft_lst_add(char *envl, t_data *data)
{
	int		j;

	j = 0;
	if (!(data->envp->next = (t_envp *)ft_memalloc(sizeof(t_envp))))
		return (0);
	while (envl[j] && envl[j] != '=')
		j++;
	if (!envl[j] || !(data->envp->next->name = ft_strsub(envl, 0, j)))
		return (0);
	j++;
	if (!(data->envp->next->value = ft_strsub(envl, j, ft_strlen(envl))))
		return (0);
	data->envp = data->envp->next;
	return (1);
}
