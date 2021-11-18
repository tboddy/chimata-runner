// enemies

#define ENEMY_COUNT 18
#define COUNT_INT 8

struct enemySpawner {
	fix16 speed;
	s16 angle, offX, offY, x, y, anim, health;
	Vect2D_f16 vel;
	Sprite* image;
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
};

struct enemy {
	bool active;
	fix16 speed;
	fix32 dist;
	Vect2D_f16 pos, vel, off;
	s16 angle, clock, health;
	Sprite* image;
	void (*updater)(s16);
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
};
struct enemy enemies[ENEMY_COUNT];


// spawn

void spawnEnemy(struct enemySpawner, void(*updater));
Vect2D_f16 velPos;

// update

void updateEnemy(s16),
	updateEnemyVel(s16),
	killEnemy(s16),
	updateEnemies();