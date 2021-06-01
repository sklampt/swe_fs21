//
// Created by marco on 02.05.21.
//

#include <iostream>
#include <cassert>  //assert
#include <ctime>

#include "Die.h"

/** @brief Constructor, only color is needed
 *  @param color color of the die
 */
Die::Die(Color color) : unique_serializable(), _color(color) {
    // Unrolled dice has no face
    _face = Face::undefined;
    _faces = Die::generateFaces(color);
}

Die::Die(std::string id, Color color, Face face) :
        unique_serializable(id), _color(color), _face(face) {
    _faces = Die::generateFaces(color);
}

/** @brief returns vector of Face variables that represent the side
 * @param color
 */
std::vector<Face> Die::generateFaces(Color color) {
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

    std::vector<Face> faces;
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

    return faces;
}

/** @brief returns the die's color
 */
Color Die::get_color(){
    return _color;
}

std::string Die::get_color_as_string() {
    if (_color == Color::green) return "green";
    else if (_color == Color::yellow) return "yellow";
    else if (_color == Color::red) return "red";
    else return "undefined";
}

/** @brief returns the die's face or undefined if throw_die() has not been called yet
 */
Face Die::get_face() {
    return _face;
}

std::string Die::get_face_as_string() {
    if (_face == Face::brain) return "brain";
    else if (_face == Face::footprint) return "footprint";
    else if (_face == Face::shotgun) return "shotgun";
    else return "undefined";
}



/** @brief returns a random face of the die's faces
 */
Face Die::throw_die(){
    srand(time(0));
    int face_at = rand() % 6; // TODO: Check if compiles and works
    _face = _faces.at(face_at);
    return _face;
}

Die *Die::from_json(const rapidjson::Value &json) {

    // Convert color string to Enum::Color value
    Color color_val;
    std::string json_color = json["color"].GetString();

    if (json_color == "green") color_val = Color::green;
    else if (json_color == "yellow") color_val = Color::yellow;
    else if (json_color == "red") color_val = Color::red;

    // Convert face string to Enum::Face value
    Face face_val;
    std::string json_face = json["face"].GetString();
    if (json_face == "undefined") face_val = Face::undefined;
    else if (json_face == "brain") face_val = Face::brain;
    else if (json_face == "footprint") face_val = Face::footprint;
    else if (json_face == "shotgun") face_val = Face::shotgun;

    return new Die(
            json["id"].GetString(),
            color_val,
            face_val
            );
}

void Die::write_into_json(rapidjson::Value &json, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    std::string color_val;
    if (_color == Color::green) color_val = "green";
    else if (_color == Color::yellow) color_val = "yellow";
    else if (_color == Color::red) color_val = "red";

    std::string face_val;
    if (_face == Face::undefined) face_val = "undefined";
    else if (_face == Face::brain) face_val = "brain";
    else if (_face == Face::footprint) face_val = "footprint";
    else if (_face == Face::shotgun) face_val = "shotgun";


    json.AddMember("color", color_val, allocator);
    json.AddMember("face",face_val, allocator);
}

