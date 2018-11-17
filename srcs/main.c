/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:15:10 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 14:12:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_prompt_pwd(t_data *data)
{
	char	*pwd;
	char	*res;
	int		temp;
	int		i;

	i = -1;
	temp = 0;
	if (!(pwd = getcwd(NULL, 0)))
		ft_err_exit(data);
	if (ft_strequ(pwd, "/"))
		return (pwd);
	while (pwd[++i])
		temp = (pwd[i] == '/') ? i : temp;
	if (!(res = ft_strsub(pwd + 1, temp, i)))
	{
		ft_strdel(&pwd);
		ft_err_exit(data);
	}
	ft_strdel(&pwd);
	return (res);
}

void	ft_shell_loop(t_data *data)
{
	char	*pwd;

	while (1)
	{
		ft_putstr("$> "C_CYAN);
		pwd = ft_get_prompt_pwd(data);
		ft_putstr(pwd);
		ft_strdel(&pwd);
		ft_putstr(C_NONE" ");
		ft_get_command(data);
		ft_change_dlr(data);
		ft_change_tld(data);
		ft_exec_command(data);
		ft_free_tab(data->input);
	}
}

int		main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_init_data(envp, &data);
	ft_shell_loop(&data);
	return (0);
}
