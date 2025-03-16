/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sveta <sveta@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/15 14:49:10 by sveta         #+#    #+#                 */
/*   Updated: 2025/03/16 11:29:56 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"
#include "../include/executer.h"
#include "../include/test.h"

int main()
{
    printf ("test_lexer_one_command ------- ");
    if(test_lexer_one_command())
        printf("\033[0;32mOK\033[0m\n");
    else
        printf("\033[0;31mKO\033[0m\n");
    printf ("test_lexer_one_command_and_param ------- ");
        if(test_lexer_one_command_and_param())
            printf("\033[0;32mOK\033[0m\n");
        else
            printf("\033[0;31mKO\033[0m\n");
    printf ("test_lexer_single_quotes ------- ");
    if(test_lexer_single_quotes())
        printf("\033[0;32mOK\033[0m\n");
    else
        printf("\033[0;31mKO\033[0m\n");
    printf ("test_lexer_double_quotes ------- ");
        if(test_lexer_double_quotes())
            printf("\033[0;32mOK\033[0m\n");
        else
            printf("\033[0;31mKO\033[0m\n");
    test_with_print();
}
