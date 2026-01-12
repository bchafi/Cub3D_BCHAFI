- The Raycasting Engine is the "heart" of your game.
- It is the mathematical machine that tricks the human eye into seeing a 3D world while using only a 2D map of 0s (empty space) and 1s (walls).

The raycaster's job is to take that map and draw it on the screen from the player's perspective.

### 1. The Core Concept: "The Fan of Rays"

Imagine you are standing in a dark room (your 2D map) holding a laser pointer.

* **The Player:** You are a single point `(x, y)` on the grid.
* **The Screen:** Your computer screen is a "window" held in front of you.
* **The Rays:** To see what is in front of you, you fire a laser beam through **every single vertical column of pixels** on your screen.

If your screen is `1080` pixels wide, you cast **1,080 rays**.

### 2. How It Works (The Algorithm)

For every vertical line on your screen (from left to right), the engine does these 4 steps:

1. **Cast a Ray:** It calculates the angle of the ray. If you are looking North, the left-most ray might look North-West, and the right-most ray might look North-East.
2. **Find the Wall:** The ray travels forward until it hits a wall (a `1` in your map).
* *In your code:* This is what `find_horizontal_intersection` and `find_vertical_intersection` do. They check the grid lines to see where the ray stops.


3. **Measure Distance:** It calculates how far that wall is from the player.
4. **Draw the Strip:** This is the magic part.
* If the wall is **close** (distance is small) -> Draw a **long** line (looks big).
* If the wall is **far** (distance is big) -> Draw a **short** line (looks small).

By doing this 1,080 times side-by-side, you create a complete image that looks like 3D walls.

