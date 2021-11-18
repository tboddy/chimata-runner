// background

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "background.h"


// scrolling
void updateBackground(){
	VDP_setVerticalScrollTile(BG_B, 0, bgPos, BG_WIDTH_2, DMA_QUEUE);
	VDP_setVerticalScrollTile(BG_A, 0, fgPos, BG_WIDTH_2, DMA_QUEUE);
	for(s16 x = 0; x < BG_WIDTH_2; x++){
		fgPos[x] -= 6;
		bgPos[x] -= 2;
		if(fgPos[x] < BG_SIZE) fgPos[x] = 0;
		if(bgPos[x] < BG_SIZE) bgPos[x] = 0;
	}
	scrollClock++;
	if(scrollClock >= CLOCK_LIMIT) scrollClock = 0;
}


// load room

void loadBg(){
	for(s16 x = 0; x < BG_WIDTH; x++){
		for(s16 y = 0; y < BG_HEIGHT; y++){
			if(x % 8 == 0 && y % 8 == 0){
				VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL2, 0, 0, 0, BG_I), x, y, 0, DMA);
				VDP_drawImageEx(BG_A, &clouds1, TILE_ATTR_FULL(PAL2, 0, 0, 0, FG_I), x, y, 0, DMA);
			}
		}
		// if(x < 2) VDP_drawImageEx(BG_A, &forestTrees, TILE_ATTR_FULL(PAL2, 0, 0, 0, BG_1_I), x * FOREST_BG_W, 3, 0, DMA);
		// if(x < 4) VDP_drawImageEx(BG_B, &forestTrees2, TILE_ATTR_FULL(PAL2, 0, 0, 0, BG_2_I), x * FOREST_BG_W_2, 9, 0, DMA);
		// VDP_drawImageEx(BG_A, x % 2 == 0 ? &forestGround1 : &forestGround2, TILE_ATTR_FULL(PAL2, 0, 0, 0, x % 2 == 0 ? FG_1_I : FG_2_I), x * 6, 22, 0, DMA);
	}
}

void loadBackground(){
	loadBg();
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_2TILE);
}


// VDP_loadTileSet(bgCloud.tileset, CLOUD_I, DMA);

	// for(s16 x = 0; x < BG_WIDTH; x++) for(s16 y = 0; y < 7; y++) // under sky
	// 	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, CLOUD_I), x, CLOUD_Y + y);

	// for(s16 x = 0; x < 3; x++){

	//   // sky
	// 	VDP_drawImageEx(BG_B, &bgSky1, TILE_ATTR_FULL(PAL2, 0, 0, 0, SKY_I), SKY_W * x, SKY_Y, 0, DMA);
	// 	if(x < 2) VDP_drawImageEx(BG_B, &bgSky2, TILE_ATTR_FULL(PAL2, 0, 0, 0, SKY_I + SKY_MOD), SKY_W * x + SKY_H, SKY_Y, 0, DMA);

	//   // mountains
	// 	VDP_drawImageEx(BG_A, &bgMountains, TILE_ATTR_FULL(PAL2, 0, 0, 0, MOUNTAIN_I), MOUNTAIN_W * x, MOUNTAIN_Y, 0, DMA);

	// 	// trees far
	// 	VDP_drawImageEx(BG_B, &bgTreesFar, TILE_ATTR_FULL(PAL2, 0, 0, 0, FAR_I), x * FAR_W, FAR_Y, 0, DMA);

	// 	// trees near
	// 	VDP_drawImageEx(BG_A, &bgTrees1, TILE_ATTR_FULL(PAL2, 0, 0, 0, TREES_I), x * TREES_W, TREES_Y, 0, DMA);
	// 	if(x < 2) VDP_drawImageEx(BG_A, &bgTrees2, TILE_ATTR_FULL(PAL2, 0, 0, 0, TREES_I + TREES_MOD), x * TREES_W + TREES_OFF, TREES_Y, 0, DMA);

	// }


	// // fg plants
	// for(s16 x = 0; x < 2; x++){
	// 	VDP_drawImageEx(BG_A, &bgPlant1, TILE_ATTR_FULL(PAL2, 1, 0, 0, PLANT_I), 0 + x * 32, PLANT_Y, 0, DMA);
	// 	VDP_drawImageEx(BG_A, &bgPlant2, TILE_ATTR_FULL(PAL2, 1, 0, 0, PLANT_I + 8), 16 + x * 32, PLANT_Y, 0, DMA);
	// }


// if(i >= SKY_Y && i < SKY_Y + SKY_H - 1 && scrollClock % 50 == 41){ // sky
	// 	bgPos[i]--;
	// 	if(bgPos[i] <= -SKY_LIMIT) bgPos[i] = 0;
	// }

	// if(i >= MOUNTAIN_Y && i < MOUNTAIN_Y + MOUNTAIN_H && scrollClock % 240 == 209){ // mountains
	// 	fgPos[i]--;
	// 	if(fgPos[i] <= -MOUNTAIN_LIMIT) fgPos[i] = 0;
	// }

	// if(i >= FAR_Y && i < FAR_Y + FAR_H && scrollClock % 20 == 17){ // tree far
	// 	bgPos[i]--;
	// 	if(bgPos[i] <= -FAR_LIMIT) bgPos[i] = 0;
	// }

	// if(i >= TREES_Y && i < TREES_Y + TREES_H && scrollClock % 4 == 3){ // tree near
	// 	fgPos[i]--;
	// 	if(fgPos[i] <= -TREES_LIMIT) fgPos[i] = 0;
	// }

	// if(i >= FLOOR_Y && scrollClock % 2 == 0){ // ground
	// 	bgPos[i]--;
	// 	if(bgPos[i] <= -BG_LIMIT) bgPos[i] = 0;
	// }
	
	// if(i >= PLANT_Y){ // plants
	// 	fgPos[i]--;
	// 	if(fgPos[i] <= -PLANT_LIMIT) fgPos[i] = 0;
	// }

	// bgPos[i]--;
	// if(bgPos[i] <= -272) bgPos[i] = 0;

// VDP_loadTileSet(tiles.tileset, TILES_I, DMA);
	// VDP_loadTileSet(floor.tileset, FLOOR_I, DMA);
	// for(s16 y = 0; y < BG_HEIGHT; y++){
	// 	for(s16 x = 0; x < BG_WIDTH; x++){
	// 		if(y < FLOOR_Y){
	// 			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, BLOCK_BLANK), x, y);
	// 		} else if(y == FLOOR_Y && x % 4 == 0){
	// 			floorBase = 0;
	// 			if(x % 12 == 4) floorBase += 16;
	// 			else if(x % 12 == 8) floorBase += 32;
	// 			for(s16 i = 0; i < 4; i++)
	// 				for(s16 j = 0; j < 4; j++) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL2, 0, 0, 0, FLOOR_I + i + j * 4 + floorBase), x + i, y + j);
	// 		} 
	// 	}
	// }
	// loadBg();