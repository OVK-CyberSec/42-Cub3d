*This project has been created as part of the 42 curriculum.*

# cub3D — My first RayCaster with miniLibX

## Description

cub3D is a 42 school project inspired by **Wolfenstein 3D** (Id Software, 1992), the first true First-Person Shooter in video game history.

The goal is to build a dynamic 3D view inside a maze from a first-person perspective using **ray-casting** (DDA algorithm), rendered with the **miniLibX** graphics library.

**What the project implements:**
- Full `.cub` scene file parser (textures, colors, map)
- DDA ray-casting engine with fish-eye correction
- Directional wall textures (North, South, East, West)
- Configurable floor and ceiling colors (RGB)
- Smooth window management and keyboard controls
- Complete map validation (closed walls, single player, valid characters)

---

## Project Structure

```
cub3D/
├── Makefile
├── README.md
├── includes/
│   └── cub3d.h              ← all structs, defines, prototypes
├── src/
│   ├── parsing/
│   │   ├── parse.c          ← top-level parser entry point
│   │   ├── parse_identifiers.c  ← NO/SO/WE/EA/F/C parsing
│   │   ├── parse_map.c      ← map reading + validation
│   │   └── parse_utils.c    ← string utils + ft_error + free
│   ├── engine/
│   │   ├── main.c           ← main(), cub(), player_position()
│   │   └── init.c           ← mlx init, textures, colors
│   ├── player/
│   │   └── player.c         ← movement, key hooks, close
│   └── rendering/
│       ├── raycasting.c     ← DDA algorithm
│       ├── render.c         ← render loop, put_pixel, texture select
│       └── draw_scene.c     ← column drawing, scene composition
├── images/
│   ├── NO.xpm
│   ├── SO.xpm
│   ├── WE.xpm
│   └── EA.xpm
└── maps/
    └── test.cub
```

---

## Instructions

### Requirements

- Linux with X11
- miniLibX (included in `minilibx-linux/`)
- `cc`, `make`, `libXext`, `libX11`

### Compilation

```bash
make
```

### Execution

```bash
./cub3D maps/test.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` `→` | Rotate view |
| `ESC` | Quit |
| Red cross | Quit |

### Makefile rules

```bash
make        # build
make clean  # remove objects
make fclean # remove objects + binary
make re     # full rebuild
make bonus  # alias for all
```

---

## Scene file format (`.cub`)

```
NO ./images/NO.xpm      # North wall texture
SO ./images/SO.xpm      # South wall texture
WE ./images/WE.xpm      # West wall texture
EA ./images/EA.xpm      # East wall texture

F 50,50,50              # Floor color (R,G,B)
C 100,150,200           # Ceiling color (R,G,B)

1111111
1000001
100N001          # N = player spawn facing North
1000001
1111111
```

**Map characters:**
- `1` — wall
- `0` — empty space
- `N` / `S` / `E` / `W` — player spawn + facing direction
- ` ` (space) — valid outside map boundaries

**Rules:**
- Map must be the **last element** in the file
- Map must be **fully enclosed by walls**
- Exactly **one** player spawn
- At least **3 lines** high

---

## Resources

### Ray-casting references
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the reference for DDA-based ray-casting
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — MiniLibX API reference
- [Wolfenstein 3D (playable)](http://users.atw.hu/wolf3d/) — original game to test before starting

### AI usage
AI (Claude) was used to:
- Help structure the project into logical modules (parsing / engine / player / rendering)
- Generate boilerplate for the parsing layer and error handling system (`ft_error` + `ERR_*` defines)
- Suggest the flood-fill approach for closed-map validation
- Review and debug the DDA fish-eye correction formula

All generated code was reviewed, understood, and adapted manually before inclusion.
