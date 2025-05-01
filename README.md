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
### handle rediraction

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

### add path to commands

### handle signals

### Add status executed command. Now it is in env

### Add is_exit variable. where should it be?

### where should be status of executed command?
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