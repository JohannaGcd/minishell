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
```shell
minishell>cd $PWD
minishell>
==6152== 
==6152== HEAP SUMMARY:
==6152==     in use at exit: 232,897 bytes in 238 blocks
==6152==   total heap usage: 608 allocs, 370 frees, 259,836 bytes allocated
==6152==
==6152== 46 bytes in 1 blocks are definitely lost in loss record 19 of 78
==6152==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6152==    by 0x10EC80: ft_strdup (in /mnt/c/Users/storb/Documents/GitHub/minishell/minishell)
==6152==    by 0x10E4C2: extract_env (extract_env.c:29)
==6152==    by 0x10E896: process_dollar_sign (expand_env_utils.c:62)
==6152==    by 0x10E62D: expand_env (expand_env.c:60)
==6152==    by 0x10989A: mshell_lexer (mshell_parser.c:33)
==6152==    by 0x10960C: main (main.c:39)
==6152==
==6152== LEAK SUMMARY:
==6152==    definitely lost: 46 bytes in 1 blocks
==6152==    indirectly lost: 0 bytes in 0 blocks
==6152==      possibly lost: 0 bytes in 0 blocks
==6152==    still reachable: 232,851 bytes in 237 blocks
==6152==         suppressed: 0 bytes in 0 blocks
==6152== Reachable blocks (those to which a pointer was found) are not shown.
==6152== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==6152==
==6152== For lists of detected and suppressed errors, rerun with: -s
==6152== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
### memory error
``` shell
valgrind --leak-check=full  ./minishell
==6616== Memcheck, a memory error detector
==6616== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==6616== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==6616== Command: ./minishell
==6616==
==6616== error calling PR_SET_PTRACER, vgdb might block
minishell>echo "$PWD is pwd"
token->type=6, token_str=echo
token->type=7, token_str=
token->type=3, token_str="$PWD is pwd"
after expend
token->type=6, token_str=echo
token->type=7, token_str=
token->type=3, token_str="/mnt/c/Users/storb/Documents/GitHub/minishell is pwd"
==6616== Invalid write of size 8
==6616==    at 0x10ACCB: copy_command_args (parser_cmd_arg.c:27)
==6616==    by 0x10AD4C: fill_command (parser_cmd_arg.c:43)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==  Address 0x4b45cc0 is 0 bytes after a block of size 16 alloc'd
==6616==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6616==    by 0x10AD1F: fill_command (parser_cmd_arg.c:38)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==
command[0]=echo
command[1]=/mnt/c/Users/storb/Documents/GitHub/minishell is pwd
==6616== Invalid read of size 8
==6616==    at 0x109A6E: mshell_parser (mshell_parser.c:76)
==6616==    by 0x10960C: main (main.c:39)
==6616==  Address 0x4b45cc0 is 0 bytes after a block of size 16 alloc'd
==6616==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6616==    by 0x10AD1F: fill_command (parser_cmd_arg.c:38)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==
==6616== Invalid read of size 8
==6616==    at 0x10D2C0: number_arguments (execute_utils.c:20)
==6616==    by 0x10D235: exec_echo (execute_echo.c:43)
==6616==    by 0x10C874: execute_builtin (execute_built_in.c:38)
==6616==    by 0x10C928: redirect_for_builtin (execute_built_in.c:66)
==6616==    by 0x10B966: execute_commands (executer.c:64)
==6616==    by 0x109AFD: mshell_executer (mshell_executer.c:18)
==6616==    by 0x10960C: main (main.c:39)
==6616==  Address 0x4b45cc0 is 0 bytes after a block of size 16 alloc'd
==6616==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6616==    by 0x10AD1F: fill_command (parser_cmd_arg.c:38)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==
==6616== Invalid read of size 8
==6616==    at 0x10D2C0: number_arguments (execute_utils.c:20)
==6616==    by 0x10D249: exec_echo (execute_echo.c:48)
==6616==    by 0x10C874: execute_builtin (execute_built_in.c:38)
==6616==    by 0x10C928: redirect_for_builtin (execute_built_in.c:66)
==6616==    by 0x10B966: execute_commands (executer.c:64)
==6616==    by 0x109AFD: mshell_executer (mshell_executer.c:18)
==6616==    by 0x10960C: main (main.c:39)
==6616==  Address 0x4b45cc0 is 0 bytes after a block of size 16 alloc'd
==6616==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6616==    by 0x10AD1F: fill_command (parser_cmd_arg.c:38)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==
/mnt/c/Users/storb/Documents/GitHub/minishell is pwd
==6616== Invalid read of size 8
==6616==    at 0x109C31: clean_commands (mshell_clean.c:48)
==6616==    by 0x109B2D: mshell_executer (mshell_executer.c:23)
==6616==    by 0x10960C: main (main.c:39)
==6616==  Address 0x4b45cc0 is 0 bytes after a block of size 16 alloc'd
==6616==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6616==    by 0x10AD1F: fill_command (parser_cmd_arg.c:38)
==6616==    by 0x10ADE0: extract_commands (parser_cmd_arg.c:64)
==6616==    by 0x109A06: mshell_parser (mshell_parser.c:69)
==6616==    by 0x10960C: main (main.c:39)
==6616==
```

### TODO

### memory leak $env in quotes
``` shell
valgrind --leak-check=full  ./minishell
==30908== Memcheck, a memory error detector
==30908== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==30908== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==30908== Command: ./minishell
==30908==
==30908== error calling PR_SET_PTRACER, vgdb might block
minishell>echo "PWD is $PWD"
PWD is /mnt/c/Users/storb/Documents/GitHub/minishell
minishell>exit
==30908== 
==30908== HEAP SUMMARY:
==30908==     in use at exit: 232,949 bytes in 241 blocks
==30908==   total heap usage: 623 allocs, 382 frees, 260,091 bytes allocated
==30908==
==30908== 46 bytes in 1 blocks are definitely lost in loss record 18 of 78
==30908==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==30908==    by 0x10ECAB: ft_strdup (in /mnt/c/Users/storb/Documents/GitHub/minishell/minishell)
==30908==    by 0x10E4E6: extract_env (extract_env.c:29)
==30908==    by 0x10DEDE: fill_result (expansion.c:83)
==30908==    by 0x10DFE7: change_all_env (expansion.c:109)
==30908==    by 0x10E5D7: process_double_quotes (expand_env.c:41)
==30908==    by 0x10E671: expand_env (expand_env.c:64)
==30908==    by 0x10989A: mshell_lexer (mshell_parser.c:33)
==30908==    by 0x10960C: main (main.c:39)
==30908==
==30908== LEAK SUMMARY:
==30908==    definitely lost: 46 bytes in 1 blocks
==30908==    indirectly lost: 0 bytes in 0 blocks
==30908==      possibly lost: 0 bytes in 0 blocks
==30908==    still reachable: 232,903 bytes in 240 blocks
==30908==         suppressed: 0 bytes in 0 blocks
==30908== Reachable blocks (those to which a pointer was found) are not shown.
==30908== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==30908==
==30908== For lists of detected and suppressed errors, rerun with: -s
==30908== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
### CTRL+D after syntax error

