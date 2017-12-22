#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_main-window.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

class WorkerThread;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:

	MainWindow();

public slots:


protected:

	virtual void closeEvent(QCloseEvent *pEvent);

private slots:

	void on_m_pActionOpen_triggered();
	void on_m_pActionProcess_triggered();
	void on_m_pActionCancel_triggered();
	void onThreadStarted();
	void onThreadFinished();
	void onThreadCanceled();

private:

	cv::Mat m_Image;
	WorkerThread *m_pThreadWork;
	bool m_bCanceled;
};

#endif // MAIN_WINDOW_H
