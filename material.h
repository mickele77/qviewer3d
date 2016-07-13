#ifndef MATERIAL_H
#define MATERIAL_H


class QString;
class QVector3D;

class MaterialPrivate;

class Material {
public:
    Material();
    ~Material();

    QString name() const;
    void setName( const QString &newName );

    QVector3D ambient() const;
    void setAmbient( const QVector3D & newAmbient );

    QVector3D diffuse() const;
    void setDiffuse( const QVector3D & newDiffuse );

    QVector3D specular() const;
    void setSpecular( const QVector3D& newSpecular );

    float shininess() const;
    void setShininess( float newShininess );

private:
    MaterialPrivate * m_d;
};

#endif // MATERIAL_H
