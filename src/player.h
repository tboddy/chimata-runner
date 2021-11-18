// player

#define PLAYER_INIT_X FIX16(GAME_W / 2)
#define PLAYER_INIT_Y FIX16(8 * 20)

#define PLAYER_Y_LIMIT FIX16(GAME_H - 48)

#define PLAYER_SPEED FIX16(2.5)

#define PLAYER_LIMIT_X FIX16(5)
#define PLAYER_LIMIT_W fix16Sub(FIX16(GAME_W), FIX16(3))
#define PLAYER_LIMIT_Y FIX16(4)
#define PLAYER_LIMIT_Z fix16Sub(FIX16(GAME_H), FIX16(4))


#define INVINCIBLE_LIMIT 170

#define SHOT_ANGLE_MOD 64
#define SHOT_ANGLE_UP 768
#define SHOT_ANGLE_DOWN 256
#define SHOT_ANGLE_LEFT 512
#define SHOT_ANGLE_RIGHT 0


// directions

#define PLAYER_VEL_BL_X fix16Mul(cosFix16(384), PLAYER_SPEED)
#define PLAYER_VEL_BL_Y fix16Mul(sinFix16(384), PLAYER_SPEED)

#define PLAYER_VEL_BR_X fix16Mul(cosFix16(128), PLAYER_SPEED)
#define PLAYER_VEL_BR_Y fix16Mul(sinFix16(128), PLAYER_SPEED)

#define PLAYER_VEL_TL_X fix16Mul(cosFix16(640), PLAYER_SPEED)
#define PLAYER_VEL_TL_Y fix16Mul(sinFix16(640), PLAYER_SPEED)

#define PLAYER_VEL_TR_X fix16Mul(cosFix16(896), PLAYER_SPEED)
#define PLAYER_VEL_TR_Y fix16Mul(sinFix16(896), PLAYER_SPEED)


// struct

struct player {
	Vect2D_f16 pos, vel, off;
	s16 angle, moveClock, shotClock, clock, invincibleClock, health,
		lives, bombs;
	fix16 moveSpeed, shotSpeed;
	fix32 dist;
	bool invincible;
	Sprite* image;
};
struct player player;


// spawn

void spawnPlayer();


// shoot

#define PLAYER_BULLET_COUNT 16
s16 playerBulletIndexes[PLAYER_BULLET_COUNT];

void spawnPlayerBullet(),
	updatePlayerBullet(s16);


// update

#define SHOT_INTERVAL 10

s16 colDebug1, colDebug2, colDebug3;

void movePlayer(),
	collidePlayer(),
	updatePlayerShot();


// loop

void updatePlayer(),
	loadPlayer();