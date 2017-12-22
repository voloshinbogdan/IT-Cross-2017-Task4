#include "worker-thread.h"
#include "main-window.h"

#include <assert.h>
#include <vector>


WorkerThread::WorkerThread(MainWindow *pWindow): m_pWindow(pWindow)
{

}



const cv::Mat *WorkerThread::getResultImage() const
{
	assert(isFinished());

	return m_ptrResult.data();
}



void WorkerThread::startLoadFile(const QString &rcFilePath)
{
	if (isRunning())
		return;

	m_nOperation = LoadFile;
	m_FilePath = rcFilePath;
	m_ptrInput.reset(new cv::Mat);
	QThread::start();
}



void WorkerThread::startProcessImage(const cv::Mat &rcImage)
{
	if (isRunning())
		return;

	m_nOperation = ProcessImage;
	m_ptrInput.reset(new cv::Mat(rcImage));
	QThread::start();
}



void WorkerThread::stop()
{
	requestInterruption();
}



void WorkerThread::run()
{
	switch (m_nOperation)
	{
	case LoadFile:
		*m_ptrInput = cv::imread(m_FilePath.toStdString(), CV_LOAD_IMAGE_COLOR);

		if (m_ptrInput->data)
			m_ptrResult.reset(new cv::Mat(*m_ptrInput));

		break;

	case ProcessImage:

		if (m_ptrInput)
		{
			m_ptrResult.reset(new cv::Mat(*m_ptrInput));
			
			cv::Mat gray;
			cv::cvtColor(*m_ptrResult, gray, cv::COLOR_BGR2GRAY);
			cv::medianBlur(gray, gray, 5);
			std::vector<cv::Vec3f> circles;
			cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1,
					 gray.rows/16, 
					 160, 80, 0, 0);

			for( size_t i = 0; i < circles.size(); i++ )
			{
				cv::Vec3i c = circles[i];
				cv::circle(*m_ptrResult, cv::Point(c[0], c[1]), c[2], cv::Scalar(0,0,255), 3, CV_AA);
			}

		} // if
		break;
	} // switch
}
