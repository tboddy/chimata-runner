// stage

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "bullet.h"
#include "player.h"
#include "stage.h"
// #include "powerups.h"

void waveOne(){
	void spawnEnemies(bool opposite){
		struct enemySpawner spawner = {
			.y = -8,
			.offX = 8,
			.offY = 8,
			.image = &bakebake,
			.health = 2
		};
		spawner.x = opposite ? GAME_W / 5 * 2 : GAME_W / 5 * 3;
		spawner.fixes[0] = FIX16(spawner.x);
		spawner.fixes[1] = FIX16(1);
		spawner.fixes[2] = FIX16(GAME_H / 2 - 64);
		spawner.fixes[3] = FIX16(2);
		spawner.ints[0] = 0;
		spawner.ints[1] = opposite ? -12 : 12;
		void updater(s16 i){
			enemies[i].pos.x = fix16Add(enemies[i].fixes[0], fix16Mul(sinFix16(enemies[i].ints[0]), enemies[i].fixes[2]));
			enemies[i].ints[0] += enemies[i].ints[1];
			enemies[i].pos.y = fix16Add(enemies[i].pos.y, enemies[i].fixes[1]);
			if(enemies[i].clock < 120 && enemies[i].clock > 0 && enemies[i].clock % 30 == 0) {
				struct bulletSpawner spawner = {
					.x = enemies[i].pos.x,
					.y = enemies[i].pos.y,
					.image = &smallRedBullet,
					.speed = FIX16(4)
				};
				spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, 4);
				spawnBullet(spawner, EMPTY);
			}
		}
		spawnEnemy(spawner, updater);
	}
	if(waveClock % 30 == 0 && (waveClock <= 30 * 5 || (waveClock >= 30 * 10 && waveClock <= 30 * 15))) spawnEnemies(waveClock >= 30 * 10);
	else if(waveClock == 30 * 20){
		waveClock = -1;
		currentWave = &waveTwo;
	}
}

void waveTwo(){
	void spawnEnemies(s16 offset){
		for(s16 i = 0; i < 2; i++){
			struct enemySpawner spawner = {
				.x = i == 0 ? -8 : GAME_W + 8,
				.y = 32 + offset * 32,
				.offX = 8,
				.offY = 8,
				.image = &bakebake,
				.speed = FIX16(3),
				.angle = i == 0 ? 0 : 512,
				.health = 1
			};
			if(i > 0) spawner.y += 16;
			spawner.fixes[0] = FIX16(0.2);
			void updater(s16 i){
				if(enemies[i].clock % 5 == 0 && enemies[i].speed > FIX16(1.25) && enemies[i].clock > 0){
					enemies[i].speed = fix16Sub(enemies[i].speed, enemies[i].fixes[0]);
					updateEnemyVel(i);
				}
			}
			spawnEnemy(spawner, updater);
		}
	}
	if(waveClock % 45 == 0 && waveClock < 45 * 10) spawnEnemies((waveClock % (45 * 5)) / 45);
	else if(waveClock == 45 * 11){
		waveClock = -1;
		currentWave = &waveThree;
	}
}

void waveThree(){
	void spawnEnemies(){
		struct enemySpawner spawner = {
			.y = -8,
			.x = GAME_H	/ 6 + random() % (GAME_H / 3 * 2),
			.offX = 8,
			.offY = 8,
			.image = &bakebake,
			.health = 2,
			.speed = FIX16(2)
		};
		velPos.x = FIX16(spawner.x);
		velPos.y = FIX16(spawner.y);
		spawner.vel = hone(velPos, player.pos, spawner.speed, 2);
		spawnEnemy(spawner, EMPTY);
	}
	if(waveClock % 20 == 0 && waveClock < 20 * 15) spawnEnemies();
	else if(waveClock == 20 * 18){
		waveClock = -1;
		currentWave = &waveFour;
	}
}

