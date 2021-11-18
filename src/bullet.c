// bullets

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "player.h"
#include "enemies.h"
#include "bullet.h"
#include "explosion.h"


// spawn

void spawnBullet(struct bulletSpawner spawner, void(*updater)){
	s16 i = -1;
	for(s16 j = 0; j < BULLET_COUNT; j++) if(!bullets[j].active && i == -1) i = j;
	if(i > -1){
		bullets[i].active = TRUE;
		bullets[i].pos.x = spawner.x;
		bullets[i].pos.y = spawner.y;
		bullets[i].off.x = FIX16(spawner.big ? 8 : 4);
		bullets[i].off.y = bullets[i].off.x;
		bullets[i].dist = fix16ToFix32(bullets[i].off.x);
		bullets[i].speed = spawner.speed;
		bullets[i].clock = 0;
		bullets[i].angle = spawner.angle;
		bullets[i].player = spawner.player;
		for(s16 j = 0; j < COUNT_INT; j++){
			bullets[i].bools[j] = spawner.bools[j];
			bullets[i].ints[j] = spawner.ints[j];
			bullets[i].fixes[j] = spawner.fixes[j];
		}
		if(spawner.vel.x && spawner.vel.y){
			bullets[i].vel.x = spawner.vel.x;
			bullets[i].vel.y = spawner.vel.y;
		} else {
			bullets[i].vel.x = fix16Mul(cosFix16(spawner.angle), spawner.speed);
			bullets[i].vel.y = fix16Mul(sinFix16(spawner.angle), spawner.speed);
		}
		bullets[i].updater = updater;
		bullets[i].image = SPR_addSprite(spawner.image,
			fix16ToInt(fix16Sub(bullets[i].pos.x, bullets[i].off.x)) + GAME_X,
			fix16ToInt(fix16Sub(bullets[i].pos.y, bullets[i].off.y)) + GAME_Y,
			TILE_ATTR(PAL1, 0, 0, 0));
	}
}


// update

void killBullet(s16 i){
	bullets[i].active = FALSE;
	SPR_releaseSprite(bullets[i].image);
}

void collideBulletWithEnemy(s16 i){
	for(s16 j = 0; j < ENEMY_COUNT; j++) if(enemies[j].active){
		bulletDist = getApproximatedDistance(
			fix16ToFix32(fix16Sub(enemies[j].pos.x, bullets[i].pos.x)),
			fix16ToFix32(fix16Sub(enemies[j].pos.y, bullets[i].pos.y)));
		if(bulletDist <= fix32Add(enemies[j].dist, bullets[i].dist)){
			spawnExplosion(bullets[i].pos.x, bullets[i].pos.y);
			killBullet(i);
			enemies[j].health--;
			if(enemies[j].health <= 0) killEnemy(j);
		}
	}
}

void collideBulletWithPlayer(s16 i){
	bulletDist = getApproximatedDistance(
		fix16ToFix32(fix16Sub(player.pos.x, bullets[i].pos.x)),
		fix16ToFix32(fix16Sub(player.pos.y, bullets[i].pos.y)));
	if(bulletDist <= fix32Add(player.dist, bullets[i].dist)){
		spawnExplosion(player.pos.x, player.pos.y);
		killBullet(i);
		player.invincible = TRUE;
		player.invincibleClock = INVINCIBLE_LIMIT;
		player.health--;
		if(player.health <= 0) player.health = 1;
	}
}

void collideBullet(s16 i){
	if(bullets[i].pos.x < fix16Sub(BULLET_LIMIT_X, bullets[i].off.x) ||
		bullets[i].pos.x > fix16Add(BULLET_LIMIT_W, bullets[i].off.x) ||
		bullets[i].pos.y < fix16Sub(BULLET_LIMIT_Y, bullets[i].off.y) ||
		bullets[i].pos.y > fix16Add(BULLET_LIMIT_Z, bullets[i].off.y)){
		killBullet(i);
	} else if(bullets[i].player) collideBulletWithEnemy(i);
	else if(!player.invincible) collideBulletWithPlayer(i);
}


// loop

void updateBullet(s16 i){
	bulletCount++;
	bullets[i].pos.x = fix16Add(bullets[i].pos.x, bullets[i].vel.x);
	bullets[i].pos.y = fix16Add(bullets[i].pos.y, bullets[i].vel.y);
	bullets[i].updater(i);
	collideBullet(i);
	SPR_setPosition(
		bullets[i].image,
		fix16ToInt(fix16Sub(bullets[i].pos.x, bullets[i].off.x)) + GAME_X,
		fix16ToInt(fix16Sub(bullets[i].pos.y, bullets[i].off.y)) + GAME_Y);
	bullets[i].clock++;
}

void updateBulletVel(s16 i){
	bullets[i].vel.x = fix16Mul(cosFix16(bullets[i].angle), bullets[i].speed);
	bullets[i].vel.y = fix16Mul(sinFix16(bullets[i].angle), bullets[i].speed);
}

void updateBullets(){
	if(clock % 2 == 0){
		bulletCount = 0;
		for(s16 i = 0; i < BULLET_COUNT; i++) if(bullets[i].active) updateBullet(i);
	}
}







	// spawnExplosion(ent[i].pos.x, ent[i].pos.y);






	// if(ent[i].subType == 1){
	// 	for(s16 j = 0; j < ENEMY_COUNT; j++) if(enemyIndexes[j] > -1){
	// 		bulletDist = getApproximatedDistance(
	// 			fix16ToFix32(fix16Sub(ent[enemyIndexes[j]].pos.x, ent[i].pos.x)),
	// 			fix16ToFix32(fix16Sub(ent[enemyIndexes[j]].pos.y, ent[i].pos.y)));
	// 		bulletCheck = FIX32(16);
	// 		if(bulletDist < bulletCheck) killEnemy(enemyIndexes[j]);
	// 	}
	// }