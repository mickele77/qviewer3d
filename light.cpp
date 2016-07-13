#include "light.h"

#include <QVector3D>
#include <QVector4D>

class LightPrivate {
public:
    LightPrivate() {

    }

    QVector4D Position;
    QVector3D Intensity;
};

Light::Light() :
    m_d( new LightPrivate() ){
}

Light::~Light(){
    delete m_d;
}

QVector4D Light::position() const {
    return m_d->Position;
}

void Light::setPosition( const QVector4D & newPosition ){
    m_d->Position = newPosition;
}

QVector3D Light::intensity() const {
    return m_d->Intensity;
}
void Light::setIntensity( const QVector3D & newIntensity ) {
    m_d->Intensity = newIntensity;
}
