#ifndef MENU_H_
#define MENU_H_

typedef struct MenuItem
{
	int id;
	char title1row[16];
	char title2row[16];
	int delayBetweenRefreshInMillis;		//"-1"-static context, 0-? in millis
	struct MenuItem* nextMenu;
	struct MenuItem* subMenu;
} MenuItem;

MenuItem* mainMenuList;

void prepareMenu();
void printTitles(int id);
#endif /* MENU_H_ */