void waveFour(){ // 0:20
	void spawnEnemies(bool opposite, s16 offset){
		struct enemySpawner spawner = {
			.x = GAME_W / 4,
			.y = -8,
			.offX = 8,
			.offY = 8,
			.image = &bakebake,
			.health = 2,
			.speed = FIX16(2.75),
			.angle = 256
		};
		spawner.ints[0] = 128;
		if(opposite){
			spawner.x = GAME_W / 4 * 3;
			spawner.ints[0] *= -1;
		}
		spawner.fixes[0] = FIX16(0.25);
		spawner.ints[1] = offset * 158;
		void updater(s16 i){
			if(enemies[i].clock > 30 && enemies[i].clock % 12 == 0 && enemies[i].angle > -256 && enemies[i].angle < 768){
				enemies[i].angle -= enemies[i].ints[0];
				enemies[i].speed = fix16Sub(enemies[i].speed, enemies[i].fixes[0]);
				updateEnemyVel(i);
			} else if(enemies[i].clock == 20){
				struct bulletSpawner spawner = {
					.x = enemies[i].pos.x,
					.y = enemies[i].pos.y,
					.image = &smallRedBullet,
					.speed = FIX16(5),
					.angle = enemies[i].ints[1]
				};
				void updater(s16 j){
					if(bullets[j].clock % 10 == 0 && bullets[j].clock < 30 && bullets[j].clock > 0){
						bullets[j].speed = fix16Sub(bullets[j].speed, FIX16(1));
						updateBulletVel(j);
					}
				}
				for(s16 j = 0; j < 8; j++){
					spawnBullet(spawner, updater);
					spawner.angle += 128;
				}
			}
		}
		spawnEnemy(spawner, updater);
	}
	if(waveClock % 30 == 0 && (waveClock < 30 * 5 || (waveClock > 30 * 5 && waveClock < 30 * 10))) spawnEnemies(waveClock > 30 * 5, waveClock / 30);
}

void waveFive(){
	void spawnEnemies(bool opposite, s16 offset){
		struct enemySpawner spawner = {
			.x = GAME_W / 4,
			.y = -8,
			.offX = 8,
			.offY = 8,
			.image = &bakebake,
			.health = 2,
			.speed = FIX16(2.75),
			.angle = 256
		};
		spawner.ints[0] = 128;
		if(opposite){
			spawner.x = GAME_W / 4 * 3;
			spawner.ints[0] *= -1;
		}
		spawner.fixes[0] = FIX16(0.25);
		spawner.ints[1] = offset * 158;
		void updater(s16 i){
			if(enemies[i].clock > 30 && enemies[i].clock % 12 == 0 && enemies[i].angle > -256 && enemies[i].angle < 768){
				enemies[i].angle -= enemies[i].ints[0];
				enemies[i].speed = fix16Sub(enemies[i].speed, enemies[i].fixes[0]);
				updateEnemyVel(i);
			} else if(enemies[i].clock == 20){
				struct bulletSpawner spawner = {
					.x = enemies[i].pos.x,
					.y = enemies[i].pos.y,
					.speed = FIX16(3)
				};
				for(s16 j = 0; j < 3; j++){
					spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, 48);
					spawner.big = j % 2 == 0;
					spawner.image = spawner.big ? &bigRedBullet : &smallRedBullet;
					spawner.speed = fix16Add(spawner.speed, FIX16(0.25));
					spawnBullet(spawner, EMPTY);
				}
			}
		}
		spawnEnemy(spawner, updater);
	}
	if(waveClock % 30 == 0 && (waveClock < 30 * 5 || (waveClock > 30 * 5 && waveClock < 30 * 10))) spawnEnemies(waveClock > 30 * 5, waveClock / 30);
}

void waveSix(){ // 0:30
	void spawnEnemies(bool opposite){
		struct enemySpawner spawner = {
			.x = GAME_W - 32,
			.y = opposite ? -12 : GAME_H + 12,
			.offX = 8,
			.offY = 8,
			.image = &bakebake,
			.speed = FIX16(3),
			.angle = opposite ? 256 : 768,
			.health = 2
		};
		spawner.fixes[0] = FIX16(0.2);
		void updater(s16 i){
			if(enemies[i].clock % 5 == 0 && enemies[i].speed > FIX16(1.5) && enemies[i].clock > 0){
				enemies[i].speed = fix16Sub(enemies[i].speed, enemies[i].fixes[0]);
				updateEnemyVel(i);
			}
		}
		spawnEnemy(spawner, updater);
	}
	if(waveClock % 20 == 0 && waveClock < 20 * 5) spawnEnemies(TRUE);
}

