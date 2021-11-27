// start

#define START_BG_HEIGHT 28
#define START_BG_WIDTH 40


// sega screen

#define START_TOP_TILE 13

#define SEGA_LIMIT 60 * 4

#define SEGA_X 320 / 2
#define SEGA_Y 224 / 2 - 16


Sprite* segaImage1;
Sprite* segaImage2;

// logo

#define START_MENU_X 3
#define START_MENU_Y 14

#define START_LOGO_LINES 32
#define START_LOGO_Y 5

bool started, selectingStartMenu, aboutShowing, loadedStart;

s16 currentStartMenu, lastStartMenu, startClock, aboutY;

s16 startLogoScrolls[START_LOGO_LINES];
bool startLogoScrollsFlip[START_LOGO_LINES], updatingStartCount;

s16 startCurrentLives;

char startHighScoreStr[10];
char startCurrentLivesStr[4];

void loadStartBg(),
	loadStart(),
	loadStartLogo(),
	loadStartMenu(),
	resetStart(),
	startGoBack(),
	selectStartMenu(),
	updateStartMenu(),
	loadStartScore(),
	updateStartLives(),
	updateStartAbout(),
	loadStartCredits(),
	loadStartAbout(),
	updateStart();