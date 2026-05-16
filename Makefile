NAME    = cub3D

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
IFLAGS  = -I includes -I minilibx-linux

MLX_DIR = minilibx-linux
MLX     = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ── Sources ────────────────────────────────────────────────────────────────────

SRC_PARSING = src/parsing/parse.c           \
              src/parsing/parse_identifiers.c \
              src/parsing/parse_map.c        \
              src/parsing/parse_utils.c

SRC_ENGINE  = src/engine/main.c             \
              src/engine/init.c

SRC_PLAYER  = src/player/player.c

SRC_RENDER  = src/rendering/raycasting.c    \
              src/rendering/render.c        \
              src/rendering/draw_scene.c

SRC = $(SRC_PARSING) $(SRC_ENGINE) $(SRC_PLAYER) $(SRC_RENDER)
OBJ = $(SRC:.c=.o)

# ── Rules ──────────────────────────────────────────────────────────────────────

all: $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
