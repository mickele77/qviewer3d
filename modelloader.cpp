#include "modelloader.h"

#include "material.h"
#include "mesh.h"
#include "node.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <QString>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector>

class ModelLoaderPrivate {
public:
    Material * processMaterial(aiMaterial *material){
        Material * mater(new Material);

        aiString mname;
        material->Get(AI_MATKEY_NAME, mname);
        if (mname.length > 0)
            mater->setName( mname.C_Str() );

        int shadingModel;
        material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);

        if (shadingModel != aiShadingMode_Phong && shadingModel != aiShadingMode_Gouraud) {
            qDebug() << "This mesh's shading model is not implemented in this loader, setting to default material";
            mater->setName( "DefaultMaterial" );
        } else {
            aiColor3D dif(0.f,0.f,0.f);
            aiColor3D amb(0.f,0.f,0.f);
            aiColor3D spec(0.f,0.f,0.f);
            float shine = 0.0;

            material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
            material->Get(AI_MATKEY_COLOR_DIFFUSE, dif);
            material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
            material->Get(AI_MATKEY_SHININESS, shine);

            mater->setAmbient( QVector3D(amb.r, amb.g, amb.b) );
            mater->setDiffuse( QVector3D(dif.r, dif.g, dif.b) );
            mater->setSpecular( QVector3D(spec.r, spec.g, spec.b) );
            mater->setShininess( shine );

            mater->setAmbient( mater->ambient() *.2 );
            if (mater->shininess() == 0.0)
                mater->setShininess( 30.0 );
        }

        return mater;
    }

    Mesh * processMesh(aiMesh * mesh) {
        Mesh * newMesh(new Mesh);

        newMesh->setName( mesh->mName.length != 0 ? mesh->mName.C_Str() : "" );
        newMesh->setIndexOffset( indices.size() );
        unsigned int indexCountBefore = indices.size();
        int vertindexoffset = vertices.size()/3;

        // Get Vertices
        if (mesh->mNumVertices > 0) {
            for (uint ii = 0; ii < mesh->mNumVertices; ++ii) {
                aiVector3D &vec = mesh->mVertices[ii];

                vertices.push_back(vec.x);
                vertices.push_back(vec.y);
                vertices.push_back(vec.z);
            }
        }

        // Get Normals
        if (mesh->HasNormals()) {
            for (uint ii = 0; ii < mesh->mNumVertices; ++ii) {
                aiVector3D &vec = mesh->mNormals[ii];
                normals.push_back(vec.x);
                normals.push_back(vec.y);
                normals.push_back(vec.z);
            }
        }

        // Get mesh indexes
        for (uint t = 0; t < mesh->mNumFaces; ++t) {
            aiFace* face = &mesh->mFaces[t];
            if (face->mNumIndices != 3) {
                qDebug() << "Warning: Mesh face with not exactly 3 indices, ignoring this primitive.";
                continue;
            }

            indices.push_back(face->mIndices[0]+vertindexoffset);
            indices.push_back(face->mIndices[1]+vertindexoffset);
            indices.push_back(face->mIndices[2]+vertindexoffset);
        }

        newMesh->setIndexCount( indices.size() - indexCountBefore );
        newMesh->setMaterial( materials.at(mesh->mMaterialIndex) );

        return newMesh;
    }

    void processNode(const aiScene *scene, aiNode *node, Node *parentNode, Node &newNode){
        newNode.setName( node->mName.length != 0 ? node->mName.C_Str() : "" );

        newNode.setTransformation( QMatrix4x4(node->mTransformation[0]) );

        newNode.resizeMeshes(node->mNumMeshes);
        for (uint imesh = 0; imesh < node->mNumMeshes; ++imesh) {
            QSharedPointer<Mesh> mesh = meshes[node->mMeshes[imesh]];
            newNode.meshes[imesh] = mesh;
        }

        for (uint ich = 0; ich < node->mNumChildren; ++ich) {
            newNode.nodes.push_back(Node());
            processNode(scene, node->mChildren[ich], parentNode, newNode.nodes[ich]);
        }
    }

    void transformToUnitCoordinates();
    void findObjectDimensions(Node *node, QMatrix4x4 transformation, QVector3D &minDimension, QVector3D &maxDimension);

    QVector<float> vertices;
    QVector<float> normals;
    QVector<unsigned int> indices;

    QVector< Material * > materials;
    QVector< Mesh * > meshes;
    Node * rootNode;
};

ModelLoader::ModelLoader():
    m_d( new ModelLoaderPrivate() ) {

}

bool ModelLoader::load(const QString &pathToFile) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pathToFile.toStdString(),
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType
                                             );

    if (!scene) {
        qDebug() << "Error loading file: (assimp:) " << importer.GetErrorString();
        return false;
    }

    // Loading Materials
    if (scene->HasMaterials()) {
        for (unsigned int ii = 0; ii < scene->mNumMaterials; ++ii) {
            Material * mat = m_d->processMaterial(scene->mMaterials[ii]);
            m_d->materials.push_back(mat);
        }
    }

    // Loading Meshes
    if (scene->HasMeshes()) {
        for (unsigned int ii = 0; ii < scene->mNumMeshes; ++ii) {
            m_d->meshes.push_back( m_d->processMesh(scene->mMeshes[ii]) );
        }
    } else {
        qDebug() << "Error: No meshes found";
        return false;
    }

    // Loading Nodes
    if (scene->mRootNode != NULL) {
        Node *rootNode = new Node;
        m_d->processNode(scene, scene->mRootNode, 0, *rootNode);
        m_d->rootNode.reset(rootNode);
    } else {
        qDebug() << "Error loading model";
        return false;
    }

    return true;
}

void ModelLoader::bufferData(QVector<float> **vertices, QVector<float> **normals, QVector<unsigned int> **indices) {

}

Node *ModelLoader::node() {
    return m_d->rootNode;
}
