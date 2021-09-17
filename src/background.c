// blocks

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "entities.h"
#include "background.h"


// scrolling
void updateBackground(){
	for(s16 i = 0; i < BG_HEIGHT; i++){
		if(i >= FLOOR_Y && scrollClock % 2 == 0){
			bgPos[i]--;
			if(bgPos[i] <= -GAME_W) bgPos[i] = 0;
		}
		else if(i >= TREES_Y && scrollClock % 4 == 3){
			bgPos[i]--;
			if(bgPos[i] <= -TREES_LIMIT) bgPos[i] = 0;
		}
		else if(i >= CLOUD_TOP_Y && i < CLOUD_TOP_Y + 2 && scrollClock % 120 == 45){
			bgPos[i]--;
			if(bgPos[i] <= -CLOUD_LIMIT) bgPos[i] = 0;
		}
		else if(i >= CLOUD_BOTTOM_Y && i < CLOUD_BOTTOM_Y + 3 && scrollClock % 60 == 25){
			bgPos[i]--;
			if(bgPos[i] <= -CLOUD_LIMIT) bgPos[i] = 0;
		}
		if(i >= FG_Y && i < FG_Y + 5 && scrollClock % 2 == 1){
			fgPos[i]--;
			if(fgPos[i] <= -FG_LIMIT) fgPos[i] = 0;
		}
	}
	VDP_setHorizontalScrollTile(BG_B, 0, bgPos, BG_HEIGHT, DMA_QUEUE);
	VDP_setHorizontalScrollTile(BG_A, 0, fgPos, BG_HEIGHT, DMA_QUEUE);
	scrollClock++;
	if(scrollClock >= CLOCK_LIMIT) scrollClock = 0;
}


// load room

void loadSky(){
	for(s16 x = 0; x < CLOUD_COUNT; x++){
		VDP_drawImageEx(BG_B, &cloudTop, TILE_ATTR_FULL(PAL1, 0, 0, 0, CLOUD_I), CLOUD_W * x, CLOUD_TOP_Y, 0, DMA);
		VDP_drawImageEx(BG_B, &cloudBottom, TILE_ATTR_FULL(PAL1, 0, 0, 0, CLOUD__BOTTOM_I), CLOUD_W * x, CLOUD_BOTTOM_Y, 0, DMA);
	}
	for(s16 x = 0; x < STARS_COUNT; x++){
		VDP_drawImageEx(BG_B, &stars, TILE_ATTR_FULL(PAL1, 0, 0, 0, STARS_I), STARS_W * x, STARS_Y, 0, DMA);
	}
}

void loadTrees(){
	for(s16 x = 0; x < TREES_COUNT; x++){
		VDP_drawImageEx(BG_B, &trees, TILE_ATTR_FULL(PAL1, 0, 0, 0, TREES_I), x * TREES_WIDTH, TREES_Y, 0, DMA);
		VDP_drawImageEx(BG_A, &fg, TILE_ATTR_FULL(PAL1, 0, 0, 0, FG_I), x * TREES_WIDTH, FG_Y, 0, DMA);
	}
}

void loadBackground(){
	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);
	VDP_loadTileSet(tiles.tileset, TILES_I, DMA);
	for(s16 y = 0; y < BG_HEIGHT; y++){
		for(s16 x = 0; x < BG_WIDTH; x++){
			if(y < FLOOR_Y){
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, BLOCK_BLANK), x, y);
			} else if(y == FLOOR_Y && x % 2 == 0){
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 1, 0, ROCK_Y), x, y);
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 1, 0, ROCK_Y + 1), x + 1, y);
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 1, 0, ROCK_Y + 2), x, y + 1);
				VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 1, 0, ROCK_Y + 3), x + 1, y + 1);
			} 
		}
	}
	loadSky();
	loadTrees();
}