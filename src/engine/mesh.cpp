
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include "mesh.h"
#include "../3rdParty/ObjLoader/OBJ_Loader.h"

using namespace std;
//using namespace objl;

mesh::mesh(string file, vec3 p, vec3 s, vec3 r, shared_ptr<material> mat){
    position = p;
    scale = s;
    rotation = r;
    material_ptr = mat;
    fileName = file;
}

bool mesh::load(string fileName){

    objl::Loader loader;

	// Load .obj File
	bool loadout = loader.LoadFile(fileName);
    if (!loadout)
	{
        cout << "Failed to open: " << fileName << endl;
        return false;
    }
    else{
        cout << "Success opening: " << fileName << endl;

		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh pmesh = loader.LoadedMeshes[i];

            glm::mat4 T = glm::translate<float>(glm::mat4(1.0f), glm::vec3(position.x(),position.y(),position.z()));

            glm::mat4 RX = glm::rotate<float>(glm::mat4(1.0f), rotation.x(), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 RY = glm::rotate<float>(glm::mat4(1.0f), rotation.y(), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 RZ = glm::rotate<float>(glm::mat4(1.0f), rotation.z(), glm::vec3(0.0f, 0.0f, 1.0f));

            //glm::mat4 R = glm::rotate(glm::mat4(1.0f), angle * M_PI / 180.0, glm::vec3(rotation.x(),rotation.y(),rotation.z()));
            glm::mat4 S = glm::scale<float>(glm::mat4(1.0f), glm::vec3(scale.x(),scale.y(),scale.z()));
            glm::mat4 Model = T*RX*RY*RZ*S;

            for(int j = 0; j < pmesh.Vertices.size(); j+=3){
                glm::vec3 gv0(pmesh.Vertices[j].Position.X, pmesh.Vertices[j].Position.Y, pmesh.Vertices[j].Position.Z);
                glm::vec4 v0 = Model * glm::vec4(gv0, 1);
                glm::vec3 gv1(pmesh.Vertices[j+1].Position.X, pmesh.Vertices[j+1].Position.Y, pmesh.Vertices[j+1].Position.Z);
                glm::vec4 v1 = Model * glm::vec4(gv1, 1);
                glm::vec3 gv2(pmesh.Vertices[j+2].Position.X, pmesh.Vertices[j+2].Position.Y, pmesh.Vertices[j+2].Position.Z);
                glm::vec4 v2 = Model * glm::vec4(gv2, 1);

                triangleList.push_back(triangle(vec3(v0.x, v0.y, v0.z), 
                                                vec3(v1.x, v1.y, v1.z), 
                                                vec3(v2.x, v2.y, v2.z), 
                                                this->material_ptr));
            }

        }
        
        return true;
    }
    
}

bool mesh::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    
    for (int i = 0; i < triangleList.size(); i++){
        if(triangleList[i].hit(r,t_min,t_max,rec)){
            return true;
        }
    }
    return false;
}

