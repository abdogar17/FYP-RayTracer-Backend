
#include <iostream>
#include "factory_methods.h"
#include "../../defs.h"
#include "../world.h"
#include "../config.h"
#include "../camera.h"
#include "../sun.h"
#include "../sphere.h"
#include "../mesh.h"
#include "../lambertian.h"
#include "../metal.h"
#include "../emissive.h"

using namespace std;
using namespace tinyxml2;

shared_ptr<config> LoadConfig(XMLElement * configElem);
shared_ptr<camera> LoadCamera(XMLElement * cameraElem, float aspect_ratio);
shared_ptr<sun> LoadSun(XMLElement * lightsElem);
vector< shared_ptr<hittable> > LoadObjects(XMLElement * objectsElem);
shared_ptr<hittable> LoadSphere(XMLElement * sphereElem);
shared_ptr<hittable> LoadTriangle(XMLElement * triangleElem);
shared_ptr<hittable> LoadMesh(XMLElement * meshElem);
shared_ptr<material> LoadMaterial(string name);

shared_ptr<world> LoadScene(string fileName){
    XMLDocument doc;
    XMLError xmlErr = doc.LoadFile( fileName.c_str() );
    if(xmlErr != XML_SUCCESS)
    {
        cout << "Error parsing " << fileName << " -- error code: " << xmlErr;
        if(xmlErr == XML_ERROR_MISMATCHED_ELEMENT){
            cout << " -- Mismatched Element " <<  endl;
        }
        return shared_ptr<world>();
    }
    
    shared_ptr<world> pworld = make_shared<world>();

    XMLNode * itemContainer = doc.FirstChildElement();
    XMLElement * configElem = itemContainer->FirstChildElement("Config");
    pworld->pconfig = LoadConfig(configElem);

    XMLElement * cameraElem = configElem->NextSiblingElement("Camera");
    pworld->pcamera = LoadCamera(cameraElem, pworld->pconfig->ASPECT_RATIO);

    XMLElement * lightsElem = configElem->NextSiblingElement("Lights");
    pworld->psun = LoadSun(lightsElem);

    XMLElement * objectsElem = configElem->NextSiblingElement("Objects");
    pworld->objects = LoadObjects(objectsElem);

    return pworld;
}

shared_ptr<config> LoadConfig(XMLElement * configElem){

    XMLElement * widthElem = configElem->FirstChildElement("Width");
    int width = atoi(widthElem->Attribute("value"));
    XMLElement * aspectElem = widthElem->NextSiblingElement("Aspect_ratio");
    float aspect_ratio = atof(aspectElem->Attribute("value"));
    XMLElement * samplesElem = widthElem->NextSiblingElement("Samples_Per_Pixel");
    int samples = atoi(samplesElem->Attribute("value"));
    XMLElement * depthElem = widthElem->NextSiblingElement("Max_Depth");
    int depth = atoi(depthElem->Attribute("value"));

    shared_ptr<config> pconfig = make_shared<config>();
    pconfig->ASPECT_RATIO = aspect_ratio;
    pconfig->IMAGE_WIDTH = width;
    pconfig->IMAGE_HEIGHT = static_cast<int>(width / aspect_ratio);
    pconfig->SAMPLES_PER_PIXEL = samples;
    pconfig->MAX_DEPTH = depth;

    return pconfig;
}

