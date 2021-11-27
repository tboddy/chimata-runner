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
	started = TRUE;
	loadBackground();
	loadPlayer();
	loadEnemies();
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
	XGM_setPCM(SFX_MENU_SELECT, sfxMenuSelect, sizeof(sfxMenuSelect)); // shit
	XGM_setPCM(SFX_MENU_CHOOSE, sfxMenuChoose, sizeof(sfxMenuChoose));
	XGM_setPCM(SFX_START_GAME, sfxStartGame, sizeof(sfxStartGame));
	XGM_setPCM(SFX_PLAYER_SHOT, sfxPlayerShot, sizeof(sfxPlayerShot));
	XGM_setPCM(SFX_ZONE_OVER, sfxZoneOver, sizeof(sfxZoneOver));
	XGM_setPCM(SFX_BULLET_1, sfxBullet1, sizeof(sfxBullet1));
	XGM_setPCM(SFX_EXPLOSION_1, sfxExplosion1, sizeof(sfxExplosion1));
	XGM_setPCM(SFX_EXPLOSION_2, sfxExplosion2, sizeof(sfxExplosion2));
	XGM_setPCM(SFX_EXPLOSION_3, sfxExplosion3, sizeof(sfxExplosion3));
	XGM_setPCM(SFX_GAME_OVER, sfxGameOver, sizeof(sfxGameOver));
	XGM_setPCM(SFX_BEAT_GAME, sfxBeatGame, sizeof(sfxBeatGame));
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
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	// loadGame();
	loadStart();
	while(1){
		started ? updateGame() : updateStart();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return(0);
}
