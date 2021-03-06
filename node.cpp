#include "node.h"

#include "mesh.h"

#include <QMatrix4x4>
#include <QVector>
#include <QString>

class NodePrivate {
public:
    NodePrivate(){
    }
    ~NodePrivate(){
    }
    QString name;
    QMatrix4x4 transformation;
    QVector<Mesh *> meshes;
    QVector<Node *> nodes;
};

Node::Node():
    m_d(new NodePrivate() ){

}

Node::~Node() {
    delete m_d;
}

QString Node::name() {
    return m_d->name;
}

void Node::setName(const QString &newName) {
    m_d->name = newName;
}

QMatrix4x4 Node::transformation() {
    return m_d->transformation;
}

void Node::setTransformation(const QMatrix4x4 &newTransformation) {
    m_d->transformation = newTransformation;
}

void Node::resizeMeshes( int newSize ) {
    int numToAdd = newSize - m_d->meshes.size();
    if( numToAdd > 0 ){
        for( int i=0; i < numToAdd; ++i ){
            m_d->meshes.append( new Mesh() );
        }
    } else if( numToAdd < 0 ){
        numToAdd *= -1;
        for( int i=0; i < numToAdd; ++i ){
            delete m_d->meshes.takeLast();
        }
    }
}
