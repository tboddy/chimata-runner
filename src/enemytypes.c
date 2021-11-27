// enemy types

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "bullet.h"
#include "player.h"
#include "chrome.h"
#include "stage.h"
#include "explosion.h"
#include "enemytypes.h"


// types

void spawnGrunt(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.image = &beer,
		.health = 3,
		.anim = random() % 2,
		.angle = random() % 1024,
		.speed = FIX16(0.5)
	};
	spawner.ints[0] = random() % 60;
	void updater(s16 i){
		if(enemies[i].clock % 60 == enemies[i].ints[0]) enemies[i].vel = hone(enemies[i].pos, player.pos, enemies[i].speed, 8);

		if(enemies[i].health <= 2 && !enemies[i].bools[0]){
			SPR_setFrame(enemies[i].image, 1);
			enemies[i].bools[0] = TRUE;
		} else if(enemies[i].health <= 1 && !enemies[i].bools[1]){
			SPR_setFrame(enemies[i].image, 2);
			enemies[i].bools[1] = TRUE;
		}

	};
	void suicide(s16 i){
		currentScore += 750;
		enemyCount--;
	}
	spawnEnemy(spawner, updater, suicide);
	enemyCount++;
}

void spawnHulk(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.image = &pickle,
		.hulk = TRUE,
		.angle = random() % 4 * 256,
		.speed = FIX16(0.25)
	};
	spawner.ints[0] = random() % 60;
	void updater(s16 i){
		if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.x < enemies[i].off.x ||
			enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y) || enemies[i].pos.x > fix16Sub(FIX16(GAME_W), enemies[i].off.x)){
			enemies[i].angle += 512;
			updateEnemyVel(i);
		}
		if(enemies[i].clock % 60 == enemies[i].ints[0]){
			enemies[i].angle += random() % 2 < 1 ? -256 : 256;
			if(enemies[i].angle > 1024) enemies[i].angle -= 1024;
			else if(enemies[i].angle < -1024) enemies[i].angle += 1024;
			updateEnemyVel(i);
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.speed = FIX16(2),
				.angle = random() % 1024,
				.image = &smallYellowBullet
			};
			if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
			for(s16 j = 0; j < 3; j++){
				spawnBullet(spawner, EMPTY);
				spawner.angle += 341;
			}
		}
	}
	spawnEnemy(spawner, updater, EMPTY);
}

void spawnElectrode(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.health = 15,
		.electrode = TRUE,
		.image = &lantern,
		.frame = random() % 4
	};
	spawner.ints[0] = random() % 60;
	spawner.ints[1] = 0;
	void updater(s16 i){
		if(enemies[i].health <= 10 && !enemies[i].bools[0]){
			SPR_setAnim(enemies[i].image, 1);
			enemies[i].bools[0] = TRUE;
		} else if(enemies[i].health <= 5 && !enemies[i].bools[1]){
			SPR_setAnim(enemies[i].image, 2);
			enemies[i].bools[1] = TRUE;
		}
	}
	spawnEnemy(spawner, updater, EMPTY);
}

void spawnEnforcer(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.image = &wine,
		.health = 6,
		.anim = random() % 2,
		.angle = random() % 4 * 256,
		.speed = FIX16(0.5)
	};
	spawner.ints[0] = random() % 60;
	void updater(s16 i){
		if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.x < enemies[i].off.x ||
			enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y) || enemies[i].pos.x > fix16Sub(FIX16(GAME_W), enemies[i].off.x)){
			enemies[i].angle += 512;
			updateEnemyVel(i);
		}
		if(enemies[i].clock % 60 == enemies[i].ints[0]){
			enemies[i].angle += random() % 2 < 1 ? -256 : 256;
			if(enemies[i].angle > 1024) enemies[i].angle -= 1024;
			else if(enemies[i].angle < -1024) enemies[i].angle += 1024;
			updateEnemyVel(i);
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.speed = FIX16(2),
				.image = &bigGreenBullet,
				.big = TRUE
			};
			if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
			for(s16 j = 0; j < 2; j++){
				if(j > 0) spawner.image = &smallGreenBullet;
				spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, j == 0 ? 16 : 64);
				spawnBullet(spawner, EMPTY);
			}
		}
		if(enemies[i].health <= 4 && !enemies[i].bools[0]){
			SPR_setFrame(enemies[i].image, 1);
			enemies[i].bools[0] = TRUE;
		} else if(enemies[i].health <= 2 && !enemies[i].bools[1]){
			SPR_setFrame(enemies[i].image, 2);
			enemies[i].bools[1] = TRUE;
		}
	}
	void suicide(s16 i){
		currentScore += 2000;
		enemyCount--;
	}
	spawnEnemy(spawner, updater, suicide);
	enemyCount++;
}

