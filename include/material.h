#pragma once
#include <cstdint>

class Material{
    public:
        Material();
        ~Material();
        Material(int x, int y, int width, int height);
        const uint16_t& operator[](int i);

        void addMaterial(int x, int y, int width, int height);
        void addMaterial(int id);
        void removeMaterial(int x, int y, int width, int height);
        void removeMaterial (int id);
    private:
        int size;
        uint16_t* components;
};