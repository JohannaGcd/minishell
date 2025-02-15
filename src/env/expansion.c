#include "../include/minishell.h"

extern char **environ;

// static char *extract_env(char *key, t_envs *envs)
// {

//     if(envs_is_contain(envs, key))
//         return (ft_strdup(envs_get(envs, key)));
//     return(ft_strdup(""));
// }

// int expand_env(t_token *list_tokens, t_envs *envs)
// {
//     char *tmp;
//     while (list_tokens)
//     {   
//         if(list_tokens->type == ENV)
//         {
//             {
//                 tmp = extract_env(list_tokens->str, envs);
//                 if (tmp == NULL)
//                 {
//                     exit(1);
//                 }
//                 free(list_tokens->str);
//                 list_tokens->str = tmp;;
//                 //this is my magic code
//             }
//             list_tokens->type = WORD;
//             printf("%s\n",environ[0]);
//         }
//         list_tokens = list_tokens->next;
//     }
// }