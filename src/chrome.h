// chrome

// wave

s16 lastWave;
char waveStr[4];
char debugStr1[8];
char debugStr2[8];
char debugStr3[8];
char highScoreStr[12];
char currentScoreStr[12];
char currentWaveStr[8];

char instructionStr[16];


// label

#define LABEL_COUNT 8

struct label {
	bool active;
	s16 clock, x, y, w;
};
struct label labels[LABEL_COUNT];

void spawnLabel(fix16, fix16),
	updateLabels();



#define LIVES_X 10

#define FRAME_I 32
#define BOSS_I FRAME_I + 5
#define BOSS_TILE_WIDTH 25
#define BOSS_TILE_PX BOSS_TILE_WIDTH * 8

#define BOSS_LABEL_LIMIT 60 * 2.5
#define BOSS_LABEL_X 11
#define BOSS_LABEL_Y 14

s16 frameI, lastBoss, bossLimit, lastLives, bossLabelClock;
s32 lastScore;

void loadFrame(),
	loadScore(),
	loadHud(),
	loadInstructions(s16),
	loadBossLabel(),
	clearBossLabel();


void updateBoss(),
	updateScore(),
	updateHud();

// loop

void loadChrome(),
	updateChrome();