//
// Created by marco on 02.05.21.
//

#include <iostream>
#include <cassert>  //assert
#include <stdlib.h>  //rand()

#include "Die.h"

/** @brief Constructor, only color is needed
 *  @param color color of the die
 */
Die::Die(Color color):color(color){
    
    assert(color == green || color == yellow || color == red);

    //define faces distribution of the die (0:brain, 1:shotgun, 2:footprint) as in enum Faces in Die.h
    int faces_dist[3];
    
    if (color == green){
        faces_dist[0] = 3;
        faces_dist[1] = 1;
        faces_dist[2] = 2;
    }
    else if (color == yellow){
        faces_dist[0] = 2;
        faces_dist[1] = 2;
        faces_dist[2] = 2;
    }
    else if (color == red){
        faces_dist[0] = 1;
        faces_dist[1] = 3;
        faces_dist[2] = 2;
    }
    
    //add brains
    for (int i = 0; i < faces_dist[0]; i++){
        faces.push_back(brain);
    }
    //add shotguns
    for (int i = 0; i < faces_dist[1]; i++){
        faces.push_back(shotgun);
    }
    //add footprints
    for (int i = 0; i < faces_dist[2]; i++){
        faces.push_back(footprint);
    }
}


/** @brief returns the die's color
 */
Color Die::get_color(){
    return color;
}


/** @brief returns a random face of the die's faces
 */
Face Die::throw_die(){
    int face_at = rand() % 6;
    return faces.at(face_at);
}


