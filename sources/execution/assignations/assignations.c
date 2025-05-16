#include "minislay.h"

static bool find_key_in_local(t_shell **minishell, char *key, char *value)
{
    t_env   *new;

    new = NULL;
    if (*minishell)
    {
        if ((*minishell)->env)
        {
            while ((*minishell)->env->local)
            {
                if ((*minishell)->env->local->key == key)
                {
                    //modify value
                    //return true;
                }
                move_pointer(&(*minishell)->env->local);
            }
            new = create_local_node(key, value);
            if (new)
            {
                (*minishell)->env->local = new;
                return true;
            }
            //error message memalloc failed
            return false;
        }
    }
    return false;
}

//Retrouve la clef et passe a la suivante
static bool	find_key_in_env(t_shell **minishell, char *key, char *value)
{
	if (*minishell)
	{
		if ((*minishell)->expt)
		{
			// Chercher la clef dans l'arbre.
			// Copier l'implementation du main de avlt			
		
			// Si la clef n'est pas dans l'arbre, l'ajouter dans la liste 
			// locale

		}
	}
}

//Trier la liste && implementer uen queue
static void	find_matching_key(t_shell **minishell, char *key, char *value)
{
	if (minishell)
	{
		if (key && value)
		{
			if (!find_key_in_env())
				find_key_in_local();
		}
		printf("Invalid key or value.\n");
	}
	printf("Invalid minishell.\n");
}

//This function makes sure we got a valid key. Valid keys are composed of either
//alpha numerical characters or '_'. They can't start with a digit.
static bool check_key(char *key)
{
    if (key)
    {
        if (isalpha(*key) || *key == '_')           //Remove this magic number
        {
            key++;
            while (*key)
            {
                if (!isalnum(*key) && *key != '_')  //Remove this magic number
            //        return (false);
                    break ;
                key++;
            }
        }
    }
    return (!*key);
}

//Si assignation && commande -> assignation juste pour la commande
//Sinon, assignation permanente dans l'environement || les variables locales.
//
//Les assignations doivent d'abord etre expand. Elles sont ensuite ajoutees ou
//modifiees dans leur liste respective.
//Envoyer une liste d'assignations.
//
//LEFT TO RIGHT PRIORITY
bool	handle_assignations(t_shell **minishell, t_tokn *token)
{
	char	*key;
	char	*value;
	char	*assignation;

	if (token && token->value)
	{
		assignation = strdup(token->value);		//We need to keep the original memory intact
		if (assignation)
		{
			key = assignation;
			strtok_r(assignation, "=", &value); //Remove this magic number
            if (check_key(key))
                find_matching_key();
            free(assignation);
            return (true);
		}
	}
    return (false);
}
