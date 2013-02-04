#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

class PositionComponent : public artemis::Component {
public:
    Position pos;

    PositionComponent(Position pos){
        this->pos = pos;
    };

    ~PositionComponent(){

    };
};

#endif