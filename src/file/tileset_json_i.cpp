#include "file_checks.h"
#include "compatible_checker.h"
#include "tileset_json_i.h"
#include "block_placer.h"
#include <windows.h>
#include <nlohmann/json.hpp>
#include <set>
#include <iostream>

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

    static Palette readPalette(nlohmann::json& json_properties, CompatibleChecker* compatible_checker){
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
            CompatibleType compatible_type(json_material.at("compatibility"));
            for (int i = 0; i < material.size(); i++){
                compatible_checker->putCompatible(CompatibleTile{material[i], compatible_type});
            }

            palette.addMaterial(it.key(), material);
        }
        return palette;
    }
    static BlockSet readBlocks(nlohmann::json& json_properties, CompatibleChecker* compatible_checker){
        std::map<std::string, std::vector<Block>> blocks;
        nlohmann::json json_blocks = json_properties.at("blocks");         

        for (auto it = json_blocks.begin(); it != json_blocks.end(); it++){
            std::vector<Block> temp_blocks;
            nlohmann::json json_block_type = it.value();

            for (auto json_block : json_block_type){
                temp_blocks.push_back(Block(
                    json_block.at("x"),
                    json_block.at("y"),
                    json_block.at("width"),
                    json_block.at("height")
                ));
                std::vector<std::string> compatibility_up = json_block.at("compatibility_up");
                std::vector<std::string> compatibility_left = json_block.at("compatibility_left");
                std::vector<std::string> compatibility_right = json_block.at("compatibility_right");
                std::vector<std::string> compatibility_bottom = json_block.at("compatibility_bottom");
                Block& block = temp_blocks[temp_blocks.size()-1];

                if (block.getWidth() != compatibility_up.size() || block.getWidth() != compatibility_bottom.size())
                    throw std::runtime_error("Block size doesn't fit its compatible_type size!");
                    
                for (int y = 0; y < block.getHeight(); y++){
                    for (int x = 0; x < block.getWidth(); x++){
                        CompatibleTile temp_compatible(block.getMatrix()[y][x], CompatibleType::null);
                        if (y != 0 && x != 0 && y != block.getHeight()-1 && x != block.getWidth()-1){
                            continue;
                        }
                        if (y == 0)
                            temp_compatible.top = compatibility_up[x];
                        if (y == block.getHeight()-1)
                            temp_compatible.bottom = compatibility_bottom[x];
                        if (x == 0)
                            temp_compatible.left = compatibility_left[y];
                        if (x == block.getWidth()-1)
                            temp_compatible.right = compatibility_right[y];
                        compatible_checker->putCompatible(temp_compatible);
                    }
                }
            }
            blocks[it.key()] = temp_blocks;
        }
        return BlockSet(blocks, compatible_checker);
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

    CompatibleChecker* compatible_checker = new CompatibleChecker(size);
    Palette palette = readPalette(json_properties, compatible_checker);
    BlockSet blocks_set = readBlocks(json_properties, compatible_checker);
    file.close();

    return TilesetProperties{palette, *compatible_checker, blocks_set};
}
void logExecutablePath() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::cout << "Executable Path: " << path << std::endl;
}