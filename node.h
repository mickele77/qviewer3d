#ifndef NODE_H
#define NODE_H

class QMatrix4x4;
class QString;

class NodePrivate;

class Node
{
public:
    Node();
    ~Node();

    QString name();
    void setName( const QString & newName );

    QMatrix4x4 transformation();
    void setTransformation( const QMatrix4x4 & newTransformation );

    void resizeMeshes(int newSize);
private:
    NodePrivate * m_d;
};

#endif // NODE_H
