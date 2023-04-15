#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include "ui_QT_D3D11.h"
#include"DxWindow.h"
class QT_D3D11 : public QMainWindow
{
    Q_OBJECT
public:
	QT_D3D11(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::QT_D3D11Class ui;
	//DxWindow* Dxwindow;
private slots:
	void on_actionOpenFile_triggered();
	void on_actionTex_triggered();
	
	void on_radioWhiteLight_clicked();
	void on_radioBlueLight_clicked();
	void on_radioRedLight_clicked();

	void on_rBtnNormal_clicked();
	void on_rBtnWater_clicked();
	void on_rBtnFire_clicked();
	
	void on_cBtnSpec_clicked(bool);

	void on_BtnModify_clicked();

	//QString filepath;
	void on_CamSlidee_changed(int);
	void on_LightSlidee_changed(int);
};
