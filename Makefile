NAME = minishell
TEST = test

CC = cc
CFLAGS = -g -O0 -Wextra -Werror -Wall -I/opt/homebrew/opt/readline/include #-fsanitize=address
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

HEADERS = -I ./include

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCDIR = src
OBJDIR = obj

SRCDIR_LEXER = $(SRCDIR)/lexer
OBJDIR_LEXER = objs_lexer

SRCDIR_SYNTAXER = $(SRCDIR)/syntaxer
OBJDIR_SYNTAXER = objs_syntaxer

SRCDIR_PARSER = $(SRCDIR)/parser
OBJDIR_PARSER = objs_parser

SRCDIR_EXECUTER = $(SRCDIR)/executer
OBJDIR_EXECUTER = objs_executer

SRCDIR_ENV = $(SRCDIR)/env
OBJDIR_ENV = objs_env

SRCDIR_TEST = src_tests
OBJDIR_TEST = objs_tests

SRC = main.c mshell_start.c mshell_parser.c mshell_executer.c mshell_clean.c mshell_signals.c
SRC_LEXER = lexer_list_utils.c lexer_utils.c lexer.c lexer_token_env.c lexer_clean.c
SRC_PARSER = parser_cmd_arg.c parser_redir.c parser_utils.c
SRC_EXECUTER = executer.c redirect.c execute_env.c execute_export.c execute_unset.c \
			execute_exit.c execute_heredoc.c path_command.c clean_in_exec.c execute_built_in.c \
			execute_cmd.c execute_pwd.c execute_cd.c execute_echo.c execute_utils.c execute_single_cmd.c
SRC_ENV = init_env.c expansion.c remove_env.c envs_to_envp.c clean_env.c find_env.c extract_env.c 
SRC_SYNTAXER = syntaxer.c syntaxer_utils.c
SRC_TEST = test.c test_lexer.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o) \
	$(SRC_LEXER:%.c=$(OBJDIR_LEXER)/%.o) \
	$(SRC_SYNTAXER:%.c=$(OBJDIR_SYNTAXER)/%.o) \
	$(SRC_PARSER:%.c=$(OBJDIR_PARSER)/%.o) \
	$(SRC_EXECUTER:%.c=$(OBJDIR_EXECUTER)/%.o) \
	$(SRC_ENV:%.c=$(OBJDIR_ENV)/%.o)

OBJ_TEST = $(SRC_TEST:%.c=$(OBJDIR_TEST)/%.o) \
	$(SRC_LEXER:%.c=$(OBJDIR_LEXER)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ)  $(LIBFT) $(LDFLAGS) -o $@ 

$(TEST): $(OBJ_TEST) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_TEST) $(LIBFLAGS) $(LIBFT) -o $@ 

$(LIBFT):
	@make -s -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_LEXER)/%.o: $(SRCDIR_LEXER)/%.c $(OBJDIR_LEXER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_SYNTAXER)/%.o: $(SRCDIR_SYNTAXER)/%.c $(OBJDIR_SYNTAXER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR_PARSER)/%.o: $(SRCDIR_PARSER)/%.c $(OBJDIR_PARSER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_EXECUTER)/%.o: $(SRCDIR_EXECUTER)/%.c $(OBJDIR_EXECUTER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_ENV)/%.o: $(SRCDIR_ENV)/%.c $(OBJDIR_ENV)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_TEST)/%.o: $(SRCDIR_TEST)/%.c $(OBJDIR_TEST)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR_LEXER):
	@mkdir -p $@

$(OBJDIR_SYNTAXER):
	@mkdir -p $@

$(OBJDIR_PARSER):
	@mkdir -p $@

$(OBJDIR_EXECUTER):
	@mkdir -p $@

$(OBJDIR_ENV):
	@mkdir -p $@

$(OBJDIR_TEST):
	@mkdir -p $@

clean:
	@rm -rf obj*
	@make -s -C $(LIBFTDIR) clean
	@printf "Object files are removed\n"

fclean: clean
	@rm -f $(NAME) $(TEST)
	@make -s -C $(LIBFTDIR) fclean
	@printf "$(NAME) and $(TEST) are removed\n"

re: fclean all