// bullets

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "entities.h"
#include "bullet.h"
#include "explosion.h"


// spawn

void spawnBullet(s16 i){}

void bUpdater(s16 i){
	EMPTY(i);
}


void killBullet(s16 i){
	spawnExplosion(ent[i].pos.x, ent[i].pos.y);
	killEntity(i);
}


// loop

void updateBullet(s16 i){
	collideEntity(i);
	// bulletCollided = FALSE;
	ent[i].clock++;
	// for(s16 j = 0; j < COLLIDER_INT; j++) if(ent[i].colliders[j]) bulletCollided = TRUE;
	// if(bulletCollided) killBullet(i);
	if(ent[i].pos.y >= BULLET_LIMIT) killBullet(i);
	else if(ent[i].pos.x <= fix16Sub(0, ent[i].offX) || ent[i].pos.x >= fix16Add(FIX16(GAME_W), ent[i].offX) ||
		ent[i].pos.y <= fix16Sub(0, ent[i].offY)) killEntity(i);
}