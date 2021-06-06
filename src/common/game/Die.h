//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_DIE_H
#define ZOMBIEDICE_DIE_H

#include <vector>
#include <string>
#include <common/serialization/unique_serializable.h>

// three colors of dice
enum Color {green, yellow, red};
// three faces present on dice
enum Face {brain, shotgun, footprint, undefined};

class Die: public unique_serializable {
    private:
        std::vector<Face> _faces;
        Color _color;
        Face _face;

        // Private constructor for deserialization
        Die(std::string id, Color color, Face face);
    
    public:
        explicit Die(Color color);

        Color get_color();
        std::string get_color_as_string();
        Face get_face();
        std::string get_face_as_string();


        Face throw_die();

        static Die *from_json(const rapidjson::Value& json);
        virtual void write_into_json(rapidjson::Value& json,
                                     rapidjson::Document::AllocatorType& allocator
        ) const override;

    ;

    std::vector<Face> generateFaces(Color color);
};


#endif //ZOMBIEDICE_DIE_H
