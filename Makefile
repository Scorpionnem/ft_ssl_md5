NAME = ft_ssl

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES =	-I ./includes/\
			-I ./libft/\
			-I ./libftgetopt/includes/\

SRCS =	src/main.c

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)

LIBFT = ./libft/libft.a

LIBFTGETOPTDIR = libftgetopt
LIBFTGETOPT = ./$(LIBFTGETOPTDIR)/libftgetopt.a

all: libftgetopt $(LIBFT) $(NAME)

libftgetopt:
	@if ls | grep -q "$(LIBFTGETOPTDIR)"; then \
		echo "\033[32;1;4mlibftgetopt Found\033[0m"; \
	else \
		echo "\033[31;1;4mlibftgetopt Not Found\033[0m"; \
		echo "\033[31;1mCloning libftgetopt from github\033[0m"; \
		git clone https://github.com/Scorpionnem/libftgetopt $(LIBFTGETOPTDIR); \
		make -C $(LIBFTGETOPTDIR) ;\
	fi

re: fclean all

$(LIBFT):
	@make -C ./libft bonus

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) $(LIBFTGETOPT)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@make -C ./libft clean
	@echo Cleaning objects
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ./libft fclean
	@echo Cleaning $(NAME)
	@rm -rf $(NAME)
	@rm -rf $(LIBFTGETOPTDIR)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run libftgetopt

-include $(DEPS)
