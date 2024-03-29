#include "file_checks.h"
#include "compatible_checker.h"
#include "tileset_json_i.h"
#include <nlohmann/json.hpp>
#include <set>

constexpr char JSON_EXTENSION[] = ".json";

namespace {
    static int readSize(nlohmann::json& json_properties){
        return json_properties.at("size").get<int>();
    };

    static std::set<CompatibleType> readCompatibleTypes(nlohmann::json& json_properties){
        
        std::set<CompatibleType> compatible_types;
        auto json_compatible_types = json_properties.at("compatibilityTypes");
        for (auto json_s : json_compatible_types){
            CompatibleType compatible_type(json_s.get<std::string>());
            compatible_types.insert(compatible_type);
        }
        return compatible_types;
    }

    static Palette readPalette(nlohmann::json& json_properties, CompatibleChecker& compatible_checker){
        Palette palette;
        std::vector<CompatibleType> compatible_types;
        
        nlohmann::json json_palette = json_properties.at("palette");

        for (auto it = json_palette.begin(); it != json_palette.end(); ++it){

            nlohmann::json json_material = it.value();
            Material material(
                json_material.at("x"),
                json_material.at("y"),
                json_material.at("width"),
                json_material.at("height"));
            CompatibleType cmpt_tp(json_material.at("compatibility"));
            for (int i = 0; i < material.size(); i++){
                compatible_checker.putCompatible(CompatibleTile{material[i], cmpt_tp, cmpt_tp, cmpt_tp, cmpt_tp});
            }

            palette.addMaterial(it.key(), material);
        }
        return palette;
    }
}

TilesetProperties load(const char filename[])
{
    checkFileExtensionError(filename, JSON_EXTENSION);

    std::ifstream file(filename);
    checkFileIssues(file);

    nlohmann::json json_properties = nlohmann::json::parse(file);

    int size = readSize(json_properties);
    std::set<CompatibleType> compatible_types = readCompatibleTypes(json_properties);

    CompatibleChecker compatible_cheker(size, compatible_types);
    Palette palette = readPalette(json_properties, compatible_cheker);
    file.close();

    return TilesetProperties{palette, compatible_cheker};
}
