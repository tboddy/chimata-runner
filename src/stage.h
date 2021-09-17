// stage
#define STAGE_COUNT_INT 8

s16 stageInts[STAGE_COUNT_INT];
Vect2D_f16 stageVectors[STAGE_COUNT_INT];

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

#define WAVE_START 60 * 45

s16 waveClock, stageClock;
void updateWave();


// loop

void loadStage(),
	updateStage();