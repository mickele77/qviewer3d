#ifndef MODELLOADER_H
#define MODELLOADER_H

class Node;

template <typename T> class QVector;
class QString;

class ModelLoaderPrivate;

class ModelLoader {
public:
    ModelLoader();

    bool load( const QString & pathToFile);
    void bufferData( QVector<float> **vertices, QVector<float> **normals,
                     QVector<unsigned int> **indices);

    Node * node();

private:
    ModelLoaderPrivate * m_d;
};

#endif // MODELLOADER_H
