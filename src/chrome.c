// chrome

#include <genesis.h>

#include "chrome.h"
#include "player.h"
#include "stage.h"


// bar

void loadBar(){
	barIndex = 0;
	VDP_drawText("market force", 2, 2);
	for(s16 x = 0; x < BAR_WIDTH; x++){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, BAR_I + barIndex), BAR_X + x, 2);
		if(x % 2 == 1 || x == 0 || x == BAR_WIDTH - 2) barIndex++;
	}
}


// loop

void loadChrome(){
	VDP_drawText("score 069420", 2, 1);
	VDP_drawText("next zone", 18, 1);
	loadBar();
}

void updateChrome(){
	if(lastWave != waveClock){
		intToStr(waveClock / 60, waveStr, 2);
		VDP_drawText(waveStr, 28, 1);
		lastWave = waveClock;
	}
}