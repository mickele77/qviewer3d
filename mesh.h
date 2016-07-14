#ifndef MESH_H
#define MESH_H

class Material;

class QString;

class MeshPrivate;

class Mesh {
public:
    Mesh();
    ~Mesh();

    QString name();
    void setName( const QString & newName );

    unsigned int indexCount();
    void setIndexCount(unsigned int newIndexCount);

    unsigned int indexOffset();
    void setIndexOffset(unsigned int newIndexOffset);

    Material *material();
    void setMaterial(Material *newMaterial);
private:
    MeshPrivate * m_d;
};

#endif // MESH_H
