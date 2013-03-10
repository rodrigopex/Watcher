// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <qdebug.h>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
		QObject(app) {
	m_rotationSensor = new QRotationSensor();
	m_rotationSensor->setAlwaysOn(true);
	m_timer = new QTimer();
	m_timer->setInterval(200);
	m_timer->setSingleShot(false);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(readingGyro()));
	this->startWatch();
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_controller", this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	app->setScene(root);
}

bool isMoving(double * data, double * newData) {
	bool ret = false;
	for (int i = 0; i < 3; ++i) {
		if (abs(data[i] - newData[i]) > 2) {
			ret = true;
			break;
		}
	}
	return ret;
}

void ApplicationUI::startWatch() {
	m_timer->start();
	m_rotationSensor->start();
}

void ApplicationUI::stopWatch() {
	m_timer->stop();
	m_rotationSensor->stop();
}

void ApplicationUI::readingGyro() {
	QRotationReading * test = m_rotationSensor->reading();
	double newData[3] = { test->x(), test->y(), test->z() };
	if (isMoving(m_sensorData, newData)) {
		emit this->moving();
	}
	for (int i = 0; i < 3; ++i) {
		m_sensorData[i] = newData[i];
	}
}
