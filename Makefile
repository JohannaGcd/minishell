NAME = minishell

CC = cc
CFLAGS = -g -O0 -Wextra -Werror -Wall

HEADERS = -I ./include

LIBFLAGS = -lreadline

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCDIR = src
OBJDIR = obj

SRCDIR_LEXER = $(SRCDIR)/lexer
OBJDIR_LEXER = objs_lexer

SRCDIR_SYNTAXER = $(SRCDIR)/syntaxer
OBJDIR_SYNTAXER = objs_syntax_checker

SRCDIR_PARSER = $(SRCDIR)/parser
OBJDIR_PARSER = objs_parser

SRCDIR_EXECUTER = $(SRCDIR)/executer
OBJDIR_EXECUTER = objs_executer

SRCDIR_ENV = $(SRCDIR)/env
OBJDIR_ENV = objs_env

SRC = main.c
SRC_LEXER = lexer_list_utils.c lexer_utils.c lexer.c lexer_token_env.c
SRC_PARSER = parser.c
SRC_EXECUTER = executer.c 
SRC_ENV = init_env.c expansion.c
SRC_SYNTAXER = syntaxer.c syntaxer_utils.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o) \
	$(SRC_LEXER:%.c=$(OBJDIR_LEXER)/%.o) \
	$(SRC_SYNTAXER:%.c=$(OBJDIR_SYNTAXER)/%.o) \
	$(SRC_PARSER:%.c=$(OBJDIR_PARSER)/%.o) \
	$(SRC_EXECUTER:%.c=$(OBJDIR_EXECUTER)/%.o) \
	$(SRC_ENV:%.c=$(OBJDIR_ENV)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) $(LIBFT) -o $@ 

$(LIBFT):
	@make -s -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_LEXER)/%.o: $(SRCDIR_LEXER)/%.c  $(OBJDIR_LEXER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_SYNTAXER)/%.o: $(SRCDIR_SYNTAXER)/%.c  $(OBJDIR_SYNTAXER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR_PARSER)/%.o: $(SRCDIR_PARSER)/%.c  $(OBJDIR_PARSER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_EXECUTER)/%.o: $(SRCDIR_EXECUTER)/%.c  $(OBJDIR_EXECUTER)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

$(OBJDIR_ENV)/%.o: $(SRCDIR_ENV)/%.c  $(OBJDIR_ENV)
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

clean:
	@rm -rf obj*
	@make -s -C $(LIBFTDIR) clean
	@printf "Object files are removed\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@printf "$(NAME) is removed\n"