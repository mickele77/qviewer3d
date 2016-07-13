#ifndef LIGHT_H
#define LIGHT_H

class QVector3D;
class QVector4D;

class LightPrivate;

class Light {
public:
    Light();
    ~Light();

    QVector4D position() const;
    void setPosition(const QVector4D &newPosition);

    QVector3D intensity() const;
    void setIntensity(const QVector3D &newIntensity);

private:
    LightPrivate * m_d;
};

#endif // LIGHT_H
