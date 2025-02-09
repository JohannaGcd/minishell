NAME = libft.a
CC = cc

CFLAG = -Wextra -Werror -Wall
AR = ar rcs

SRCS = ft_strlen.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_atoi.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_strchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncpm.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line.c \
		get_free_line.c \
		ft_tolower_string.c \
		ft_atoi_base.c 


SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstclear_bonus.c

OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

OBJS = $(SRCS:%.c=%.o)
#OBJS = ft_strlen.o ft_isalpha.o ft_isalnum.o ft_atoi.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_strchr.o ft_tolower.o ft_toupper.o


%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)


all: $(NAME)
	bonus

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	
bonus: $(NAME) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ_BONUS)

re: fclean all


