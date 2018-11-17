/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 23:07:05 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 14:03:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_strenv(t_data *data)
{
	char	**strenv;
	t_envp	*start;
	int		i;

	i = -1;
	start = data->envp;
	if (!(strenv = (char **)ft_memalloc(
	sizeof(char *) * (ft_lst_len(data) + 1))))
		ft_err_exit(data);
	while (data->envp)
	{
		if (!(strenv[++i] = ft_strjoin(data->envp->name, "=")))
		{
			ft_free_tab(strenv);
			ft_err_exit(data);
		}
		if (!(strenv[i] = ft_strjoin_free(strenv[i], data->envp->value)))
		{
			ft_free_tab(strenv);
			ft_err_exit(data);
		}
		data->envp = data->envp->next;
	}
	data->envp = start;
	return (strenv);
}

void	ft_exec_binary(char *bin_path, t_data *data)
{
	char	**strenv;
	pid_t	parent;

	strenv = ft_make_strenv(data);
	if ((parent = fork()) != -1 && !parent)
	{
		if ((execve(bin_path, data->input, strenv)) == -1)
			ft_print_error(bin_path, "Denied or is a directory");
		ft_free_tab(strenv);
		free(bin_path);
		ft_free_data(data);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	ft_free_tab(strenv);
	free(bin_path);
}

void	ft_exec_command(t_data *data)
{
	char	*bin_path;

	if (ft_strequ(data->input[0], "exit"))
		ft_exit(data);
	else if (ft_strequ(data->input[0], "cd"))
		ft_change_dir(data);
	else if (ft_strequ(data->input[0], "env"))
		ft_display_env(data);
	else if (ft_strequ(data->input[0], "echo"))
		ft_echo(data);
	else if (ft_strequ(data->input[0], "setenv"))
		ft_setenv(data);
	else if (ft_strequ(data->input[0], "unsetenv"))
		ft_unsetenv(data);
	else if ((bin_path = ft_find_binary(data)))
		ft_exec_binary(bin_path, data);
	else if (data->input[0])
		ft_print_error(data->input[0], "command not found");
}

void	ft_get_command(t_data *data)
{
	char	*line;
	int		ret;

	if ((ret = (get_next_line(0, &line))) == -1)
		ft_err_exit(data);
	if (ret)
	{
		if (!(data->input = ft_strsplit_w(line)))
		{
			free(line);
			ft_err_exit(data);
		}
	}
	else
	{
		ft_putendl("exit");
		ft_free_lst(data->envp);
		exit(EXIT_SUCCESS);
	}
	free(line);
}
