NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCFLAGS 	= -I./inc -I./libmlx

LDFLAGS		= -L./libmlx
LDLIBS		= -lmlx -framework OpenGL -framework AppKit

VPATH 		= src/ 

SRCS        = main.c


ODIR        = tmp
OBJS        = $(SRCS:%.c=$(ODIR)/%.o)

DDIR        = tmp
DEPS        = $(SRCS:%.c=$(DDIR)/%.d)

.PHONY: all clean fclean re bonus deb

$(NAME): libmlx/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

%.a:
	$(MAKE) -C $(dir $@)

all: $(NAME)

deb: libmlx/libmlx.a
	gcc $(INCFLAGS) $(LDFLAGS) -g src/*.c -o $@ $(LDLIBS)

clean:
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(MAKE) -C libmlx clean
	$(RM) $(NAME)

re: fclean all

$(DEPS):
include $(wildcard $(DEPS))