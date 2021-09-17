// enemies

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "entities.h"
#include "stage.h"
#include "enemies.h"


// spawn

void spawnEnemy(s16 i){
	SPR_setHFlip(ent[i].image, random() % 2 < 1 ? 1 : 0);
}


// update

void updateEnemy(s16 i){
	ent[i].clock++;
	if(ent[i].pos.x > fix16Add(FIX16(GAME_W), FIX16(ent[i].offX)) ||
		ent[i].pos.x < fix16Sub(0, FIX16(ent[i].offX)) || ent[i].pos.y < FIX16(-ent[i].offY)) killEntity(i);
}