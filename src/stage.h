// stage
#define STAGE_COUNT_INT 8

s16 stageInts[STAGE_COUNT_INT];
Vect2D_f16 stageVectors[STAGE_COUNT_INT];

void (*currentWave)();

void waveOne(),
	waveTwo(),
	waveThree(),
	waveFour(),
	waveFive(),
	waveSix(),
	waveSeven(),
	waveEight(),
	waveNine(),
	waveTen();


// wave

#define WAVE_LIMIT 15
#define WAVE_MAX 60 * WAVE_LIMIT


s16 waveClock, stageClock, bossHealth, bossMax;
bool bossActive;
void updateWave();


// loop

void loadStage(),
	updateStage();