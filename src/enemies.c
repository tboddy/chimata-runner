// enemies

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"


// spawn

void spawnEnemy(struct enemySpawner spawner, void(*updater)){
	s16 i = -1;
	for(s16 j = 0; j < ENEMY_COUNT; j++) if(!enemies[j].active && i == -1) i = j;
	if(i > -1){
		enemies[i].active = TRUE;
		enemies[i].pos.x = FIX16(spawner.x);
		enemies[i].pos.y = FIX16(spawner.y);
		enemies[i].off.x = FIX16(spawner.offX);
		enemies[i].off.y = FIX16(spawner.offY);
		enemies[i].dist = fix16ToFix32(enemies[i].off.x);
		enemies[i].speed = spawner.speed;
		enemies[i].angle = spawner.angle;
		enemies[i].health = spawner.health ? spawner.health : 1;
		if(spawner.vel.x && spawner.vel.y){
			enemies[i].vel.x = spawner.vel.x;
			enemies[i].vel.y = spawner.vel.y;
		} else {
			enemies[i].vel.x = fix16Mul(cosFix16(spawner.angle), spawner.speed);
			enemies[i].vel.y = fix16Mul(sinFix16(spawner.angle), spawner.speed);
		}
		for(s16 j = 0; j < COUNT_INT; j++){
			enemies[i].bools[j] = spawner.bools[j];
			enemies[i].ints[j] = spawner.ints[j];
			enemies[i].fixes[j] = spawner.fixes[j];
		}
		enemies[i].updater = updater;
		enemies[i].clock = 0;
		enemies[i].image = SPR_addSprite(spawner.image,
			fix16ToInt(fix16Sub(enemies[i].pos.x, enemies[i].off.x)),
			fix16ToInt(fix16Sub(enemies[i].pos.y, enemies[i].off.y)),
			TILE_ATTR(PAL1, 0, 0, 0));
		if(spawner.anim) SPR_setAnim(enemies[i].image, spawner.anim);
	}
}


// update

void updateEnemy(s16 i){
	if(enemies[i].pos.x < fix16Sub(0, enemies[i].off.x) ||
		enemies[i].pos.x > fix16Add(FIX16(GAME_W), enemies[i].off.x) ||
		enemies[i].pos.y < fix16Sub(0, enemies[i].off.y) ||
		enemies[i].pos.y > fix16Add(FIX16(GAME_H), enemies[i].off.y)){
		killEnemy(i);
	} else {
		enemies[i].pos.x = fix16Add(enemies[i].pos.x, enemies[i].vel.x);
		enemies[i].pos.y = fix16Add(enemies[i].pos.y, enemies[i].vel.y);
		enemies[i].updater(i);
		enemies[i].clock++;
		SPR_setPosition(enemies[i].image,
			fix16ToInt(fix16Sub(enemies[i].pos.x, enemies[i].off.x)),
			fix16ToInt(fix16Sub(enemies[i].pos.y, enemies[i].off.y)));
	}
}

void updateEnemyVel(s16 i){
	enemies[i].vel.x = fix16Mul(cosFix16(enemies[i].angle), enemies[i].speed);
	enemies[i].vel.y = fix16Mul(sinFix16(enemies[i].angle), enemies[i].speed);
}

void killEnemy(s16 i){
	enemies[i].active = FALSE;
	SPR_releaseSprite(enemies[i].image);
}

void updateEnemies(){
	if(clock % 2 == 1)
		for(s16 i = 0; i < ENEMY_COUNT; i++) if(enemies[i].active) updateEnemy(i);
}