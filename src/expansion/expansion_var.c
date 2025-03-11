/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:40:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 11:03:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Comportement identique a  get_key_in_str mais pour la len du malloc
 */
int	len_key_in_str(char *str)
{
	int	i;
	int	len_key;

	i = 0;
	len_key = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
	{
		len_key++;
		i++;
	}
	while (str[i]
		&& (ft_isalnum(str[i])
			|| str[i] == '_'))
	{
		len_key++;
		i++;
	}
	return (len_key);
}

/**
 * Recupere uniquement la cle de la variable d'environnement
 * dans la chaine principale
 * Ex : "$key lalala -> key"
 * 
 * @param str Adresse du debut de la cle $ ou premier caractere
 * @return la cle
 */
char	*get_key_in_str(char *str)
{
	int		i;
	int		i_key;
	char	*key;

	i = 0;
	i_key = 0;
	key = malloc(len_key_in_str(str) + 1 * sizeof(char));
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
	{
		key[i_key] = str[i];
		key[++i_key] = '\0';
		return (key);
	}
	while (str[i]
		&& (ft_isalnum(str[i])
			|| str[i] == '_'))
	{
		key[i_key] = str[i];
		i_key++;
		i++;
	}
	key[i_key] = '\0';
	return (key);
}

char	*get_value_from_key(char *key, t_list **lst_env)
{
	char	*value;

	if (strcmp(key, "?") == 0)
		value = get_exit_status_str();
	else
		value = find_value_in_env(key, lst_env);
	return (value);
}

/**
 * Effectue l'expansion d'une variable d'envrionnement
 * 
 * @param str Adresse de la premiere lettre de la cle (apres le $) 
 * provenant de la chaine initiale
 * @param out Chaine de sortie, c'est ici qu'on fait la copie
 * @param i_out Indice qui indique la position du caractere dans output
 * @param lst_env Liste des variables d'environnement
 * @return La longeur de la cle de la variable
 * d'environnement (dans le but de la sauter dans la fonction parente)
 */
int	expansion_var(char *str, char *out, int *i_out, t_list **lst_env)
{
	char	*value;
	char	*key;
	int		len_key;
	int		i;

	i = 0;
	key = get_key_in_str(str);
	len_key = ft_strlen(key);
	if (len_key == 0)
		return (free(key), len_key);
	value = get_value_from_key(key, lst_env);
	if (value == NULL)
		return (free(key), len_key);
	while (value[i])
	{
		out[*i_out] = value[i];
		i++;
		*i_out += 1;
	}
	return (free(value), free(key), len_key);
}

/**
 * Check si on a rencontre une expansion a realiser
 * 
 * @param str chaine de depart
 * @param i indice du caractere actuelle dans la chaine
 * @return OUI ou NON s'il s'agit d'une expansion
 */
t_bool	is_start_of_expansion(char *str, int i)
{
	if (str[i] == '$'
		&& str[i + 1]
		&& (ft_isalpha(str[i + 1])
			|| str[i + 1] == '_'
			|| str[i + 1] == '?'))
		return (TRUE);
	return (FALSE);
}
