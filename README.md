```bash
┌─────────────────┐
│   main()        │
│  argc == 2?     │──────┐ No ── Error("Arguments") ── exit(1)
└─────────┬───────┘      │
          │ Yes
          ▼
┌─────────────────┐      │
│ check_file()    │──────┘
│  .cub?          │
│  exists?        │── No ── Error("File") ── exit(1001/1002)
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ get_full_file() │
│ 2-pass GNL      │
│ count lines     │── Fail ── Error("Empty") ── NULL
│ → read_file     │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ check_config()  │
│ initial_state?  │── No ── NULL
└─────────┬───────┘
          │ Yes
          ▼
┌─────────────────┐
│ check_file_lines│ ← trim(line)
└─────────┬───────┘
          │
     ┌────┼────┐
     │    │    │
     ▼    ▼    ▼
┌───────┐ ┌───────┐ ┌──────────┐
│Texture│ │ Color │ │ Map line │
│NO/SO  │ │F/C RGB│ │detected  │
│WE/EA  │ │       │ │          │
└──┬───┘ └──┬──┘ └──┬──────┘
   │        │        │
   ▼        ▼        ▼
check_tex() check_color()  map_index = i
   │           │
   ▼           ▼
ft_strndup()  ft_split(,)
"NO " → path  "220,100,0"
   │           │
   ▼           ▼
.png? fd?     3 RGB? nums?
store NO/SO/  store_rgb()
WE/EA path    → packed int

Invalid char 'X'   → Error("Invalid character") → 0
Player count ≠ 1   → Error("exactly one player") → 0
Player/0 touches space → Error("not surrounded") → 0
Perfect map        → 1
    
EVERY FAIL → EXACT FREE CHAIN:
├── parcing() fail → free2D(read_file) + free_texture()
├── check_tex() → free(side)
├── check_color() → free(side) + free(rgb_str) + free2D(slice_rgb)
├── get_map() → NULL (no alloc yet)
├── map_copy_s() → free2D(map)
├── validate_map() → free2D(map) + free2D(map_s)
└── free_texture() → free(NO,SO,WE,EA) + NULL assign

✅ 1×NO + 1×SO + 1×WE + 1×EA + 1×F + 1×C = 6
✅ Exactly 1 player spawn (N/S/E/W)
✅ Map fully walled (no leaks)
✅ All textures exist + .png
✅ RGB 0-255 range
✅ map_s rectangular + bordered
```

## 1️⃣ What is MiniLibX (really)?

**MiniLibX (MLX)** is the graphic library you use in **Cub3D** to open a window and draw pixels. Nothing magic — just a thin bridge between **your C code** and the OS window system.


MiniLibX is a **very small graphics library** provided by 42.

It lets you:

* Open a window 🪟
* Create images (pixel buffers)
* Put pixels in memory
* Display that memory on the screen
* Capture keyboard events

👉 **Important**:
- MLX does **NOT** draw walls, rays, or textures for you.
- You do **all the math**, MLX just **shows pixels**.
- Cub3D = **Raycasting engine written by YOU**, not MLX.

---

## 3️⃣ Core MLX objects (you MUST know these)

```c
🔹"Connection to the graphical system. `mlx_ptr`"
mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize);
void *mlx;
mlx = mlx_init();
+-> returning an opaque pointer that represents this connection.
|--->If this fails → program should exit.
This memory persists until you call mlx_destroy_display() or your program exits
```
---

## 5️⃣ Keyboard & events (basic)

### Close window ❌

```c
mlx_hook(win, 17, 0, close_game, &data);
```

### Keyboard press ⌨️

```c
mlx_hook(win, 2, 1L<<0, key_press, &data);
```

# Main loop 🔁
```c
mlx_loop(mlx);
* waits for events
* calls your functions
* redraws the screen
```

### 🐢 What is MLX42?
```
Your computer screen ←── MLX42 ←── Your code
Your keyboard ───────┘
```

#### 🐢 SIMPLE EXPLANATION - What is MLX42?
|-- MLX = window + image + events
|-- Cub3D = math + logic + pixels
|-- Your window = empty paper
|-- Your code = crayons
|-- draw_floor_ceiling() = first crayon strokes

#### 📁 Your Repository Files EXPLAINED:
```bash
cub3D/                           # Main project
├── Makefile                     # Builds everything
├── main.c                       # Game brain (parsing + MLX42)
├── include/
│   └── parcing.h                # t_var + t_cub structs
├── parcing/                     # YOUR parser genius ✨
├── utils/
│   ├── libft/                   # String functions
│   ├── printf/               # Printf replacement  
│   └── get_next_line/           # Read .cub file
└── libmlx42_linux.a             # MLX42 library (window + keys)

✅ Parser reads map1.cub → extracts colors/textures/map
✅ MLX42 creates 640x480 window  
✅ Window stays open (mlx_loop())
✅ Ready to draw floor/ceiling colors
```


🐢 STEP 2: Draw Floor/Ceiling Colors (SIMPLE)

- MLX42 pixels = 32-bit colors (8R+8G+8B+8Alpha)
- your parser → 0xDC6400 (24-bit) → uint32_t perfect