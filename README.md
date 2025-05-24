# minishell
42 project minishell

### DONE

## Bugs

+ ### Double and single quotes should not be echoed

echo path: /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/binnhome: /Users/sveta
path: /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
home: /Users/sveta

### | does not work for parser - works
### FR01 export command -> add env 
### FR02 ececute env command
### add redirections  in parser
### buildin commands: pwd export unset
### bug with parser ls | grep "text" or ls | grep 'text'(there is no command grep). There is no such problem with  ls | grep text 
minishell > echo "bla" "bla-bla"
debug LEXER
token_type: 6, token_str: echo
token_type: 7, token_str:  
token_type: 3, token_str: "bla"
token_type: 7, token_str:  
token_type: 3, token_str: "bla-bla"
debug SYNTAXER
debug PARSER
cmd args nbr: 1
debug new_command[0] = ???
debug new_command[1] = bla
debug new_command[2] = bla-bla
debug EXECUTER
debug current command ???
execvp failed: No such file or directory

### BUG empty line, enter
### BUG space, enter

### bug: command->in 0xbebebebebebebebe should be NULL
minishell > ls
debug LEXER
token_type: 6, token_str: ls
token_type: 6, token_str: ls
debug SYNTAXER
debug PARSER
debug EXECUTER
command->in 0xbebebebebebebebe
AddressSanitizer:DEADLYSIGNAL
=================================================================
==53482==ERROR: AddressSanitizer: SEGV on unknown address 0xffffd847d7d9d7d7 (pc 0x000104d58b6c bp 0x00016b0b3090 sp 0x00016b0b2f50 T0)
==53482==The signal is caused by a READ memory access.
    #0 0x104d58b6c in handle_heredoc execute_heredoc.c:53
    #1 0x104d5645c in execute_single_command executer.c:84
    #2 0x104d56fa4 in execute_commands executer.c:163
    #3 0x104d4ea08 in mshell_executer mshell_executer.c:19
    #4 0x104d4dbcc in main main.c:34
    #5 0x19b9cf150  (<unknown module>)

## TODO

### HEREDOC: 1. handle env expansion 2. handle signals 3. handle exit status 4. modify calling function so that heredoc is only called when needed.

### handle multiply command in executer

### buildin commands: echo cd pwd export unset env exit

### handle signals

### Add status executed command. Now it is in env


# HANDLE EXIT STATUS OF LAST COMMAND AND OF MINISHELL
### Add is_exit variable. where should it be?
### where should be status of executed command?
### where should be the status that we need to exit after execution?
### where should be the status that we need to exit after execution?

### check what will be if remove PATH 
### check how works changing env


### ls > 1.txt
    more 1.txt
    1.txt: Permission denied
     ls -la |grep txt
     ----r-----    1 sveta  staff     127 May  1 05:43 1.txt - add another permisions to file during the creation

### add execution built in commands into multicomands

### check memory leak with valgrind 

### env should be changed if it is already exists

### BUGS!!!!

### minishell>echo "jsjj" > ppp (1 builtin command with redirrect)

### expand_env memory leak

```shell
 valgrind --leak-check=full ./minishell
==2498== Memcheck, a memory error detector
==2498== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==2498== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==2498== Command: ./minishell
==2498==
==2498== error calling PR_SET_PTRACER, vgdb might block
minishell>cd $PWD
minishell>pwd
/mnt/c/Users/storb/Documents/GitHub/minishell
minishell>env | grep PWD
PWD=/mnt/c/Users/storb/Documents/GitHub/minishell
minishell>exit
==2498== 
==2498== HEAP SUMMARY:
==2498==     in use at exit: 233,029 bytes in 247 blocks
==2498==   total heap usage: 674 allocs, 427 frees, 263,242 bytes allocated
==2498==
==2498== 46 bytes in 1 blocks are definitely lost in loss record 17 of 78
==2498==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2498==    by 0x10EC64: ft_strdup (in /mnt/c/Users/storb/Documents/GitHub/minishell/minishell)
==2498==    by 0x10E4B6: extract_env (extract_env.c:29)
==2498==    by 0x10E886: process_dollar_sign (expand_env_utils.c:62)
==2498==    by 0x10E621: expand_env (expand_env.c:60)
==2498==    by 0x10989A: mshell_lexer (mshell_parser.c:33)
==2498==    by 0x10960C: main (main.c:39)
==2498==
==2498== LEAK SUMMARY:
==2498==    definitely lost: 46 bytes in 1 blocks
==2498==    indirectly lost: 0 bytes in 0 blocks
==2498==      possibly lost: 0 bytes in 0 blocks
==2498==    still reachable: 232,983 bytes in 246 blocks
==2498==         suppressed: 0 bytes in 0 blocks
==2498== Reachable blocks (those to which a pointer was found) are not shown.
==2498== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==2498==
==2498== For lists of detected and suppressed errors, rerun with: -s
==2498== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```