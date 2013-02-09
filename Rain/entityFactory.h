/*
geometry data, i dont know what else it will have
*/

#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <GL/glew.h>
// #include "include/Artemis-Cpp/Component.h"
#include "Artemis-Cpp/Artemis.h"
#include <vector>
#include "types.h"
#include "geoManager.h"
#include <string>
#include "normals.h"
#include "geoBuilder.h"


using namespace std;

class EntityFactory : public artemis::Component {
    artemis::EntityManager* em;
    GeoManager geoManager;
public:
    EntityFactory(artemis::EntityManager* em, GeoManager& geoManager);
    ~EntityFactory();
    artemis::Entity& makePlaneEntity();
};

#endif