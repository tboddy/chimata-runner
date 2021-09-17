// stage

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "entities.h"
#include "enemies.h"
#include "stage.h"


void waveOne(){

	void spawnEnemy(bool dir){

		// update
		void eUpdater(s16 i){

			// spawn bullet
			if(ent[i].clock % 90 == ent[i].ints[0]){
				struct spawner spawner = {
					.x = ent[i].pos.x,
					.y = ent[i].pos.y,
					.type = TYPE_BULLET,
					.image = &smallBlueBullet
				};
				ePos.x = spawner.x;
				ePos.y = spawner.y;
				spawner.vel = hone(ePos, ent[p].pos, FIX16(1), 0);
				spawn(spawner, EMPTY);
			}

			// change direction
			if(ent[i].clock >= ent[i].ints[2] && ent[i].clock < ent[i].ints[3] && ent[i].clock % 15 == 0){
				ent[i].angle -= 512 - 64;
				ent[i].angle += random() % 128;
				UPDATE_VEL(i);
			} else if(ent[i].clock == ent[i].ints[3]){
				ent[i].angle = ent[i].ints[1];
				UPDATE_VEL(i);
			}
		}

		// spawn
		struct spawner spawner = {
			.x = FIX16(dir ? GAME_W + 24 : -24),
			.y = fix16Add(FIX16(32), FIX16(random() % 56)),
			.type = TYPE_ENEMY,
			.subType = TYPE_SMALL_ONE,
			.image = &bakebake,
			.speed = FIX16(1),
			.angle = dir ? 512 : 0,
			.offX = 8,
			.offY = 8
		};
		spawner.ints[0] = random() % 90;
		spawner.ints[1] = spawner.angle;
		spawner.ints[2] = 120;
		spawner.ints[3] = 240;
		spawner.bools[0] = dir;
		spawn(spawner, eUpdater);
	}

	if(waveClock % 120 == 0) spawnEnemy(waveClock % 240 == 0);
}

void waveTwo(){
	if(waveClock % 240 == 0){

		// update
		void eUpdater(s16 i){

			if(ent[i].clock % 90 == ent[i].ints[0]){

				// movement
				ent[i].angle = ent[i].angle == 544 ? 480 : 544;
				UPDATE_VEL(i);

				// missle
				struct spawner spawner = {
					.x = ent[i].pos.x,
					.y = ent[i].pos.y,
					.type = TYPE_BULLET,
					.image = &smallRedBullet
				};
				spawner.bools[0] = ent[i].bools[0];
				spawner.ints[1] = 32 - random() % 64;
				spawner.angle = (spawner.bools[0] ? 512 : 0) + spawner.ints[1];
				spawner.speed = FIX16(spawner.bools[0] ? 1 : 0.75);
				ent[i].bools[0] = !ent[i].bools[0];
				void bUpdater(s16 j){
					if(ent[j].clock % 20 == 0 && ent[j].ints[0] < 4 && ent[j].clock > 0){
						ent[j].angle -= ent[j].bools[0] ? 40 : -40;
						UPDATE_VEL(j);
						ent[j].ints[0]++;
					}
				}
				spawn(spawner, bUpdater);
			}

			// shot
			if(ent[i].clock % 90 == ent[i].ints[1]){
				struct spawner spawner = {
					.x = ent[i].pos.x,
					.y = ent[i].pos.y,
					.type = TYPE_BULLET,
					.image = &smallBlueBullet
				};
				ePos.x = spawner.x;
				ePos.y = spawner.y;
				spawner.vel = hone(ePos, ent[p].pos, FIX16(1.25), 32);
				spawn(spawner, EMPTY);
			}

		}

		// spawn

		struct spawner spawner = {
			.x = FIX16(GAME_W + 24),
			.y = fix16Add(FIX16(32), FIX16(random() % 56)),
			.type = TYPE_ENEMY,
			.subType = TYPE_MEDIUM_ONE,
			.image =  &bakebake,
			.speed = FIX16(0.4),
			.angle = 544,
			.offX = 8,
			.offY = 8
		};
		spawner.ints[0] = random() % 90;
		spawner.ints[1] = random() % 90;
		spawn(spawner, eUpdater);

	}
}

