# minishell
42 project minishell

## Bugs

+ ### Double and single quotes should not be echoed

echo path: /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/binnhome: /Users/sveta
path: /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
home: /Users/sveta

### DONE
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
