#ifndef WORKER_THREAD_H 
#define WORKER_THREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>

class MainWindow;

class WorkerThread : public QThread
{
	Q_OBJECT

public:

	WorkerThread(MainWindow *pWindow);
	~WorkerThread() = default;

	const cv::Mat *getResultImage() const;

	void startLoadFile(const QString &rcFilePath);
	void startProcessImage(const cv::Mat &rcImage);
	void stop();

signals:

	void canceled();

private:

	enum Operation
	{
		LoadFile,
		ProcessImage
	};

	MainWindow *m_pWindow;
	Operation m_nOperation;
	QString m_FilePath;
	QScopedPointer<cv::Mat> m_ptrInput, m_ptrResult;

	virtual void run();
};

#endif // WORKER_THREAD_H

