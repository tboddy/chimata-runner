// chrome

// wave

s16 lastWave;
char waveStr[4];
char debugStr1[8];
char debugStr2[8];
char debugStr3[8];
char highScoreStr[12];
char currentScoreStr[12];


// bar

#define HUD_X 23
#define FRAME_I 32
#define BOSS_I FRAME_I + 5
#define BOSS_TILE_WIDTH 8
#define BOSS_TILE_PX BOSS_TILE_WIDTH * 8

s16 frameI, lastBoss, bossLimit, lastLives, lastBombs;
s32 lastScore;

void loadFrame(),
	loadScore(),
	loadHud();

void updateBoss(),
	updateScore(),
	updateHud();

// loop

void loadChrome(),
	updateChrome();