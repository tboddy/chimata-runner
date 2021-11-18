// chrome

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "chrome.h"
#include "player.h"
// #include "bullet.h"
#include "stage.h"


// load

void loadFrame(){
	for(s16 x = 0; x < WIN_W / 8; x++){
		for(s16 y = 0; y < WIN_H / 8; y++){
			if(x >= 22){
				frameI = FRAME_I + 2;
				if(x == 22) frameI = FRAME_I + 3;
				// if(y == 15) frameI = FRAME_I + 2;
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, 1, 0, 0, frameI), x, y);
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL2, 0, 0, 0, frameI), x, y);
			}
		}
	}
}

void loadScore(){
	highScore = 69420;
	intToStr(highScore, highScoreStr, 8);
	VDP_drawText("high", HUD_X, 2);
	VDP_drawText(highScoreStr, HUD_X, 3);
	VDP_drawText("score", HUD_X, 5);
	VDP_drawText("00000000", HUD_X, 6);
}

void loadHud(){
	VDP_drawText("bomb", HUD_X, 13);
	VDP_drawText("$$$", HUD_X, 14);
	VDP_drawText("player", HUD_X, 16);
	VDP_drawText("###", HUD_X, 17);
	VDP_drawText("V0.01", HUD_X + 3, 26);
}


// update

void updateBoss(){
	if(bossHealth > 0){
		if(lastBoss != bossHealth){
			if(!bossActive){
				bossActive = TRUE;
				VDP_drawText("boss", HUD_X, 9);
			}
			bossLimit = fix16ToRoundedInt(fix16Div(fix16Mul(fix16Div(FIX16(bossHealth), FIX16(bossMax)), BOSS_TILE_PX), BOSS_TILE_WIDTH));
			for(s16 x = 0; x < BOSS_TILE_WIDTH; x++){
				if(x < bossLimit) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, BOSS_I), HUD_X + x, 10);
				else VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FRAME_I + 2), HUD_X + x, 10);
			}
			lastBoss = bossHealth;
		}
	} else if(bossActive){
		bossActive = FALSE;
		lastBoss = 0;
	}
}

void updateScore(){
	if(currentScore > lastScore){
		lastScore = currentScore;
	}
}

void updateHud(){

}


// loop

void loadChrome(){
	VDP_loadTileSet(frame1.tileset, FRAME_I, DMA);
	VDP_loadTileSet(frame2.tileset, FRAME_I + 1, DMA);
	VDP_loadTileSet(frame3.tileset, FRAME_I + 2, DMA);
	VDP_loadTileSet(frame4.tileset, FRAME_I + 3, DMA);
	VDP_loadTileSet(bossBar.tileset, BOSS_I, DMA);
	loadFrame();
	loadScore();
	loadHud();
}

void updateChrome(){
	updateBoss();
	updateScore();
	updateHud();
	// intToStr(bossDiff, debugStr1, 4);
	// VDP_clearText(HUD_X, 0, 8);
	// VDP_drawText(debugStr1, HUD_X, 0);
}