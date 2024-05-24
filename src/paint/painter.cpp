#include "painter.h"
#include <stdexcept>
#include <queue>
#include <utility>

Painter::Painter() : map{nullptr}, palette{nullptr}{}

Painter::Painter(Map* map) : map{map}, palette{nullptr}{}

Painter::Painter(Map* map, Palette* palette) : map{map}, palette{palette}{}

bool Painter::isMaterial(int x, int y, const Material &material){
    return (material.containsTile((*map)[y][x].tileID));;
}
bool Painter::isMaterial(int x, int y, const std::string& material_name){
    return isMaterial(x, y, (*palette)[material_name]);
}


void Painter::setMap(Map* map){
    this->map = map;
}
void Painter::setPalette(Palette* palette){
    this->palette = palette;
}

void Painter::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

void Painter::paint(int x, int y, const Material& material){
    if (!history_stack){
        (*map)[y][x].tileID = Palette::pick(material);
        return;
    }
    release();
    holdPaint(x, y, material);
    release();
}

void Painter::paint(int x, int y, const std::string& material_name){
    checkPaletteSet();
    paint(x, y, (*palette)[material_name]);
}

bool Painter::holdPaint(int x, int y, const Material &material){
    if (!history_stack){
        paint(x, y, material);
        return false;
    }
    history_stack->trackChange({
        {Palette::pick(material), (*map)[y][x].entityID},
        x, y
    });
    return true;
}

bool Painter::holdPaint(int x, int y, const std::string &material_name){
    checkPaletteSet();
    return holdPaint(x, y, (*palette)[material_name]);
}

bool Painter::release(){
    if (!history_stack)
        return false;
    return history_stack->commit();
}

bool Painter::isOutOfBounds(int x, int y)
{
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

    release();
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
    release();
}
void Painter::fill(int x, int y, const std::string& fill_material_name, const std::string& replaced_material_name){
    checkPaletteSet();
    fill(x, y, (*palette)[fill_material_name], (*palette)[replaced_material_name]);
}

void Painter::fill(int x, int y, const Material& fill_material, bool use_palette){
    if (use_palette){
        fill(x, y, fill_material, palette->findMaterial((*map)[y][x].tileID));
    } else {
        fill(x, y, fill_material, Material((*map)[y][x].tileID));
    }
}

void Painter::fill(int x, int y, const std::string& fill_material_name, bool use_palette)
{
    checkPaletteSet();
    fill(x, y, (*palette)[fill_material_name], use_palette);
}

bool Painter::checkMapSet()
{
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

bool Painter::checkHistoryStack(){
    if (!history_stack){
        throw std::runtime_error("History stack is not set");
        return false;
    }
    return true;
}
