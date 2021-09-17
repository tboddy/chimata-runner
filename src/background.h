// blocks

#define BG_WIDTH 256 * 2 / 8
#define BG_HEIGHT 224 / 8


// tiles

#define TILE_WIDTH 16
#define TILES_I 64
#define BLOCK_BLANK TILES_I
#define ROCK_Y BLOCK_BLANK + 1
#define ROCK_C ROCK_X + 2
#define ROCK_X ROCK_Y + 4


// scrolling

#define FLOOR_Y 26

s16 bgPos[BG_HEIGHT];
s16 fgPos[BG_HEIGHT];
s16 scrollClock;


// load bg

#define CLOUD_I TILES_I + 32
#define CLOUD__BOTTOM_I CLOUD_I + 24
#define CLOUD_TOP_Y 4
#define CLOUD_BOTTOM_Y 11
#define CLOUD_W 12
#define CLOUD_COUNT 4
#define CLOUD_LIMIT 96

#define STARS_I CLOUD__BOTTOM_I + 32
#define STARS_LIMIT 80
#define STARS_COUNT 4
#define STARS_W 10
#define STARS_Y CLOUD_TOP_Y + 2

#define FG_I STARS_I + 32
#define FG_Y 23

#define TREES_I FG_I + 32
#define TREES_Y 15
#define TREES_WIDTH 12
#define TREES_COUNT 4

#define TREES_LIMIT 96
#define FG_LIMIT 96


void loadSky(),
	loadTrees();


// loop

void loadBackground(),
	updateBackground();