shared_ptr<camera> LoadCamera(XMLElement * cameraElem, float aspect_ratio){

    XMLElement * vpWidthElem = cameraElem->FirstChildElement("Viewport_Width");
    float vpWidth = atof(vpWidthElem->Attribute("value"));
    
    XMLElement * focalElem = vpWidthElem->NextSiblingElement("Focal_Length");
    float focal_length = atof(focalElem->Attribute("value"));

    XMLElement * lookFromElem = vpWidthElem->NextSiblingElement("Look_From");
    float x,y,z;
    x = atof(lookFromElem->Attribute("x"));
    y = atof(lookFromElem->Attribute("y"));
    z = atof(lookFromElem->Attribute("z"));
    vec3 lookFrom(x,y,z);

    XMLElement * lookAtElem = vpWidthElem->NextSiblingElement("Look_at");
    x = atof(lookAtElem->Attribute("x"));
    y = atof(lookAtElem->Attribute("y"));
    z = atof(lookAtElem->Attribute("z"));
    vec3 lookAt(x,y,z);

    XMLElement * upElem = vpWidthElem->NextSiblingElement("Up");
    x = atof(upElem->Attribute("x"));
    y = atof(upElem->Attribute("y"));
    z = atof(upElem->Attribute("z"));
    vec3 up(x,y,z);

    XMLElement * fovElem = vpWidthElem->NextSiblingElement("FOV");
    float fov = atof(fovElem->Attribute("angle"));

    //XMLElement * aspectElem = vpWidthElem->NextSiblingElement("Aspect_ratio");
    //float aspectRatio = atof(aspectElem->Attribute("value"));

    shared_ptr<camera> pcamera = make_shared<camera>(lookFrom, lookAt, up, fov, aspect_ratio);
    pcamera->VIEWPORT_WIDTH = vpWidth;
    pcamera->VIEWPORT_HEIGHT = vpWidth / aspect_ratio;
    pcamera->ASPECT_RATIO = aspect_ratio;
    pcamera->FOCAL_LENGTH = focal_length;

    return pcamera;

}

shared_ptr<sun> LoadSun(XMLElement * lightsElem){
    
    XMLElement * sunElem = lightsElem->FirstChildElement("Sun");
    XMLElement * dirElem = sunElem->FirstChildElement("Direction");

    float x,y,z;
    x = atof(dirElem->Attribute("x"));
    y = atof(dirElem->Attribute("y"));
    z = atof(dirElem->Attribute("z"));
    vec3 dir(x,y,z);

    XMLElement * intensityElem = dirElem->NextSiblingElement("Intensity");
    float intensity = atof(intensityElem->Attribute("value"));

    float r,g,b;
    XMLElement * colorElem = dirElem->NextSiblingElement("Color");
    r = atof(colorElem->Attribute("r"));
    g = atof(colorElem->Attribute("g"));
    b = atof(colorElem->Attribute("b"));
    vec3 color(r,g,b);

    shared_ptr<sun> psun = make_shared<sun>();
    psun->direction = dir;
    psun->sunColor = color;

    return psun;

}

vector< shared_ptr<hittable> > LoadObjects(XMLElement * objectsElem){

    vector< shared_ptr<hittable> > list;

    XMLElement * item = objectsElem->FirstChildElement();
    while(item){
        string type = item->Name();
        if(type == "Sphere"){
            list.push_back(LoadSphere(item));
        }
        else if(type == "Mesh"){
            list.push_back(LoadMesh(item));
        }
        else if(type == "Triangle"){
            list.push_back(LoadTriangle(item));
        }
        
        item = item->NextSiblingElement();
    }

    return list;

}

shared_ptr<hittable> LoadSphere(XMLElement * sphereElem){
    string name = sphereElem->Name();

    XMLElement * radiusElem = sphereElem->FirstChildElement("Radius");
    double radius = atof(radiusElem->Attribute("value"));

    XMLElement * posElem = radiusElem->NextSiblingElement("Position");
    float x,y,z;
    x = atof(posElem->Attribute("x"));
    y = atof(posElem->Attribute("y"));
    z = atof(posElem->Attribute("z"));
    vec3 center(x,y,z);

    XMLElement * scaleElem = radiusElem->NextSiblingElement("Scale");
    x = atof(scaleElem->Attribute("x"));
    y = atof(scaleElem->Attribute("y"));
    z = atof(scaleElem->Attribute("z"));
    vec3 scale(x,y,z);

    XMLElement * rotateElem = radiusElem->NextSiblingElement("Rotation");
    x = atof(rotateElem->Attribute("x"));
    y = atof(rotateElem->Attribute("y"));
    z = atof(rotateElem->Attribute("z"));
    vec3 rotation(x,y,z);

    XMLElement * materialElem = radiusElem->NextSiblingElement("Material");
    string materialName = materialElem->Attribute("name");

    auto material = LoadMaterial(materialName);
    shared_ptr<hittable> psphere = make_shared<sphere>(center, radius, material);

    return psphere;
}