``` shell
minishell>echo " '
syntax error
minishell>
=================================================================
==5805==ERROR: AddressSanitizer: heap-use-after-free on address 0x603000002750 at pc 0x0001002850c8 bp 0x00016fb7ec10 sp 0x00016fb7ec08
READ of size 8 at 0x603000002750 thread T0
    #0 0x0001002850c4 in clean_tokens lexer_clean.c:30
    #1 0x0001002823e0 in mshell_clean mshell_clean.c:71
    #2 0x000100280af0 in main main.c:39
    #3 0x00019904ab94 in start+0x17b8 (dyld:arm64e+0xfffffffffff3ab94)

0x603000002750 is located 16 bytes inside of 24-byte region [0x603000002740,0x603000002758)
freed by thread T0 here:
    #0 0x000100ae9480 in free+0x7c (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x3d480)
    #1 0x00010028515c in clean_tokens lexer_clean.c:33
    #2 0x000100281914 in mshell_syntaxer mshell_parser.c:60
    #3 0x000100280af0 in main main.c:39
    #4 0x00019904ab94 in start+0x17b8 (dyld:arm64e+0xfffffffffff3ab94)

previously allocated by thread T0 here:
    #0 0x000100ae938c in malloc+0x78 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x3d38c)
    #1 0x000100282d78 in create_new_token lexer_list_utils.c:20
    #2 0x0001002848e0 in extract_tokens lexer.c:75
    #3 0x000100281548 in mshell_lexer mshell_parser.c:18
    #4 0x000100280af0 in main main.c:39
    #5 0x00019904ab94 in start+0x17b8 (dyld:arm64e+0xfffffffffff3ab94)

SUMMARY: AddressSanitizer: heap-use-after-free lexer_clean.c:30 in clean_tokens
Shadow bytes around the buggy address:
  0x603000002480: 00 fa fa fa 00 00 05 fa fa fa fd fd fd fa fa fa
  0x603000002500: 00 00 00 fa fa fa 00 00 04 fa fa fa fd fd fd fd
  0x603000002580: fa fa 00 00 00 fa fa fa 00 00 00 02 fa fa 00 00
  0x603000002600: 00 fa fa fa 00 00 00 01 fa fa fd fd fd fd fa fa
  0x603000002680: fd fd fd fd fa fa fd fd fd fd fa fa fd fd fd fd
=>0x603000002700: fa fa 00 00 00 fa fa fa fd fd[fd]fa fa fa fd fd
  0x603000002780: fd fa fa fa fd fd fd fa fa fa fa fa fa fa fa fa
  0x603000002800: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x603000002880: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x603000002900: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x603000002980: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==5805==ABORTING
zsh: abort      ./minishell
```
