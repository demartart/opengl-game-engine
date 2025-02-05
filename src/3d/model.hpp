#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "mesh.hpp"
#include "../rendering/shader.hpp"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    Model(const std::string &path);

    void Draw(Shader &shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;

    void LoadModel(const std::string &path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type);
};


#endif