// main

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
#include "entities.h"
#include "stage.h"
#include "background.h"


// game loop

void loadGame(){
	loadBackground();
	loadEntities();
	loadChrome();
	loadStage();
}

void updateGame(){
	updateBackground();
	updateEntities();
	updateChrome();
	updateStage();
	clock++;
	if(clock >= CLOCK_LIMIT) clock = 0;
}


// resources

void loadResources(){
	VDP_loadFont(font.tileset, DMA);
	VDP_setPalette(PAL1, least.palette -> data);
	VDP_setTextPalette(1);
	VDP_loadTileSet(least.tileset, LEAST_TILE, DMA);
	VDP_loadTileSet(half.tileset, HALF_TILE, DMA);
	VDP_loadTileSet(most.tileset, MOST_TILE, DMA);
	VDP_loadTileSet(full.tileset, FULL_TILE, DMA);
}

void EMPTY(s16 i){}


// main loop

int main(){
	VDP_setScreenWidth256();
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	loadGame();
	while(1){
		updateGame();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return(0);
}