shared_ptr<hittable> LoadTriangle(XMLElement * triangleElem){
    string name = triangleElem->Name();

    float x,y,z;
    XMLElement * v0Elem = triangleElem->FirstChildElement("V0");
    x = atof(v0Elem->Attribute("x"));
    y = atof(v0Elem->Attribute("y"));
    z = atof(v0Elem->Attribute("z"));
    point3 v0(x,y,z);

    XMLElement * v1Elem = v0Elem->NextSiblingElement("V1");
    x = atof(v1Elem->Attribute("x"));
    y = atof(v1Elem->Attribute("y"));
    z = atof(v1Elem->Attribute("z"));
    point3 v1(x,y,z);

    XMLElement * v2Elem = v0Elem->NextSiblingElement("V2");
    x = atof(v2Elem->Attribute("x"));
    y = atof(v2Elem->Attribute("y"));
    z = atof(v2Elem->Attribute("z"));
    point3 v2(x,y,z);

    XMLElement * materialElem = v0Elem->NextSiblingElement("Material");
    string materialName = materialElem->Attribute("name");
    auto material = LoadMaterial(materialName);

    shared_ptr<hittable> ptriangle = make_shared<triangle>(vec3(-1, 1, -3), vec3( 1, 1, -3), vec3( 0,  2, -3), material);
    return ptriangle;
}

shared_ptr<hittable> LoadMesh(XMLElement * meshElem){
    string name = meshElem->Name();

    XMLElement * posElem = meshElem->FirstChildElement("Position");
    float x,y,z;
    x = atof(posElem->Attribute("x"));
    y = atof(posElem->Attribute("y"));
    z = atof(posElem->Attribute("z"));
    vec3 position(x,y,z);

    XMLElement * scaleElem = posElem->NextSiblingElement("Scale");
    x = atof(scaleElem->Attribute("x"));
    y = atof(scaleElem->Attribute("y"));
    z = atof(scaleElem->Attribute("z"));
    vec3 scale(x,y,z);

    XMLElement * rotateElem = posElem->NextSiblingElement("Rotation");
    x = atof(rotateElem->Attribute("x"));
    y = atof(rotateElem->Attribute("y"));
    z = atof(rotateElem->Attribute("z"));
    vec3 rotation(x,y,z);

    XMLElement * materialElem = posElem->NextSiblingElement("Material");
    string materialName = materialElem->Attribute("name");
    auto material = LoadMaterial(materialName);

    XMLElement * fileElem = posElem->NextSiblingElement("File");
    string fileName = fileElem->Attribute("name");

    shared_ptr<hittable> pmesh = make_shared<mesh>(fileName, position, scale, rotation, material);
    
    shared_ptr<mesh> derived = dynamic_pointer_cast<mesh> (pmesh);
    if(derived->load(fileName)){
        return pmesh;
    }

    return shared_ptr<hittable>();
}

shared_ptr<material> LoadMaterial(string name){
    shared_ptr<material> pmaterial;
    
    if(name == "ground"){
        pmaterial = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    }
    else if(name == "mattBrown"){
        pmaterial = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    }
    else if(name == "fuzzySilver"){
        pmaterial = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    }else if(name == "shinyGold"){
        pmaterial = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    }
    else if(name == "emissive"){
        pmaterial = make_shared<emissive>(color(1.0, 1.0, 1.0));
    }

    return pmaterial;
}