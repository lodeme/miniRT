NAME    := minirt
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g -O0
LIBFT   := ./libraries/libft
LIBMLX  := ./libraries/mlx42
HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm
SRCS    :=	source/main.c \
						source/free.c \
						source/init.c
OBJ_DIR := obj
SRC_DIRS := $(sort $(dir $(SRCS)))
OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))
OBJS    := $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: directories libmlx libft $(NAME)

directories:
	@mkdir -p $(OBJ_DIRS)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all
