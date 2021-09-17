// player

#define PLAYER_INIT_X FIX16(GAME_W / 2)
#define PLAYER_INIT_Y FIX16(8 * 18)

#define PLAYER_SPEED FIX16(2)
#define PLAYER_SPEED_LEFT FIX16(1.5)

Vect2D_f16 playerPos, playerVel, playerOff;
Sprite* playerSprite;


// spawn

void spawnPlayer(s16);


// update

#define C_OFF FIX16(8)
#define C_OFF_Y FIX16(0)
#define C_OFF_2 FIX16(6)
#define C_OFF_3 FIX16(5)
#define C_MOD FIX16(8)

#define FALL_MAX FIX16(1.25)
#define JUMP_SPEED FIX16(-5.5)

#define GRAVITY FIX16(0.2)
#define GRAVITY_MIN FIX16(0.05)
#define GRAVITY_MAX FIX16(3.5)

#define SHOT_INTERVAL 10

Vect4D_f16 dist, bPos, pPos;

s16 pClock, moveClock, jumpClock, shotClock, shotAngle;
fix16 fallSpeed;

bool falling, jumping;

void jumpPlayer(),
	movePlayer(),
	updatePlayerCollision(),
	updatePlayerShot();


// loop

void updatePlayer(s16),
	loadPlayer();