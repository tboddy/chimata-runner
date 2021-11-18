// main

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
#include "stage.h"
#include "player.h"
#include "enemies.h"
#include "bullet.h"
#include "background.h"
#include "explosion.h"


// game loop

void loadGame(){
	loadBackground();
	loadPlayer();
	loadChrome();
	loadStage();
}

void updateGame(){
	updateBackground();
	updatePlayer();
	updateBullets();
	updateEnemies();
	updateStage();
	updateExplosions();
	updateChrome();
	clock++;
	if(clock >= CLOCK_LIMIT) clock = 0;
}


// resources

void loadResources(){
	VDP_loadFont(font.tileset, DMA);
	VDP_setPalette(PAL1, least.palette -> data);
	VDP_setPalette(PAL2, ground1.palette -> data);
	// VDP_setPalette(PAL2, floor.palette -> data);
	VDP_setTextPalette(1);
	VDP_loadTileSet(least.tileset, LEAST_TILE, DMA);
	VDP_loadTileSet(half.tileset, HALF_TILE, DMA);
	VDP_loadTileSet(most.tileset, MOST_TILE, DMA);
	VDP_loadTileSet(full.tileset, FULL_TILE, DMA);
}


// helpers

void EMPTY(s16 i){}

Vect2D_f16 hone(Vect2D_f16 pos, Vect2D_f16 target, fix16 speed, s16 lerp){
	hPos.x = target.x;
	hPos.y = target.y;
	if(lerp > 0){
		hPos.x = fix16Add(fix16Sub(hPos.x, FIX16(lerp)), FIX16(random() % (lerp * 2)));
		hPos.y = fix16Add(fix16Sub(hPos.y, FIX16(lerp)), FIX16(random() % (lerp * 2)));
	}
	honeSpeed = fix32ToFix16(getApproximatedDistance(
		fix32Sub(fix16ToFix32(pos.x), fix16ToFix32(hPos.x)),
		fix32Sub(fix16ToFix32(pos.y), fix16ToFix32(hPos.y))));
	hPos.x = fix16Mul(fix16Div(fix16Sub(hPos.x, pos.x), honeSpeed), speed);
	hPos.y = fix16Mul(fix16Div(fix16Sub(hPos.y, pos.y), honeSpeed), speed);
	return hPos;
}


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
