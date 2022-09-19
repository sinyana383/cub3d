NAME        := cub3D

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCFLAGS 	= -MMD -I./inc

LIBS      := -Lmlx -lmlx -framework OpenGL -framework AppKit

VPATH 		= src/ 

SRCS        = main.c


ODIR        = tmp
OBJS        = $(SRCS:%.c=$(ODIR)/%.o)

DDIR        = tmp
DEPS        = $(SRCS:%.c=$(DDIR)/%.d)

.PHONY: all clean fclean re bonus deb

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

$(DEPS):
include $(wildcard $(DEPS))

all: $(NAME)

deb:
	gcc $(INCFLAGS) -g */*.c */*/*.c */*/*/*.c -o $@ $(LIBS)

clean:
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all