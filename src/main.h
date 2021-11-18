// main

void EMPTY(s16);

#define WIN_W 256
#define WIN_H 224

#define GAME_W 176
#define GAME_H 224

#define GAME_X 0
#define GAME_Y 0

#define CLOCK_LIMIT 7200

s16 clock;
s32 currentScore, highScore;


// game loop

void loadGame(),
	updateGame();


// helpers

#define S_ATTR TILE_ATTR(PAL1, 0, 0, 0)

fix16 honeSpeed;
Vect2D_f16 hPos;
Vect2D_f16 hone(Vect2D_f16, Vect2D_f16, fix16, s16);

// resources

#define LEAST_TILE 2
#define HALF_TILE LEAST_TILE + 1
#define MOST_TILE HALF_TILE + 1
#define FULL_TILE MOST_TILE + 1

void loadResources();


// main loop

int main();