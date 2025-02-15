#include "minislay.h"

static void sub_type_initialisation(t_tokn **token, int *sub_type)
{
    *sub_type = 0;
    if (is_state_active((*token)->type, DQTE))
        set_state(sub_type, DQTE);
    if (is_state_active((*token)->type, SQTE))
        set_state(sub_type, SQTE);
    if (is_state_active((*token)->type, WORD))
        set_state(sub_type, WORD);
}

static void check_initial_special_content(t_tokn **token, int *index)
{
    *index = 0;
    if ((*token)->value[*index] == '$')
        set_state(&(*token)->type, DOLL);
    else if ((*token)->value[*index] == '*')
        set_state(&(*token)->type, STAR);
    (*index)++;
}

static bool create_sub_token(t_tokn **token, int index, int sub_type, int mask)
{
    t_tokn *new_token;

    new_token = create_node(strdup((*token)->value + index), sub_type | mask);
    if (new_token)
    {
        (*token)->value = realloc((*token)->value, index);
		(*token)->value[index] = '\0';
        (*token)->next = new_token;
        *token = new_token;
    }
    return (new_token != NULL);
}

bool check_word_content(t_tokn **token)
{
    int mask;
    int type;
    int index;
    int start;

    if (*token && (*token)->value)
    {
        sub_type_initialisation(token, &type);
		check_initial_special_content(token, &index);
        while ((*token)->value[index])
        {
            if ((*token)->value[index] == '$')
            {
                mask = DOLL;
                index++;
                if ((*token)->value[index] == '$')
                {
                    index++;
                    if (!create_sub_token(token, start, type, mask))
                        return (false);
                    return (check_word_content(token));
                }
            }
            else if ((*token)->value[index] == '*')
            {
                mask = STAR;
                if (!create_sub_token(token, start, type, mask))
                    return (false);
                return (check_word_content(token));
            }
            else if (isspace((*token)->value[index]))
            {
                if (start != index)
                {
                    mask = WORD;
                    if (!create_sub_token(token, start, type, mask))
                        return (false);
                }
                start = index + 1;
            }
            index++;
        }
        if (start != index)
        {
            mask = WORD;
            if (!create_sub_token(token, start, type, mask))
                return (false);
        }
    }
    return true;
}


/*
#include "minislay.h"

static void sub_type_initialisation(t_tokn **token, int *sub_type)
{
    *sub_type = 0;
    if (is_state_active((*token)->type, DQTE))
        set_state(sub_type, DQTE);
    if (is_state_active((*token)->type, SQTE))
        set_state(sub_type, SQTE);
    if (is_state_active((*token)->type, WORD))
        set_state(sub_type, WORD);
}

static void check_initial_special_content(t_tokn **token, int *index)
{
    *index = 0;
    if ((*token)->value[*index] == '$')
        set_state(&(*token)->type, DOLL);
    else if ((*token)->value[*index] == '*')
        set_state(&(*token)->type, STAR);
    (*index)++;
}

static bool create_sub_token(t_tokn **token, int index, int sub_type, int mask)
{
    t_tokn *new_token;

    new_token = create_node(strdup((*token)->value + index), sub_type | mask);
    if (new_token)
    {
        (*token)->value[index] = '\0';
        (*token)->next = new_token;
        *token = new_token;
    }
    return (new_token != NULL);
}

bool check_word_content(t_tokn **token)
{
    int mask;
    int type;
    int index;

    if (*token && (*token)->value)
    {
        sub_type_initialisation(token, &type);
        check_initial_special_content(token, &index);
        while ((*token)->value[index])
        {
            if ((*token)->value[index] == '$')
            {
                mask = DOLL;
            }
            else if ((*token)->value[index] == '*')
            {
                mask = STAR;
            }
            else if (isspace((*token)->value[index]))
            {
                mask = WORD;
            }
            else
            {
                index++;
                continue;
            }
            if (!create_sub_token(token, index, type, mask))
                return (false);
            return (check_word_content(token));
        }
    }
    return true;
}*/