void waveThree(){

	// update
	void eUpdater(s16 i){

		// move
		if(ent[i].clock == 280){
			ent[i].angle += 480 + random() % 64;
			ent[i].speed = fix16Sub(ent[i].speed, FIX16(0.15));
			UPDATE_VEL(i);
		}

		// ring
		if(ent[i].clock >= 120 && ent[i].clock % 20 == 0 && ent[i].ints[0] < 3){
			if(ent[i].clock == 120){
				ent[i].vectors[0].x = ent[i].pos.x;
				ent[i].vectors[0].y = ent[i].pos.y;
				ent[i].ints[1] = random() % 1024;
			}
			struct spawner spawner = {
				.x = ent[i].vectors[0].x,
				.y = ent[i].vectors[0].y,
				.type = TYPE_BULLET,
				.image = &smallBlueBullet,
				.angle = ent[i].ints[1],
				.speed = FIX16(1.75)
			};
			void bUpdater(s16 j){
				if(ent[j].clock % 30 == 0 && ent[j].clock > 0 && ent[j].speed > FIX16(0.75)){
					ent[j].speed = fix16Sub(ent[j].speed, FIX16(0.25));
					UPDATE_VEL(j);
				}
			}
			for(s16 j = 0; j < 8; j++){
				spawn(spawner, bUpdater);
				spawner.angle += 128;
			}
			ent[i].ints[0]++;
		}

		// puke
		if(ent[i].clock >= 160 && ent[i].clock < 180 && ent[i].clock % 2 == 0){
			if(ent[i].clock == 160){
				ent[i].vectors[0].x = ent[i].pos.x;
				ent[i].vectors[0].y = ent[i].pos.y;
			}
			struct spawner spawner = {
				.x = ent[i].vectors[0].x,
				.y = ent[i].vectors[0].y,
				.type = TYPE_BULLET,
				.image = &smallRedBullet,
				.angle = random() % 1024,
				.speed = FIX16(1)
			};
				spawn(spawner, EMPTY);
		}

	}

	// spawn
	if(waveClock % 240 == 0){
		struct spawner spawner = {
			.x = FIX16(GAME_W + 24),
			.y = fix16Add(FIX16(64), FIX16(random() % (GAME_H - 128))),
			.type = TYPE_ENEMY,
			.image =  &bakebake,
			.speed = FIX16(0.4),
			.angle = 512,
			.offX = 8,
			.offY = 8
		};
		spawn(spawner, eUpdater);
	}
}

void waveFour(){
	if(waveClock % 20 == 0){

		void eUpdater(s16 i){
			if(ent[i].clock % 30 == 0 && ent[i].clock > ent[i].ints[2] && ent[i].ints[0] < 4){
				ent[i].angle += ent[i].ints[1];
				ent[i].ints[0]++;
				UPDATE_VEL(i);
			}
		}

		if(waveClock % 120 == 0){
			stageVectors[0].x = FIX16(waveClock % 240 == 0 ? 32 : (GAME_W / 2));
			stageVectors[0].x = fix16Add(stageVectors[0].x, FIX16(random() % (GAME_W / 2 - 32)));
			stageInts[0] = !stageInts[0] || stageInts[0] == 1 ? 2 : 1;
			stageInts[2] = random() % 30;
		}
		struct spawner spawner = {
			.x = stageVectors[0].x,
			.y = FIX16(-8),
			.type = TYPE_ENEMY,
			.image =  &bakebake,
			.speed = FIX16(1.5),
			.angle = 256,
			.offX = 8,
			.offY = 8,
			.anim = stageInts[0]
		};
		spawner.ints[1] = spawner.x > FIX16(GAME_W / 2) ? 64 : -64;
		spawner.ints[2] = stageInts[2];
		if(spawner.x > 0) spawn(spawner, eUpdater);
	}
}

void waveFive(){
	if(waveClock % 60 == 0){

		// movement

		stageVectors[0].x = FIX16(waveClock % 120 == 0 ? 32 : (GAME_W / 2));
		stageVectors[0].x = fix16Add(stageVectors[0].x, FIX16(random() % (GAME_W / 2 - 32)));

		void eUpdater(s16 i){
			if(ent[i].clock % 20 == 0 && ent[i].clock >= ent[i].ints[2] && ent[i].ints[0] < 8){
				ent[i].angle += ent[i].ints[1] * (ent[i].bools[0] ? 1 : -1);
				if(ent[i].ints[0] == 7) ent[i].speed = fix16Sub(ent[i].speed, FIX16(0.5));
				UPDATE_VEL(i);
				ent[i].ints[0]++;
			}

			// shoot

			if(ent[i].clock >= ent[i].ints[2] && ent[i].ints[3] < 8 && ent[i].clock % 4 == 0){
				struct spawner spawner = {
					.x = ent[i].pos.x,
					.y = ent[i].pos.y,
					.type = TYPE_BULLET,
					.offX = 4,
					.offY = 4,
					.speed = ent[i].fixes[0],
					.image = ent[i].ints[3] % 2 == 0 ? &smallGreenBullet : &smallPinkBullet,
					.angle = ent[i].ints[4] + ent[i].ints[3] * 128
				};
				spawn(spawner, EMPTY);
				ent[i].ints[3]++;
				ent[i].fixes[0] = fix16Add(ent[i].fixes[0], FIX16(0.05));
			}

		};

		struct spawner spawner = {
			.x = stageVectors[0].x,
			.y = FIX16(-8),
			.type = TYPE_ENEMY,
			.image =  &bakebake,
			.speed = FIX16(1),
			.angle = 256,
			.offX = 8,
			.offY = 8
		};
		spawner.bools[0] = spawner.x >= FIX16(GAME_W / 2);
		spawner.anim = spawner.bools[0] ? 0 : 1;
		spawner.ints[1] = 96;
		spawner.ints[2] = random() % 2 < 1 ? 120 : 100;
		spawner.ints[4] = random() % 1024;
		spawner.fixes[0] = FIX16(1);
		spawn(spawner, eUpdater);

	}
};

void waveSix(){

};

void waveSeven(){

};

void waveEight(){

};

void waveNine(){

};

void waveTen(){

};


// wave

void updateWave(){
	waveSix();
	waveClock--;
	if(waveClock <= 0) waveClock = WAVE_START;
}


// loop

void loadStage(){
	waveClock = WAVE_START;
}

void updateStage(){
	updateWave();
	stageClock++;
	if(stageClock >= CLOCK_LIMIT) stageClock = 0;
}