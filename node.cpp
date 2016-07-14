#include "node.h"

#include "mesh.h"

#include <QMatrix4x4>
#include <QVector>
#include <QString>

class NodePrivate {
    NodePrivate(){

    }

    QString name;
    QMatrix4x4 transformation;
    QVector< Mesh * > meshes;
    QVector<Node> nodes;
};

Node::Node()
{

}
