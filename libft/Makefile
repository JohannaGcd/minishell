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
		ft_strncmp.c \
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
		ft_atoi_base.c \
		ft_max.c\
		ft_is_number.c \
		ft_strjoin_with_char.c\
		ft_strcpy.c


SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstclear_bonus.c

OBJS = $(SRCS:%.c=%.o) $(SRC_BONUS:%.c=%.o) 

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all


