#include "include/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define SPRITE_SIZE 32
#define MOVE_SPEED 5

typedef struct {
    mlx_t* mlx;
    mlx_image_t* player_sprite;
    mlx_image_t* background;
    int32_t player_instance;
    int player_x;
    int player_y;
} game_t;

// Create a simple colored sprite
mlx_image_t* create_colored_sprite(mlx_t* mlx, uint32_t color, int size) {
    mlx_image_t* img = mlx_new_image(mlx, size, size);
    if (!img)
        return NULL;

    // Fill the sprite with the specified color
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int pixel_index = (y * size + x) * 4;
            // Convert color to RGBA format
            img->pixels[pixel_index] = (color >> 24) & 0xFF;     // Red
            img->pixels[pixel_index + 1] = (color >> 16) & 0xFF; // Green
            img->pixels[pixel_index + 2] = (color >> 8) & 0xFF;  // Blue
            img->pixels[pixel_index + 3] = color & 0xFF;         // Alpha
        }
    }
    return img;
}

// Create a grid background for visual reference
mlx_image_t* create_grid_background(mlx_t* mlx, int width, int height) {
    mlx_image_t* bg = mlx_new_image(mlx, width, height);
    if (!bg)
        return NULL;

    // Fill with dark background
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel_index = (y * width + x) * 4;

            // Create grid lines every 32 pixels
            if (x % 32 == 0 || y % 32 == 0) {
                bg->pixels[pixel_index] = 50;      // Dark gray grid
                bg->pixels[pixel_index + 1] = 50;
                bg->pixels[pixel_index + 2] = 50;
                bg->pixels[pixel_index + 3] = 255;
            } else {
                bg->pixels[pixel_index] = 20;      // Very dark background
                bg->pixels[pixel_index + 1] = 20;
                bg->pixels[pixel_index + 2] = 20;
                bg->pixels[pixel_index + 3] = 255;
            }
        }
    }
    return bg;
}

// Key handler for movement
void key_handler(mlx_key_data_t keydata, void* param) {
    game_t* game = (game_t*)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        int new_x = game->player_x;
        int new_y = game->player_y;

        switch (keydata.key) {
            case MLX_KEY_W:
            case MLX_KEY_UP:
                new_y -= MOVE_SPEED;
                break;
            case MLX_KEY_S:
            case MLX_KEY_DOWN:
                new_y += MOVE_SPEED;
                break;
            case MLX_KEY_A:
            case MLX_KEY_LEFT:
                new_x -= MOVE_SPEED;
                break;
            case MLX_KEY_D:
            case MLX_KEY_RIGHT:
                new_x += MOVE_SPEED;
                break;
            case MLX_KEY_ESCAPE:
                mlx_close_window(game->mlx);
                return;
        }

        // Boundary checking
        if (new_x >= 0 && new_x <= WIDTH - SPRITE_SIZE &&
            new_y >= 0 && new_y <= HEIGHT - SPRITE_SIZE) {

            // Update position
            game->player_x = new_x;
            game->player_y = new_y;

            // Move the instance visually
            game->player_sprite->instances[game->player_instance].x = new_x;
            game->player_sprite->instances[game->player_instance].y = new_y;

            printf("Player moved to: (%d, %d)\n", new_x, new_y);
        }
    }
}

// Smooth movement with animation loop
void smooth_movement_loop(void* param) {
    static int direction = 1;
    static int auto_x = 100;
    game_t* game = (game_t*)param;

    // Example of programmatic smooth movement
    auto_x += direction * 2;

    if (auto_x >= WIDTH - 100 || auto_x <= 100)
        direction *= -1;

    // You can create multiple instances for demonstration
    // This shows how instances work independently
}

int main(void) {
    game_t game = {0};

    // Initialize MLX
    game.mlx = mlx_init(WIDTH, HEIGHT, "Sprite Movement Demo", true);
    if (!game.mlx) {
        printf("Error initializing MLX\n");
        return 1;
    }

    // Create background grid
    game.background = create_grid_background(game.mlx, WIDTH, HEIGHT);
    if (!game.background) {
        printf("Error creating background\n");
        mlx_terminate(game.mlx);
        return 1;
    }

    // Create player sprite (blue square)
    game.player_sprite = create_colored_sprite(game.mlx, 0x0000FFFF, SPRITE_SIZE);
    if (!game.player_sprite) {
        printf("Error creating player sprite\n");
        mlx_terminate(game.mlx);
        return 1;
    }

    // Add background to window
    mlx_image_to_window(game.mlx, game.background, 0, 0);

    // Add player sprite instance to window
    game.player_x = WIDTH / 2 - SPRITE_SIZE / 2;
    game.player_y = HEIGHT / 2 - SPRITE_SIZE / 2;
    game.player_instance = mlx_image_to_window(game.mlx, game.player_sprite,
                                              game.player_x, game.player_y);

    // Set up key handler
    mlx_key_hook(game.mlx, key_handler, &game);

    // Optional: set up loop for smooth animations
    // mlx_loop_hook(game.mlx, smooth_movement_loop, &game);

    printf("Use WASD or arrow keys to move the blue square!\n");
    printf("Press ESC to exit\n");

    // Start the main loop
    mlx_loop(game.mlx);

    // Cleanup
    mlx_terminate(game.mlx);
    return 0;
}