void bossOne(){ // 1:30

	void patternOne(s16 i){ // random homing small
		if(enemies[i].clock % 10 == 0){
			struct bulletSpawner spawner = {
				.image = &smallRedBullet,
				.angle = 256,
				.speed = FIX16(4)
			};
			enemies[i].ints[0] = random() % 1024;
			enemies[i].fixes[0] = FIX16(32);
			spawner.x = fix16Add(enemies[i].pos.x, fix16Mul(cosFix16(enemies[i].ints[0]), enemies[i].fixes[0]));
			spawner.y = fix16Add(enemies[i].pos.y, fix16Mul(sinFix16(enemies[i].ints[0]), enemies[i].fixes[0]));
			spawner.hPos.x = spawner.x;
			spawner.hPos.y = spawner.y;
			spawner.vel = hone(spawner.hPos, player.pos, spawner.speed, 16);
			spawnExplosion(spawner.x, spawner.y);
			spawnBullet(spawner, EMPTY);
		}
	}

	void patternTwo(s16 i){ // random triangle small
		if(enemies[i].clock % 5 == 0){
			struct bulletSpawner spawner = {
				.image = enemies[i].clock % 60 < 30 ? &smallRedBullet : &smallBlueBullet,
				.angle = random() % 1024,
				.speed = FIX16(4)
			};
			enemies[i].fixes[0] = FIX16(32);
			spawner.x = fix16Add(enemies[i].pos.x, fix16Mul(cosFix16(spawner.angle), enemies[i].fixes[0]));
			spawner.y = fix16Add(enemies[i].pos.y, fix16Mul(sinFix16(spawner.angle), enemies[i].fixes[0]));
			spawnExplosion(spawner.x, spawner.y);
			for(s16 j = 0; j < 3; j++){
				spawnBullet(spawner, EMPTY);
				spawner.angle += 341;
			}
		}
	}

	void patternThree(s16 i){ // curvy boys and balls 1:47
		if(enemies[i].clock % 90 == 0){
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.image = &bigBlueBullet,
				.big = TRUE,
				.angle = enemies[i].clock % 240 == 0 ? 0 : 64,
				.speed = FIX16(3)
			};
			void updater(s16 j){
				if(bullets[j].clock > 0 && bullets[j].clock % 20 == 0){
					bullets[j].angle += bullets[j].clock % 40 == 0 ? -256 : 256;
					updateBulletVel(j);
				}
				if(bullets[j].clock > 0 && bullets[j].clock % 10 == 0 && bullets[j].clock <= 60){
					struct bulletSpawner spawner = {
						.x = bullets[j].pos.x,
						.y = bullets[j].pos.y,
						.image = &smallBlueBullet,
						.angle = 0,
						.speed = 0
					};
					void updater(s16 h){
						if(bullets[h].clock == 30){
							bullets[h].angle = random() % 256 + 128;
							bullets[h].speed = FIX16(4);
							updateBulletVel(h);
						}
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
			for(s16 j = 0; j < 11; j++){
				spawnBullet(spawner, EMPTY);
				spawner.angle += 93;
			}
		}
	}

	void patternFour(s16 i){ // knives 2:03
		if(enemies[i].clock % 60 < 15 && enemies[i].clock % 5 == 0){
			if(enemies[i].clock % 60 == 0) enemies[i].ints[0] = random() % 1024;
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.angle = enemies[i].ints[0],
				.speed = FIX16(3)
			};
			spawner.bools[0] = enemies[i].clock % 120 < 60;
			enemies[i].ints[0] += spawner.bools[0] ? -40 : 40;
			spawner.image = spawner.bools[0] ? &smallBlueBullet : &smallRedBullet;
			spawner.ints[0] = spawner.bools[0] ? 56 : -56;
			void updater(s16 j){
				if(bullets[j].clock % 5 == 0 && bullets[j].clock > 0 && bullets[j].clock < 20){
					bullets[j].speed = fix16Sub(bullets[j].speed, FIX16(1));
					updateBulletVel(j);
				} else if(bullets[j].clock >= 30 && bullets[j].clock % 15 == 0){
					bullets[j].speed = FIX16(4);
					bullets[j].angle += bullets[j].ints[0];
					updateBulletVel(j);
				}
			}
			for(s16 j = 0; j < 8; j++){
				spawnBullet(spawner, updater);
				spawner.angle += 128;
			}
		}
	}

	void patternFive(s16 i){ //balls 2:08
		if(enemies[i].clock % 60 < 30){
			if(enemies[i].clock % 60 == 0) enemies[i].ints[0] = random() % 1024;
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.angle = enemies[i].ints[0],
				.speed = FIX16(2.5),
				.big = TRUE
			};
			spawner.bools[0] = enemies[i].clock % 120 < 60;
			spawner.fixes[0] = FIX16(1.25);
			spawner.ints[0] = spawner.bools[0] ? -195 : 324;
			spawner.image = spawner.bools[0] ? &bigBlueBullet : &bigRedBullet;
			void updater(s16 j){
				if(bullets[j].clock > 0 && bullets[j].clock % 10 == 0){
					bullets[j].speed = fix16Sub(bullets[j].speed, bullets[j].fixes[0]);
					updateBulletVel(j);
				}
			}
			spawnBullet(spawner, updater);
			enemies[i].ints[0] += spawner.ints[0];
		}
	}

	void patternSix(s16 i){ // double balls 2:16

		if(enemies[i].clock % 30 == 0 || enemies[i].clock % 30 == 5){
			struct bulletSpawner spawner = {
				.y = enemies[i].pos.y,
				.angle = random() % 1024,
				.speed = FIX16(3.5),
				.big = TRUE,
				.image = &bigBlueBullet
			};
			spawner.bools[0] = enemies[i].clock % 30 == 0;
			spawner.fixes[0] = FIX16(32);
			spawner.fixes[1] = FIX16(0.25);
			spawner.ints[0] = spawner.bools[0] ? 64 : -64;
			spawner.x = fix16Add(enemies[i].pos.x, (spawner.bools[0] ? spawner.fixes[0] : -spawner.fixes[0]));
			void updater(s16 h){
				if(bullets[h].clock % 15 == 0 && bullets[h].clock > 0){
					bullets[h].angle += bullets[h].ints[0];
					bullets[h].speed = fix16Sub(bullets[h].speed, bullets[h].fixes[1]);
					updateBulletVel(h);
				}
			}
			spawnExplosion(spawner.x, spawner.y);
			for(s16 j = 0; j < 9; j++){
				spawnBullet(spawner, updater);
				spawner.angle += 114;
			}
		}

		else if(enemies[i].clock % 30 >= 10 && enemies[i].clock % 5 == 0){

			if(enemies[i].clock % 120 < 60){
				struct bulletSpawner spawner = {
					.y = enemies[i].pos.y,
					.angle = enemies[i].clock % 60 < 30 ? 224 : 288,
					.speed = FIX16(5),
					.image = &smallRedBullet
				};
				spawner.bools[0] = enemies[i].clock % 10 == 0;
				spawner.ints[0] = spawner.bools[0] ? 128 : -128;
				spawner.fixes[0] = FIX16(32);
				spawner.x = fix16Add(enemies[i].pos.x, (spawner.bools[0] ? spawner.fixes[0] : -spawner.fixes[0]));
				for(s16 h = 0; h < 2; h++){
					spawnBullet(spawner, EMPTY);
					spawner.angle += spawner.ints[0];
				}
				spawnExplosion(spawner.x, spawner.y);
			} else {
				if(enemies[i].clock % 30 == 10){
					enemies[i].ints[1] = 0;
				}
				struct bulletSpawner spawner = {
					.x = enemies[i].pos.x,
					.y = enemies[i].pos.y,
					.angle = enemies[i].ints[1],
					.speed = FIX16(5),
					.image = &smallRedBullet
				};
				enemies[i].ints[1] += enemies[i].clock % 60 > 30 ? 16 : -16;
				for(s16 h = 0; h < 6; h++){
					if(h > 0) spawnBullet(spawner, EMPTY);
					spawner.angle += 85;
				}
			}
		}

	}

	if(waveClock == 0){
		struct enemySpawner spawner = {
			.x = GAME_W / 2,
			.y = 48,
			.offX = 12,
			.offY = 24,
			.image = &mike,
			.speed = 0,
			.angle = 256,
			.health = 350
		};
		bossMax = spawner.health;
		void updater(s16 i){
			bossHealth = enemies[i].health;
			if(bossHealth > bossMax - 25) patternOne(i);
			else if(bossHealth > bossMax - 75) patternTwo(i);
			else if(bossHealth > bossMax - 150) patternThree(i);
			else if(bossHealth > bossMax - 200) patternFour(i);
			else if(bossHealth > bossMax - 275) patternFive(i);
			else patternSix(i);
		}
		spawnEnemy(spawner, updater);
	}
	waveClock = 1;
}