void spawnTank(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.image = &martini,
		.health = 6,
		.anim = random() % 2,
		.angle = random() % 4 * 256,
		.speed = FIX16(0.25),
		.angle = random() % 1024
	};
	spawner.ints[0] = 30 + random() % 90;
	void updater(s16 i){
		if(enemies[i].clock % 120 == enemies[i].ints[0]){
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.speed = FIX16(2),
				.image = &smallRedBullet,
				.angle = random() % 256
			};
			if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
			void updater(s16 j){
				if(!bullets[j].bools[0] && (bullets[j].pos.x <= bullets[j].off.x ||
					bullets[j].pos.x >= fix16Sub(FIX16(GAME_W), bullets[j].off.x) ||
					bullets[j].pos.y <= bullets[j].off.y ||
					bullets[j].pos.y >= fix16Sub(FIX16(GAME_H), bullets[j].off.y))){
					bullets[j].angle = 512 - bullets[j].angle;
					if(bullets[j].pos.y < bullets[j].off.y || bullets[j].pos.y > fix16Sub(FIX16(GAME_H), bullets[j].off.y)) bullets[j].angle -= 512;
					updateBulletVel(j);
					bullets[j].bools[0] = TRUE;
				}
			}
			for(s16 j = 0; j < 5; j++){
				spawnBullet(spawner, updater);
				spawner.angle += 205;
			}
		}


		if(enemies[i].health <= 4 && !enemies[i].bools[0]){
			SPR_setFrame(enemies[i].image, 1);
			enemies[i].bools[0] = TRUE;
		} else if(enemies[i].health <= 2 && !enemies[i].bools[1]){
			SPR_setFrame(enemies[i].image, 2);
			enemies[i].bools[1] = TRUE;
		}
		if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.x < enemies[i].off.x ||
			enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y) || enemies[i].pos.x > fix16Sub(FIX16(GAME_W), enemies[i].off.x)){
			enemies[i].angle = 512 - enemies[i].angle;
			if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y)) enemies[i].angle -= 512;
			updateEnemyVel(i);
		}
		if(enemies[i].clock % 60 == 0){
			enemies[i].angle += -32 + random() % 64;
			updateEnemyVel(i);
		}
	}
	void suicide(s16 i){
		currentScore += 5000;
		enemyCount--;
	}
	spawnEnemy(spawner, updater, suicide);
	enemyCount++;
}

void spawnSushi(){
	struct enemySpawner spawner = {
		.offX = 8,
		.offY = 8,
		.drink = TRUE,
		.angle = random() % 1024,
		.speed = FIX16(0.5)
	};
	spawner.frame = random() % 2;
	spawner.image = &sushi1;
	switch(random() % 3){
		case 0: spawner.image = &sushi1; break;
		case 1: spawner.image = &sushi2; break;
		case 2: spawner.image = &sushi3; break;
	}
	void updater(s16 i){
		if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.x < enemies[i].off.x ||
			enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y) || enemies[i].pos.x > fix16Sub(FIX16(GAME_W), enemies[i].off.x)){
			enemies[i].angle = 512 - enemies[i].angle;
			if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y)) enemies[i].angle -= 512;
			updateEnemyVel(i);
		}
		if(enemies[i].clock % 60 == 0){
			enemies[i].angle += -32 + random() % 64;
			updateEnemyVel(i);
		}
	}
	spawnEnemy(spawner, updater, EMPTY);
}

