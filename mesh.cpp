#include "mesh.h"

#include "material.h"
#include <QString>

class MeshPrivate {
    MeshPrivate(){

    }

    QString name;
    unsigned int indexCount;
    unsigned int indexOffset;
    Material * material;
};

Mesh::Mesh()
{

}