void bossTwo(){

	void patternOne(s16 i){ // balls 4:00
		if(enemies[i].clock % 60 < 50 && enemies[i].clock % 2 == 0){
			if(enemies[i].clock % 60 == 0){
				enemies[i].ints[0] = random() % -32 - 32;
				enemies[i].ints[1] = enemies[i].clock % 120 < 60 ? 32 : -32;
				enemies[i].fixes[0] = FIX16(32);
				if(enemies[i].clock % 120 >= 60) enemies[i].ints[0] += 512;
			}
			struct bulletSpawner spawner = {
				.x = fix16Add(enemies[i].pos.x, fix16Mul(cosFix16(enemies[i].ints[0]), enemies[i].fixes[0])),
				.y = fix16Add(enemies[i].pos.y, fix16Mul(sinFix16(enemies[i].ints[0]), enemies[i].fixes[0])),
				.angle = enemies[i].ints[0],
				.speed = FIX16(0),
				.big = TRUE
			};
			spawner.bools[0] = enemies[i].clock % 120 < 60;
			spawner.fixes[0] = FIX16(1);
			spawner.ints[0] = spawner.bools[0] ? 32 : -32;
			spawner.image = spawner.bools[0] ? &bigBlueBullet : &bigRedBullet;
			void updater(s16 j){
				if(bullets[j].clock % 5 == 0 && bullets[j].clock > 10){
					bullets[j].speed = fix16Add(bullets[j].speed, bullets[j].fixes[0]);
					bullets[j].angle += bullets[j].ints[0];
					updateBulletVel(j);
				}
			}
			spawnBullet(spawner, updater);
			enemies[i].ints[0] += enemies[i].ints[1];
			enemies[i].ints[1] += spawner.bools[0] ? 2 : -2;
		}
	}

	void patternTwo(s16 i){ // sun 4:10
		if(enemies[i].clock % 30 <= 15 && enemies[i].clock % 5 == 0){
			if(enemies[i].clock % 30 == 0){
				enemies[i].ints[0] = -32 + random() % 64;
				enemies[i].ints[2] = 24;
				enemies[i].fixes[0] = FIX16(24);
				enemies[i].fixes[1] = FIX16(2);
			}
			struct bulletSpawner spawner = {
				.angle = enemies[i].ints[0] - (enemies[i].clock % 60 < 30 ? 48 : -48),
				.speed = FIX16(0),
				.big = TRUE
			};
			spawner.bools[0] = enemies[i].clock % 60 < 30;
			spawner.ints[0] = spawner.bools[0] ? 64 : -64;
			spawner.ints[1] = spawner.bools[0] ? 102 : -102;
			spawner.image = spawner.bools[0] ? &bigRedBullet : &bigBlueBullet;
			void updater(s16 j){
				if(bullets[j].clock == 15){
					if(!bullets[j].bools[0]) bullets[j].angle += 512;
					bullets[j].speed = FIX16(bullets[j].bools[0] ? 3.5 : 5);
					updateBulletVel(j);
				} else if(bullets[j].clock % 15 == 0 && bullets[j].clock > 15){
					bullets[j].angle += bullets[j].ints[0];
					updateBulletVel(j);
				}
			}
			for(s16 j = 0; j < 5; j++){
				spawner.x = fix16Add(enemies[i].pos.x, fix16Mul(cosFix16(spawner.angle), enemies[i].fixes[0]));
				spawner.y = fix16Add(enemies[i].pos.y, fix16Mul(sinFix16(spawner.angle), enemies[i].fixes[0]));
				spawnBullet(spawner, updater);
				spawner.angle += spawner.ints[1];
			}
			enemies[i].ints[0] += spawner.bools[0] ? 48 : -48;
		}
	}

	void patternThree(s16 i){ // coils 4:17
		if(enemies[i].clock % 3 == 0 && enemies[i].clock % 60 < 45){
			if(enemies[i].clock % 60 == 0){
				enemies[i].ints[0] = random() % 1024;
				enemies[i].fixes[0] = FIX16(16);
				enemies[i].fixes[1] = fix16Add(enemies[i].pos.x, FIX16(enemies[i].clock % 120 == 0 ? (16 + random() % 16) : (-32 - random() % 16)));
				enemies[i].fixes[2] = enemies[i].pos.y;
			}
			struct bulletSpawner spawner = {
				.x = fix16Add(enemies[i].fixes[1], fix16Mul(cosFix16(enemies[i].ints[0]), enemies[i].fixes[0])),
				.y = fix16Add(enemies[i].fixes[2], fix16Mul(sinFix16(enemies[i].ints[0]), fix16Mul(FIX16(0.5), enemies[i].fixes[0]))),
				.speed = FIX16(3),
				.image = &smallRedBullet,
				.angle = enemies[i].ints[0]
			};
			void updater(s16 j){
				if(bullets[j].bools[0] && bullets[j].clock == 30){
					struct bulletSpawner spawner = {
						.x = bullets[j].pos.x,
						.y = bullets[j].pos.y,
						.speed = FIX16(5),
						.image = &smallRedBullet,
						.angle = 256
					};
					spawner.vel = hone(bullets[j].pos, player.pos, spawner.speed, 4);
					spawnBullet(spawner, EMPTY);
					bullets[j].speed = FIX16(4);
					bullets[j].angle = random() % 256 + 128;
					updateBulletVel(j);

				} else if(bullets[j].clock % 5 == 0 && bullets[j].clock > 0 && !bullets[j].bools[0]){
					bullets[j].speed = fix16Sub(bullets[j].speed, FIX16(1));
					if(bullets[j].speed <= 0) bullets[j].bools[0] = TRUE;
					updateBulletVel(j);
				}
			}
			spawnBullet(spawner, updater);
			enemies[i].ints[0] += enemies[i].clock % 120 < 60 ? 64 : -64;
		}
	}

	void patternFour(s16 i){ // knives + balls 4:27
		if(enemies[i].clock % 30 == 0){
			enemies[i].bools[0] = enemies[i].clock % 60 < 30;
			enemies[i].fixes[0] = FIX16(32);
			enemies[i].fixes[1] = FIX16(enemies[i].bools[0] ? GAME_W / 4 : GAME_W / 4 * 3);
			struct bulletSpawner spawner = {
				.x = enemies[i].fixes[1],
				.y = enemies[i].pos.y,
				.speed = FIX16(5),
				.image = &bigRedBullet,
				.big = TRUE,
				.angle = enemies[i].ints[0]
			};
			spawner.ints[0] = enemies[i].bools[0] ? -32 : 32;
			void updater(s16 j){
				if(bullets[j].clock == 5){
					bullets[j].angle += 512;
					bullets[j].speed = FIX16(0);
					updateBulletVel(j);
				} else if(bullets[j].clock == 15){
					bullets[j].angle += 512;
					bullets[j].speed = FIX16(3.5);
					updateBulletVel(j);
				} else if(bullets[j].clock > 15 && bullets[j].clock % 5 == 0){
					bullets[j].angle += bullets[j].ints[0];
					updateBulletVel(j);
				}
			}
			spawnExplosion(spawner.x, spawner.y);
			for(s16 j = 0; j < 8; j++){
				spawner.bools[0] = i % 2 == 0;
				spawnBullet(spawner, updater);
				spawner.angle += 128;
			}
			enemies[i].speed = FIX16(1);
			if(enemies[i].clock % 240 == 0) enemies[i].angle = 480;
			else if(enemies[i].clock % 240 == 60) enemies[i].angle = 32;
			else if(enemies[i].clock % 240 == 120) enemies[i].angle = -32;
			else if(enemies[i].clock % 240 == 180) enemies[i].angle = 544;
			updateEnemyVel(i);
		}
		if(enemies[i].clock % 10 == 5){
			struct bulletSpawner spawner = {
				.x = enemies[i].pos.x,
				.y = enemies[i].pos.y,
				.speed = FIX16(4),
				.image = &bigBlueBullet,
				.big = TRUE,
				.angle = 256
			};
			spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, 8);
			spawnBullet(spawner, EMPTY);
			spawner.speed = FIX16(3);
			spawner.big = FALSE;
			spawner.image = &smallBlueBullet;
			spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, 32);
			spawnBullet(spawner, EMPTY);
		}
	}

	void patternFive(s16 i){ // balls to bottom 4:43
		if(enemies[i].clock % 120 == 0){

		}
	}

	void patternSix(s16 i){ // corner + burst 4:58

	}

	if(waveClock == 0){
		struct enemySpawner spawner = {
			.x = GAME_W / 2,
			.y = 48,
			.offX = 24,
			.offY = 28,
			.image = &sannyo,
			.speed = 0,
			.angle = 256,
			.health = 500
		};
		bossMax = spawner.health;
		void updater(s16 i){
			bossHealth = enemies[i].health;
			patternFive(i);
		}
		spawnEnemy(spawner, updater);
	}
	waveClock = 1;
}