void spawnSake(){
	struct enemySpawner spawner = {
		.offX = 32,
		.offY = 32,
		.image = &sake,
		.health = 100,
		.angle = 256,
		.speed = FIX16(2),
		.boss = TRUE
	};
	spawner.ints[8] = 64 + random() % 384;
	switch(random() % 4){
		case 0:
			spawner.x = GAME_W / 2;
			spawner.y = -spawner.offY;
			spawner.angle = 256;
			break;
		case 1:
			spawner.x = GAME_W + spawner.offX;
			spawner.y = GAME_H / 2;
			spawner.angle = 512;
			spawner.ints[8] += 256;
			break;
		case 2:
			spawner.x = GAME_W / 2;
			spawner.y = GAME_H + spawner.offY;
			spawner.angle = 768;
			spawner.ints[8] += 512;
			break;
		case 3:
			spawner.x = -spawner.offX;
			spawner.y = GAME_H / 2;
			spawner.angle = 0;
			spawner.ints[8] += 768;
			break;
	}
	bossMax = spawner.health;
	void updater(s16 i){
		if(enemies[i].bools[0]){

			// shoot
			void patternOne(){  // random triangle small
				if(enemies[i].clock % 5 == 0){
					struct bulletSpawner spawner = {
						.image = enemies[i].clock % 60 < 30 ? &smallRedBullet : &smallBlueBullet,
						.angle = random() % 1024,
						.speed = FIX16(3)
					};
					if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
					enemies[i].fixes[0] = FIX16(40);
					spawner.x = fix16Add(enemies[i].pos.x, fix16Mul(cosFix16(spawner.angle), enemies[i].fixes[0]));
					spawner.y = fix16Add(enemies[i].pos.y, fix16Mul(sinFix16(spawner.angle), enemies[i].fixes[0]));
					spawnExplosion(spawner.x, spawner.y);
					for(s16 j = 0; j < 3; j++){
						spawnBullet(spawner, EMPTY);
						spawner.angle += 341;
					}
				}
			}

			void patternTwo(){ // curvy boys and balls 1:47
				if(enemies[i].clock % 90 == 0){
					struct bulletSpawner spawner = {
						.x = enemies[i].pos.x,
						.y = enemies[i].pos.y,
						.image = &bigBlueBullet,
						.big = TRUE,
						.angle = enemies[i].clock % 240 == 0 ? 0 : 64,
						.speed = FIX16(2.5)
					};
					if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
					void updater(s16 j){
						if(bullets[j].clock > 0 && bullets[j].clock % 20 == 0){
							bullets[j].angle += bullets[j].clock % 40 == 0 ? -256 : 256;
							updateBulletVel(j);
						}
						if(bullets[j].clock > 0 && bullets[j].clock % 15 == 0 && bullets[j].clock <= 60){
							struct bulletSpawner spawner = {
								.x = bullets[j].pos.x,
								.y = bullets[j].pos.y,
								.image = &smallBlueBullet,
								.angle = 0,
								.speed = 0
							};
							void updater(s16 h){
								if(bullets[h].clock == 30)
									bullets[h].vel = hone(bullets[h].pos, player.pos, FIX16(3) + (fastBullets ? FAST_BULLET_MOD : 0), 256);
							}
							spawnBullet(spawner, updater);
						}
					}
					for(s16 j = 0; j < 6; j++){
						spawnBullet(spawner, updater);
						spawner.angle += 171;
					}
				}
				if(enemies[i].clock % 90 == 60){
					struct bulletSpawner spawner = {
						.x = enemies[i].pos.x,
						.y = enemies[i].pos.y,
						.image = &bigRedBullet,
						.big = TRUE,
						.angle = random() % 128,
						.speed = FIX16(3)
					};
					if(fastBullets) spawner.speed = fix16Add(spawner.speed, FAST_BULLET_MOD);
					for(s16 j = 0; j < 11; j++){
						spawnBullet(spawner, EMPTY);
						spawner.angle += 93;
					}
				}
			}

			if(enemies[i].health >= 50) patternOne();
			else patternTwo();


			// movement
			if(enemies[i].pos.y <= enemies[i].off.y || enemies[i].pos.x <= enemies[i].off.x ||
				enemies[i].pos.y >= fix16Sub(FIX16(GAME_H), enemies[i].off.y) || enemies[i].pos.x >= fix16Sub(FIX16(GAME_W), enemies[i].off.x)){
				enemies[i].angle = 512 - enemies[i].angle;
				if(enemies[i].pos.y < enemies[i].off.y || enemies[i].pos.y > fix16Sub(FIX16(GAME_H), enemies[i].off.y)) enemies[i].angle -= 512;
				updateEnemyVel(i);
			} else if(enemies[i].clock % 60 == 0){
				enemies[i].angle += -32 + random() % 64;
				updateEnemyVel(i);
			}

		} else if(enemies[i].clock > 0 && enemies[i].clock % 15 == 0){
			enemies[i].speed = fix16Sub(enemies[i].speed, FIX16(0.5));
			updateEnemyVel(i);
			if(enemies[i].speed <= 0){
				enemies[i].angle = enemies[i].ints[8];
				enemies[i].speed = FIX16(0.5);
				updateEnemyVel(i);
				enemies[i].bools[0] = TRUE;
				enemies[i].clock = -1;
			}
		}
	}
	void suicide(s16 i){
		VDP_clearTileMapRect(BG_A, 1, 2, 4, 1);
		enemyCount--;
		for(s16 x = 0; x < BOSS_TILE_WIDTH; x++) VDP_clearTileMapRect(BG_A, 6 + x, 2, 1, 1);
		for(s16 j = 0; j < BULLET_COUNT; j++) if(bullets[j].active){
			if(j < EXPLOSION_LIMIT / 2) spawnExplosion(bullets[j].pos.x, bullets[j].pos.y);
			killBullet(j);
		}
	}
	spawnEnemy(spawner, updater, suicide);
	enemyCount++;
}





// void updater(s16 i){
		// if(enemies[i].clock % 60 == enemies[i].ints[0]){
		// 	struct bulletSpawner spawner = {
		// 		.x = enemies[i].pos.x,
		// 		.y = enemies[i].pos.y,
		// 		.image = &smallYellowBullet,
		// 		.angle = random() % 1024,
		// 		.speed = FIX16(3)
		// 	};
		// 	for(s16 j = 0; j < 8; j++){
		// 		spawnBullet(spawner, EMPTY);
		// 		spawner.angle += 128;
		// 	}
		// }
	// }