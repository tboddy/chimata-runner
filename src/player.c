// player

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "entities.h"
#include "player.h"


// spawn

void spawnPlayer(s16 i){
	ent[i].offX = 16;
	ent[i].offY = 18;
}


// move

void jumpPlayer(){
	if(falling){
		if(jumpClock % 10 == 0 && jumpClock > 0 && jumpClock < 10 * 3) SPR_nextFrame(ent[p].image);
		jumpClock++;
	}
	if(ctrl.a && !jumping && fallSpeed == 0){
		SPR_setFrame(ent[p].image, 1);
		jumpClock = 0;
		fallSpeed = JUMP_SPEED;
		jumping = TRUE;
		falling = TRUE;
	} else if(!ctrl.a && jumping && fallSpeed == 0) jumping = FALSE;
	ent[p].pos.y = fix16Add(ent[p].pos.y, fallSpeed);
	if(fallSpeed < GRAVITY_MAX){
		fallSpeed = fix16Add(fallSpeed, GRAVITY);
		if(fallSpeed > GRAVITY_MAX) fallSpeed = GRAVITY_MAX;
	}
}

void movePlayer(){
	ent[p].speed = 0;
	if(ctrl.left || ctrl.right || ctrl.up || ctrl.down){
		if(ctrl.left || ctrl.right){
			ent[p].angle = ctrl.left ? 512 : 0;
			ent[p].speed = ctrl.left ? PLAYER_SPEED_LEFT : PLAYER_SPEED;
			SPR_setHFlip(ent[p].image, ctrl.left ? 1 : 0);
			shotAngle = ent[p].angle;
			if(ctrl.up) shotAngle = ctrl.left ? 640 : 896;
			else if(ctrl.down) shotAngle = ctrl.left ? 384 : 128;
		} else if(ctrl.up) shotAngle = 768;
		else if(ctrl.down) shotAngle = 256;
	}
	if(!falling) if(moveClock % 10 == 0) SPR_nextFrame(ent[p].image);
	moveClock++;
	if(moveClock >= CLOCK_LIMIT) moveClock = 0;
}

void updatePlayerCollision(){
	if(ent[p].pos.x < FIX16(ent[p].offX)){
		ent[p].speed = 0;
		ent[p].pos.x = FIX16(ent[p].offX);
	} else if(ent[p].pos.x > fix16Sub(FIX16(GAME_W), FIX16(ent[p].offX))){
		ent[p].speed = 0;
		ent[p].pos.x = fix16Sub(FIX16(GAME_W), FIX16(ent[p].offX));
	}
	if(ent[p].pos.y > fix16Sub(fix16Sub(FIX16(GAME_H), FIX16(ent[p].offY)), FIX16(16))){
		fallSpeed = 0;
		falling = FALSE;
		ent[p].pos.y = fix16Sub(fix16Sub(FIX16(GAME_H), FIX16(ent[p].offY)), FIX16(16));
	}
}


// shoot
void spawnPlayerBullet(){
	struct spawner spawner = {
		.x = ent[p].pos.x,
		.y = ent[p].pos.y,
		.type = TYPE_BULLET,
		.image = &smallWhiteBullet,
		.speed = FIX16(6),
		.angle = shotAngle
	};
	spawn(spawner, EMPTY);
}

void updatePlayerShot(){
	if(shotClock >= SHOT_INTERVAL && ctrl.b) shotClock = 0;
	if(shotClock == 0) spawnPlayerBullet();
	shotClock++;
	if(shotClock >= CLOCK_LIMIT) shotClock = SHOT_INTERVAL;
}


// loop

void updatePlayer(s16 i){
	p = i;
	jumpPlayer();
	movePlayer();
	UPDATE_VEL(p);
	updatePlayerCollision();
	updatePlayerShot();
	pClock++;
	if(pClock >= CLOCK_LIMIT) pClock = 0;
}

void loadPlayer(){
	shotClock = SHOT_INTERVAL;
	struct spawner spawner = {
		.x = PLAYER_INIT_X,
		.y = PLAYER_INIT_Y,
		.type = TYPE_PLAYER,
		.image = &chimata
	};
	spawn(spawner, EMPTY);
}