void bossThree(){ // 6:40

	void patternOne(s16 i){ // triad 6:41

	}

	void patternTwo(s16 i){ // knives + bubbles 6:58

	}

	void patternThree(s16 i){ // sentries with balls + small 7:26

	}

	void patternFour(s16 i){ // lots of balls 7:48
		
	}

	void patternFive(s16 i){ // reflect-once lasers 8:18
		
	}

	void patternSix(s16 i){ // crazier lasers with knives 8:40
		
	}

	void patternSeven(s16 i){ // fast ball bursts 9:05

	}

	void patternEight(s16 i){ // horizontal shots 9:19

	}

	void patternNine(s16 i){ // coils + balls 9:47

	}

}


// wave

void updateWave(){
	bossTwo();
}


// // loop

void loadStage(){
	currentWave = &waveSix;
}

void updateStage(){
	updateWave();
	stageClock++;
	waveClock++;
	if(stageClock >= CLOCK_LIMIT) stageClock = 0;
}






			// if(enemies[i].clock == 60){
			// 	struct bulletSpawner spawner = {
			// 		.x = enemies[i].pos.x,
			// 		.y = enemies[i].pos.y,
			// 		.image = enemies[i].bools[0] ? &smallBlueBullet : &smallRedBullet,
			// 		// .big = TRUE,
			// 		.speed = FIX16(2),
			// 		.angle = 256
			// 	};
			// 	spawner.vel = hone(enemies[i].pos, player.pos, spawner.speed, 4);
			// 	spawnBullet(spawner, EMPTY);
			// 	enemies[i].speed = FIX16(1.5);
			// }
			// if(enemies[i].clock >= 60 && enemies[i].clock < 100 && enemies[i].clock % 5 == 0){
			// 	enemies[i].angle += enemies[i].ints[0];
			// 	updateEnemyVel(i);
			// }