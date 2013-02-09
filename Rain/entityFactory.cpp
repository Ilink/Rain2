#include "entityFactory.h"

EntityFactory::EntityFactory(artemis::EntityManager* em, GeoManager& geoManager){
    this->em = em;
    this->geoManager = geoManager;
}

EntityFactory::~EntityFactory(){

}

artemis::Entity& EntityFactory::makePlaneEntity(){
    artemis::Entity& planeEntity = em->create();

    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makePlane(5,5, planeVerts, planeVertIndex);
    calcFaceNormals(planeVerts, planeVertIndex);

    planeEntity.addComponent(geoManager.create(planeVerts, planeVertIndex));

    return planeEntity;
}
