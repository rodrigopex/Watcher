// Default empty project template
#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <qrotationsensor.h>
#include <qtimer.h>

using namespace QtMobility;
namespace bb { namespace cascades { class Application; }}

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() {}
    public slots:
    void readingGyro();
    Q_INVOKABLE void startWatch();
    Q_INVOKABLE void stopWatch();
signals:
	void moving();
private:
    QRotationSensor * m_rotationSensor;
    QTimer * m_timer;
    double m_sensorData[3];
};


#endif /* ApplicationUI_HPP_ */
