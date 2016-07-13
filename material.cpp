#include "material.h"

#include <QString>
#include <QVector3D>

class MaterialPrivate {

public:
    MaterialPrivate(){
    }

    QString Name;
    QVector3D Ambient;
    QVector3D Diffuse;
    QVector3D Specular;
    float Shininess;
};

Material::Material():
    m_d( new MaterialPrivate() ) {

}

Material::~Material(){
    delete m_d;
}

QString Material::name() const {
    return m_d->Name;
}

void Material::setName(const QString &newName) {
    m_d->Name = newName;
}

QVector3D Material::ambient() const {
    return m_d->Ambient;
}

void Material::setAmbient(const QVector3D &newAmbient) {
    m_d->Ambient = newAmbient;
}

QVector3D Material::diffuse() const {
    return m_d->Diffuse;
}

void Material::setDiffuse(const QVector3D &newDiffuse) {
    m_d->Diffuse = newDiffuse;
}

QVector3D Material::specular() const {
    return m_d->Specular;
}

void Material::setSpecular(const QVector3D &newSpecular) {
    m_d->Specular = newSpecular;
}

float Material::shininess() const {
    return m_d->Shininess;
}

void Material::setShininess(float newShininess) {
    m_d->Shininess = newShininess;
}
