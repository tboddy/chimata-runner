// background

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "background.h"


// scrolling
void updateBackground(){
	if(clock % 4 == 0){
		bgPos.x -= 1;
		if(clock % 8 == 0) bgPos.y -= 1;
		if(bgPos.x < BG_SIZE) bgPos.x = 0;
		if(bgPos.y < BG_SIZE) bgPos.y = 0;
		VDP_setHorizontalScroll(BG_B, bgPos.x);
		VDP_setVerticalScroll(BG_B, bgPos.y);
	}
}


// load room

void loadBg(){
	for(s16 x = 0; x < BG_WIDTH; x++) for(s16 y = 0; y < BG_HEIGHT; y++)
		if(x % 8 == 0 && y % 8 == 0) VDP_drawImageEx(BG_B, &ground3, TILE_ATTR_FULL(PAL2, 0, 0, 0, BG_I), x, y, 0, DMA);
}

void loadFg(){
	for(s16 x = 0; x < BG_WIDTH; x++) for(s16 y = 0; y < BG_HEIGHT; y++){
		if ((y == 0 && x == 0) || (x == 31 && y == 0) || (y == 27 && x == 31) || (y == 27 && x == 0))
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL2, 0, 0, 0, HALF_TILE), x, y);
		else if(y == 0 || y == 27 || x == 0 || x == 31)
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL2, 0, 0, 0, MOST_TILE), x, y);
	}
}

void loadBackground(){
	VDP_setScrollingMode(HSCROLL_PLANE, HSCROLL_PLANE);
	loadBg();
	loadFg();
}