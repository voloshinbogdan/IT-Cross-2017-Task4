#include "main-window.h"
#include "worker-thread.h"
#include <iostream>
MainWindow::MainWindow()
{
	setupUi(this);

	m_pAreaImage->setBackgroundRole(QPalette::Dark);
	m_pAreaImage->setWidgetResizable(true);
	setCentralWidget(m_pAreaImage);

	m_pAreaImage->addAction(m_pActionOpen);
	m_pAreaImage->addAction(m_pActionExit);

	m_pThreadWork = new WorkerThread(this);
	connect(
		m_pThreadWork, SIGNAL(started()),
		this, SLOT(onThreadStarted()));
	connect(
		m_pThreadWork, SIGNAL(finished()),
		this, SLOT(onThreadFinished()));
	connect(
		m_pThreadWork, SIGNAL(canceled()),
		this, SLOT(onThreadCanceled()));
} // MainWindow::MainWindow()


void MainWindow::closeEvent(QCloseEvent *pEvent)
{
	pEvent->accept();
	m_pThreadWork->stop();
}



void MainWindow::on_m_pActionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
		m_pThreadWork->startLoadFile(fileName);
}



void MainWindow::on_m_pActionProcess_triggered()
{
	m_pThreadWork->startProcessImage(m_Image);
}



void MainWindow::on_m_pActionCancel_triggered()
{
	m_pThreadWork->stop();
}



void MainWindow::onThreadStarted()
{
	m_pActionOpen->setEnabled(false);
	m_pActionProcess->setEnabled(false);
	m_pActionCancel->setEnabled(true);
	QApplication::setOverrideCursor(Qt::WaitCursor);

	m_bCanceled = false;

	statusBar()->showMessage("Process...");
}



void MainWindow::onThreadFinished()
{
	m_pActionOpen->setEnabled(true);
	m_pActionProcess->setEnabled(true);
	m_pActionCancel->setEnabled(false);
	QApplication::restoreOverrideCursor();

	const cv::Mat *pcImage = m_pThreadWork->getResultImage();
	if (pcImage)
	{
		m_Image = *pcImage;
		cv::Mat displayed;
		cvtColor(m_Image, displayed, CV_BGR2RGB);
		m_pLabelImage->setPixmap(QPixmap::fromImage(QImage(displayed.data, displayed.cols, displayed.rows, displayed.step, QImage::Format_RGB888)));
	}

	statusBar()->showMessage(
		m_bCanceled ? "Canceled" : "Finished");
}



void MainWindow::onThreadCanceled()
{
	m_bCanceled = true;
}
