#include "QT_D3D11.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QT_D3D11 w;
	w.show();
	return a.exec();
}
