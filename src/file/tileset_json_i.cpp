#include "tileset_json_i.h"
#include "file_checks.h"
#include <nlohmann/json.hpp>

constexpr char JSON_EXTENSION[] = ".json";

TilesetProperties load(const char filename[])
{
    checkFileExtensionError(filename, JSON_EXTENSION);

    std::ifstream file(filename);
    checkFileIssues(file);

    nlohmann::json json_properties = nlohmann::json::parse(file);

    TilesetProperties tilesetProperties;
    
    Palette palette = readPalette(json_properties);

    return TilesetProperties{palette};
}

static Palette readPalette(nlohmann::json& json_properties){
    Palette palette;
    
    nlohmann::json json_palette = json_properties.at("palette");

    for (auto it = json_palette.begin(); it != json_palette.end(); ++it){

        nlohmann::json json_material = it.value();
        Material material(
            json_material.at("x"),
            json_material.at("y"),
            json_material.at("width"),
            json_material.at("height"));

        palette.addMaterial(it.key(), material);
    }

    return palette;
}