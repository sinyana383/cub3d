NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCFLAGS 	= -MMD -I./inc -I./libs/libmlx

LDFLAGS		= -L./libs/libmlx
LDLIBS		= -lmlx -framework OpenGL -framework AppKit

VPATH 		= src/ src/get_next_line/ src/libft/ src/realizer src/parser

SRCS        = main.c \
				get_lines.c get_lines_utils.c get_next_line.c get_next_line_utils.c\
				ft_strlen.c ft_strnstr.c ft_strchr.c\
				draw_fun.c find_dist_and_draw_column.c draw_column.c set_img_x_and_data_tex.c hooks.c\
				color_texture.c parse.c utilit_map.c utilt.c

LIBS		= libs/libmlx/libmlx.a

ODIR        = tmp
OBJS        = $(SRCS:%.c=$(ODIR)/%.o)

DDIR        = tmp
DEPS        = $(SRCS:%.c=$(DDIR)/%.d)

.PHONY: all clean fclean re bonus deb

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

%.a:
	$(MAKE) -C $(dir $@)

all: $(NAME)

deb: $(LIBS)
	gcc $(INCFLAGS) $(LDFLAGS) -g src/*.c src/*/*.c -o $@ $(LDLIBS)

clean:
	$(MAKE) -C libs/libmlx clean
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(DEPS):
include $(wildcard $(DEPS))