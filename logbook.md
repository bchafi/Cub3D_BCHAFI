### DAY 1

I went to look for some infor about raycasting , howevr i ended up reading about raytracing, from what i understood in practice it is something about projecting the light from a light source to the eye, it depends on a lot of factors like the texturing of the object , but in general it is related to light reaching the eye, in computer words it is applied in reverse (reverse tracing) by starting the ray of light from the eye/camera towards the object and then looking for the light source.
i also looked at how can i draw a rectangle and how are colors used with mlx42, and started playing with some hooks for closing the program, i know that they're not ready but for a basis they are good enough for now.
from what i heard from elkess , i should start by making a 2d map then draw it , the map would be  containing symbols that would express objects such as the player , the walls , the empty space where the player can move , doors .etc. the map would need the tiles to be multiplied by a size that can allow it to appear in the window. and then i'm supposed to map the player's location.

### DAY 2

Today i managed to finish making the map , created on the stack , instead of the heap for now, all the elemens are color coded , i also added a small timer for fun , i managed to make hooks work to a certain extent, i added some files and hooks , i still need to work on textures and images a bit more.

##### DAY 3

i didn't do much work but i manaed to show a texture on the window, that's all.

### DAY 4

Today i trid t pass the exam , but i found it t be too difficult, so i quit.

i managed to change the string color using thepixels param inside of the image struct, i also added the ability to move a player  with a bit of collision, i also changde hw the map is drawn , nstead of drawing it once i now use mlx_loop_hook to draw and delete the map for every frame , although i think the old approach is better , i will see if this proves to be a problem in the future.
i also added a button that would make the timer appear or disappear . i want to make buttons however i think i will focus on making the raycastng now.

### DAY 5
Today i managed to draw comin from the player's point of view , it used to be under the map  and splatter in older locations , but now it's working almost as intended except that it doesn't stop in the wall adjacent to the ray.

## DAY 6

Today i managed to draw a ray that goes down it staops when it encounters a wall .

## DAY 10

I had to revamp the codebas to allow for better maloc failure detection a i also managed to make the player move freely through the map , i seperated the player and the ray from the map image , and addedsome minor imrovements.

## DAY 11

i tried some stuff in JS,was sick for most of the day.

## DAY 12

Fixed a weird bug in the player's drawing method , sorted some positioning quirks, managed to make instances work some how but still need s more work 
