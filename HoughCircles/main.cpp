#include "main-window.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QApplication>

int main(int nArgC, char *apszArgV[]) {
	srand(time(NULL));
	QApplication app(nArgC, apszArgV);
	MainWindow *pWindow = new MainWindow;
	pWindow->show();

	return app.exec();
}
