#include "minislay.h"

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

//
bool	handle_assignations(t_shel *minishell, t_tokn *token)
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
                retrieve_node()
            free(assignation);
            return (true);
		}
	}
    return (false);
}
