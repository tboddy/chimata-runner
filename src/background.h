// bg

#define BG_WIDTH 24
#define BG_WIDTH_2 11
#define BG_HEIGHT 32
#define BG_SIZE -64


// scrolling

s16 bgPos[12];
s16 fgPos[12];
s16 scrollClock;


// load bg

#define BG_I 64
#define FG_I BG_I + 64


// forest
#define FOREST_BG_W_P GAME_W
#define FOREST_BG_W FOREST_BG_W_P / 8
#define FOREST_BG_W_2_P 112
#define FOREST_BG_W_2 FOREST_BG_W_2_P / 8


void loadBg();


// loop

void loadBackground(),
	updateBackground();






// tiles

// #define TILE_WIDTH 16
// #define BLOCK_BLANK TILES_I
// #define ROCK_Y BLOCK_BLANK + 1
// #define ROCK_C ROCK_X + 2
// #define ROCK_X ROCK_Y + 4

// #define SKY_I TILES_I + 32

// #define SKY_Y 2
// #define SKY_W 24
// #define SKY_H 12
// #define SKY_LIMIT 192
// #define SKY_MOD 132

// #define CLOUD_I SKY_I + SKY_MOD * 2
// #define CLOUD_Y SKY_Y + SKY_H - 1
// #define CLOUD_H 3

// #define MOUNTAIN_I CLOUD_I + 1
// #define MOUNTAIN_Y SKY_Y + CLOUD_H
// #define MOUNTAIN_W 20
// #define MOUNTAIN_H 8
// #define MOUNTAIN_LIMIT 160

// #define TREES_I MOUNTAIN_I + 160
// #define TREES_Y 12
// #define TREES_W 24
// #define TREES_OFF 12
// #define TREES_H 11
// #define TREES_LIMIT 192
// #define TREES_MOD 132

// #define FAR_I TREES_I + TREES_MOD * 2
// #define FAR_Y TREES_Y - 1
// #define FAR_W 20
// #define FAR_H 8
// #define FAR_LIMIT 160

// #define PLANT_I FAR_I + 160
// #define PLANT_Y 26
// #define PLANT_LIMIT 256

// #define FLOOR_I PLANT_I + 8 + 8