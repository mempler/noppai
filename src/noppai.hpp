#ifndef PROJECT_NOPPAI_HPP
#define PROJECT_NOPPAI_HPP

// We're using oppai, so we have to include it. (else it'll be only header mode.)
#define OPPAI_IMPLEMENTATION
// Include oppai
#include <oppai.c>

// needed includes
#include <fstream>

// Include playmodes for STD,TAIKO,CTB,MANIA
#include "playmodes.hpp"

// Noppai::...
namespace Noppai {
    class oppai {
    public:
        oppai() = default;
        oppai(const char* path);
        oppai(const char* path, uint32_t mods);
        oppai(const char* path, playModes mode);
        oppai(const char* path, uint32_t mods, playModes mode);

        void setMods(uint32_t mods);
        void setMap(const char* path);
        void setMode(playModes mode);
        diff_calc* getStars();
        pp_calc* getPP();
        beatmap* getMap();
    private:
        void calculate(bool init, bool diff, bool pp);
        bool taiko;
        uint32_t mods;
        struct parser pstate;
        struct beatmap map;
        struct diff_calc stars;
        struct pp_calc pp;
    };
}
#endif
