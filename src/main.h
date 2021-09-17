// main

void EMPTY(s16);

#define GAME_W 256
#define GAME_H 224

#define CLOCK_LIMIT 7200

s16 clock;


// game loop

void loadGame(),
	updateGame();


// helpers

#define S_ATTR TILE_ATTR(PAL1, 0, FALSE, FALSE)

// resources

#define LEAST_TILE 2
#define HALF_TILE LEAST_TILE + 1
#define MOST_TILE HALF_TILE + 1
#define FULL_TILE MOST_TILE + 1

void loadResources();


// main loop

int main();