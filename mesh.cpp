#include "mesh.h"

#include "material.h"
#include <QString>

class MeshPrivate {
public:
    MeshPrivate(){
    }
    ~MeshPrivate(){
    }

    QString name;
    unsigned int indexCount;
    unsigned int indexOffset;
    Material * material;
};

Mesh::Mesh():
    m_d(new MeshPrivate() ){

}

Mesh::~Mesh() {
    delete m_d;
}

QString Mesh::name() {
    return m_d->name;
}

void Mesh::setName( const QString & newName ) {
    m_d->name = newName;
}

unsigned int Mesh::indexCount(){
    return m_d->indexCount;
}

void Mesh::setIndexCount( unsigned int newIndexCount ){
    m_d->indexCount = newIndexCount;
}

unsigned int Mesh::indexOffset(){
    return m_d->indexOffset;
}

void Mesh::setIndexOffset( unsigned int newIndexOffset ){
    m_d->indexOffset = newIndexOffset;
}

Material * Mesh::material(){
    return m_d->material;
}

void Mesh::setMaterial( Material * newMaterial ){
    m_d->material = newMaterial;
}
