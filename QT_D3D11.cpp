#include "QT_D3D11.h"
#include<iostream>
#include <fstream>
QString filepath;

bool result1;
int vertexCount1, textureCount1, normalCount1, faceCount1;

QT_D3D11::QT_D3D11(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	resize(QSize(1000, 900));

	//Dxwindow = new DxWindow;

	connect(ui.actionOpenFile, &QAction::trigger, this, &QT_D3D11::on_actionOpenFile_triggered);
	connect(ui.actionTex, SIGNAL(triggerer()), this, SLOT(on_actionTex_triggered()));

	connect(ui.radioWhiteLight, SIGNAL(clicked()), this, SLOT(on_radioWhiteLight_clicked()));
	connect(ui.radioBlueLight, SIGNAL(clicked()), this, SLOT(on_radioBlueLight_clicked()));
	connect(ui.radioRedLight, SIGNAL(clicked()), this, SLOT(on_radioRedLight_clicked()));

	connect(ui.rBtnNormal, SIGNAL(clicked()), this, SLOT(on_rBtnNormal_clicked()));
	connect(ui.rBtnWater, SIGNAL(clicked()), this, SLOT(on_rBtnWater_clicked()));
	connect(ui.rBtnFire, SIGNAL(clicked()), this, SLOT(on_rBtnFire_clicked()));

	connect(ui.cBtnSpec, SIGNAL(clicked(bool)), this, SLOT(on_cBtnSpec_clicked(bool)));
	
	connect(ui.BtnModify, SIGNAL(clicked()), this, SLOT(on_BtnModify_clicked()));

	connect(ui.camSlider, SIGNAL(valueChanged(int)), this, SLOT(on_CamSlidee_changed(int)));
	connect(ui.lightSlider, SIGNAL(valueChanged(int)), this, SLOT(on_LightSlidee_changed(int)));
}

void QT_D3D11::on_actionOpenFile_triggered() {
	//MessageBox((HWND)winId(), L"triggered", NULL, MB_OK);

	QString curpath = QCoreApplication::applicationDirPath();
	QString dlgTitle = "打开文件";
	QString filter = "objFile(*.obj);;text(*.txt);;all(*.*)";
	filepath = QFileDialog::getOpenFileName(this,dlgTitle,curpath,filter);

	if (filepath.isEmpty())return;

	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		ui.FileText->setPlainText(file.readAll());
		file.close();
		ui.tabWidget->setCurrentIndex(1);
	}
	ui.W_DxWindow->setRaster(0);
	ui.W_DxWindow->filepath = filepath.toStdString();
	ui.W_DxWindow->isback = false;
	ui.W_DxWindow->isFirstOpen = true;
}



void QT_D3D11::on_radioWhiteLight_clicked()
{
	ui.W_DxWindow->setLightColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void QT_D3D11::on_radioBlueLight_clicked()
{
	ui.W_DxWindow->setLightColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void QT_D3D11::on_radioRedLight_clicked()
{
	ui.W_DxWindow->setLightColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void QT_D3D11::on_rBtnNormal_clicked()
{
	ui.W_DxWindow->renderMode = 1;
}

void QT_D3D11::on_rBtnWater_clicked()
{
	ui.W_DxWindow->renderMode = 2;
}

void QT_D3D11::on_rBtnFire_clicked()
{
	//MessageBox((HWND)winId(),L"fire",NULL,MB_OK);
	ui.W_DxWindow->renderMode = 3;
}

void QT_D3D11::on_actionTex_triggered()
{	
	QString curpath = QCoreApplication::applicationDirPath();
	QString dlgTitle = "打开文件";
	QString filter = "texFile(*.dds);;text(*.txt);;all(*.*)";
	QString texpath = QFileDialog::getOpenFileName(this, dlgTitle, curpath, filter);

	ui.W_DxWindow->texpath = texpath.toStdString();
	ui.W_DxWindow->setRaster(1);
}

void QT_D3D11::on_cBtnSpec_clicked(bool isClicked)
{
	ui.W_DxWindow->setSpec(isClicked);
	//MessageBox((HWND)winId(), L"CBTN", NULL, MB_OK);
}

void QT_D3D11::on_BtnModify_clicked()
{
	//MessageBox((HWND)winId(), L"BTN", NULL, MB_OK);
	QFile file(filepath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QString str = ui.FileText->toPlainText();
	QByteArray strBytes = str.toUtf8();
	file.write(strBytes,strBytes.length());
	ui.tabWidget->setCurrentIndex(1);
	ui.W_DxWindow->isModify = true;
}

void QT_D3D11::on_CamSlidee_changed(int value)
{
	//MessageBox((HWND)winId(), L"slider", NULL, MB_OK);
	ui.W_DxWindow->angle = value;
}

void QT_D3D11::on_LightSlidee_changed(int value) {
	//MessageBox((HWND)winId(), L"slider", NULL, MB_OK);
	ui.W_DxWindow->lightangle = value;
}


