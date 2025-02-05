#include "painter.h"
#include <stdexcept>
#include <queue>
#include <utility>

Painter::Painter() : map{nullptr}, palette{nullptr}{}

Painter::Painter(SmartMap* map) : map{map}, palette{nullptr}{}

Painter::Painter(SmartMap* map, Palette* palette) : map{map}, palette{palette}{}

bool Painter::isMaterial(int x, int y, const Material &material){
    return (material.containsTile(map->getTile(x, y).tileID));
}
bool Painter::isMaterial(int x, int y, const std::string& material_name){
    return isMaterial(x, y, (*palette)[material_name]);
}


void Painter::setMap(SmartMap* map){
    this->map = map;
}
void Painter::setPalette(Palette* palette){
    this->palette = palette;
}

void Painter::paint(int x, int y, const Material& material){
    holdPaint(x, y, material);
    map->commit();
}

void Painter::paint(int x, int y, const std::string& material_name){
    checkPaletteSet();
    paint(x, y, (*palette)[material_name]);
}

void Painter::holdPaint(int x, int y, const Material &material){
    map->addTile(x, y, {Palette::pick(material)});
}

void Painter::holdPaint(int x, int y, const std::string &material_name){
    checkPaletteSet();
    return holdPaint(x, y, (*palette)[material_name]);
}

bool Painter::isOutOfBounds(int x, int y){
    return 
        x < 0 ||
        y < 0 || 
        x >= map->width() ||
        y >= map->height();
}


void Painter::fill(int x, int y, const Material& fill_material, const Material& replaced_material){
    checkMapSet();
    if (fill_material == replaced_material)
        return;
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(x, y));

    while (!queue.empty()){
        std::pair<int, int> coords = queue.front();
        int x = coords.first;
        int y = coords.second;
        queue.pop();

        if(isOutOfBounds(x, y) || !isMaterial(x, y, replaced_material))
            continue;
        holdPaint(x, y, fill_material);
        queue.push(std::make_pair(x+1, y));
        queue.push(std::make_pair(x-1, y));
        queue.push(std::make_pair(x, y+1));
        queue.push(std::make_pair(x, y-1));
    }
    map->commit();
}
void Painter::fill(int x, int y, const std::string& fill_material_name, const std::string& replaced_material_name){
    checkPaletteSet();
    fill(x, y, (*palette)[fill_material_name], (*palette)[replaced_material_name]);
}

void Painter::fill(int x, int y, const Material& fill_material, bool use_palette){
    if (use_palette){
        fill(x, y, fill_material, palette->findMaterial(map->getTileID(x, y)));
    } else {
        fill(x, y, fill_material, Material(map->getTileID(x, y)));
    }
}

void Painter::fill(int x, int y, const std::string& fill_material_name, bool use_palette){
    checkPaletteSet();
    fill(x, y, (*palette)[fill_material_name], use_palette);
}

bool Painter::checkMapSet(){
    if (!map){
        throw std::runtime_error("Map is not set");
        return false;
    };
    return true;
}
bool Painter::checkPaletteSet(){
    if (!palette){
        throw std::runtime_error("Palette is not set");
        return false;
    };
    return true;
}
