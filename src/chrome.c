// chrome

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "chrome.h"
#include "player.h"
#include "enemies.h"
// #include "bullet.h"
#include "stage.h"


// load

void loadScore(){
	intToStr(currentScore, currentScoreStr, 8);
	VDP_drawText(currentScoreStr, 1, 1);
}

void loadHud(){
	intToStr(currentWaveNum == 0 ? 1 : currentWaveNum, currentWaveStr, 3);
	VDP_drawText("wave", 23, 1);
	VDP_drawText(currentWaveStr, 28, 1);
	for(s16 i = 0; i < player.lives; i++) VDP_drawText("#", LIVES_X + i, 1);
}

void loadInstructions(s16 offset){
	VDP_drawText(instructionStr, 1 + offset, 2);
}

void loadBossLabel(){
	bossLabelClock = BOSS_LABEL_LIMIT;
	VDP_drawText("BOSS  WAVE", BOSS_LABEL_X, BOSS_LABEL_Y);
}

void clearBossLabel(){
	VDP_clearTileMapRect(BG_A, BOSS_LABEL_X, BOSS_LABEL_Y, 10, 1);
}


// labels

void spawnLabel(fix16 x, fix16 y){
	s16 i = -1;
	for(s16 j = 0; j < LABEL_COUNT; j++) if(!labels[j].active && i == -1) i = j;
	labels[i].active = TRUE;
	labels[i].clock = 0;
	labels[i].x = fix16ToRoundedInt(fix16Div(x, FIX16(8))) - 3;
	labels[i].y = fix16ToRoundedInt(fix16Div(y, FIX16(8)));
	labels[i].w = 5;
	VDP_drawText("+1000", labels[i].x, labels[i].y);
}

void updateLabels(){
	for(s16 i = 0; i < LABEL_COUNT; i++) if(labels[i].active){
		labels[i].clock++;
		if(labels[i].clock >= 90){
			labels[i].active = FALSE;
			VDP_clearText(labels[i].x, labels[i].y, labels[i].w);
		}
	}
}



// update

void updateBoss(){
	if(bossHealth > 0){
		if(lastBoss != bossHealth){
			VDP_drawText("boss", 1, 2);
			bossLimit = fix16ToInt(fix16Mul(fix16Div(FIX16(bossHealth), FIX16(bossMax)), FIX16(BOSS_TILE_PX))) / 8; // percent of 100
			for(s16 x = 0; x < BOSS_TILE_WIDTH; x++){
				if(x < bossLimit) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, BOSS_I), 6 + x, 2);
				else VDP_clearTileMapRect(BG_A, 6 + x, 2, 1, 1);
			}
			lastBoss = bossHealth;
		}
	} else {
		lastBoss = 0;
		bossActive = FALSE;
	}
	if(bossLabelClock > 0){
		bossLabelClock--;
		if(bossLabelClock <= 0) clearBossLabel();
	}
}

void updateScore(){
	if(currentScore > lastScore && enemyCount > 0){
		lastScore = currentScore;
		intToStr(currentScore, currentScoreStr, 8);
		VDP_clearText(1, 1, 8);
		VDP_drawText(currentScoreStr, 1, 1);
	}
}

void updateHud(){
	if(player.lives != lastLives){
		lastLives = player.lives;
		VDP_clearTileMapRect(BG_A, LIVES_X, 1, 12, 1);
		for(s16 i = 0; i < player.lives; i++) VDP_drawText("#", LIVES_X + i, 1);
	}
}


// loop

void loadChrome(){
	VDP_loadTileSet(bossBar.tileset, BOSS_I, DMA);
	loadScore();
	loadHud();
}

void updateChrome(){
	updateBoss();
	updateScore();
	updateLabels();
	updateHud();

	// intToStr(enemyCount, debugStr1, 4);
	// VDP_drawText(debugStr1, 0, 27);
}