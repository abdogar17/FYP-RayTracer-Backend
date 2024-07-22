#ifndef FACTORY_METHODS_H
#define FACTORY_METHODS_H

#include <string>

class world;

std::shared_ptr<world> LoadScene(std::string fileName);


#endif
