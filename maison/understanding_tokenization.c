#include <stdio.h>
#include <string.h>

/*
void    get_parsed(char *string, char *delim, char **save)
{
    if (strtok_r(string, delim, save))
    {
        printf("%s\n", string);
        get_parsed(string, delim, save);
    }
}

int main(int argc, char **argv)
{
    char    *save = NULL;
    char    *delim = NULL;
    char    *string = NULL;

    if (argc == 3)
    {
        delim = argv[2];
        string = argv[1];
        get_parsed(string, delim, &save);
    }
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TOKENIZATION EXAMPLE USING STRTOK_R
//
//I got the following code snippet from man strtok.
//It really helped understanding the function's behaviour && ways to use it for
//our Minislay's tokenization.
//Find below the tested case && understanding
//
//Tested case: 
//  
//  ./a.out "(<< 'wll' uniq | wc -l > outfile.txt) && (caca || echo 'le boss')" "&|()" " "
//
//In this example, we first tokenize around "&|()" priorities. Hence, we get the 
//command blocks that we can then split into smaller space separated chuncks.
//This way, we get the following output:
//
//Original    -->  (<< 'wll' uniq | wc -l > outfile.txt) && (caca || echo 'le boss')
//
//Token 1     -->  << 'wll' uniq
//            -->  <<
//            -->  'wll'
//            -->  uniq
//
//Token 2     -->   wc -l > outfile.txt
//            -->  wc
//            -->  -l
//            -->  >
//            -->  outfile.txt
//
//Token 3     -->
//
//Token 4     -->
//
//Token 5     -->  caca
//            -->  caca
//
//Token 6     -->   echo 'le boss'
//            -->  echo
//            -->  'le
//            -->  boss'
//
//You can see that the leading space for each token is still present in the
//printed string, yet gets removed in the sub_token call. Also, the '' and ""
//detection is not activated, hence the content of 'le boss' is splited into 2
//sub-tokens.
//
//Let's run another test without bonuses:
//
//  ./a.out "< infile.txt cat | wc -l >> line_counter.txt" "&|()" " "
//
//Original    -->  < infile.txt cat | wc -l >> line_counter.txt
//
//Token 1     -->  < infile.txt cat 
//            -->  <
//            -->  infile.txt
//            -->  cat
//
//Token 2     -->   wc -l >> line_counter.txt
//            -->  wc
//            -->  -l
//            -->  >>
//            -->  line_counter.txt
//
//In this case, the 2 execustion blocks get splited straight away. They can now
//be parsed for execution.
//In this case, we would send a **list containing 
//
//  ->  *list -> Token1 ->  1 redirection node followed by 1 command node. 
//  ->  *list -> Token2 ->  1 command node followed by 1 redirection node.
//
//
int main(int argc, char **argv)
{
    char *str1 = NULL, *str2 = NULL, *token = NULL, *subtoken = NULL;
    char *saveptr1 = NULL, *saveptr2 = NULL;

    if (argc == 4)
    {
        printf("Original    -->  %s\n\n", argv[1]);
        str1 = argv[1];
        for (int j = 1; ;j++, str1 = NULL)
        {
            token = strtok_r(str1, argv[2], &saveptr1);
            if (token == NULL)
                break;
            printf("Token %d     -->  %s\n", j, token);
            for (str2 = token; ; str2 = NULL) 
            {
                subtoken = strtok_r(str2, argv[3], &saveptr2);
                if (subtoken == NULL)
                    break;
                printf("            -->  %s\n", subtoken);
            }
            printf("\n");
        }
        exit(EXIT_SUCCESS);
    }
    fprintf(stderr, "Usage: %s string delim subdelim\n",
    argv[0]);
    exit(EXIT_FAILURE);
}
