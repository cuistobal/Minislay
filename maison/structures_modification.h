
typedef struct  parsing
{
    char    *input;
    char    *quote_hash;
}   t_pars;

typedef struct  argtree
{
    struct  tokens  *command;
    struct  argtree *left;
    struct  argtree *right;
}   t_tree;

&   &&   (   )   ;   ;;   <newline>   |   ||

# define S_PIPE '|'
# define D_PIPE "||"
# define S_AMPR '&'
# define D_AMPR "&&"
# define S_QUOT '''
# define D_QUOT '"'
# define O_PART '('
# define C_PART ')'

# define I_REDI '<'
# define O_REDI '>'
# define I_HDOC "<<"
# define O_HDOC ">>"

typedef enum    syntax
{

}
