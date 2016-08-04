#ifndef MENU_H_
#define MENU_H_

typedef struct MenuItem
{
	char title1row[16];
	char title2row[16];
	int delayBetweenRefreshInMillis;		//"-1"-static context, 0-? in millis
	void (*callFunction)();
	struct MenuItem* nextMenu;
	struct MenuItem* subMenu;
} MenuItem;

MenuItem* mainMenuItem;
char title1[16],title2[16];

void prepareMenu();
void tachoView();
void adcView();
void welcomingMessage();

#endif /* MENU_H_ */