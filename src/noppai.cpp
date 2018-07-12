#include "noppai.hpp"

void Noppai::oppai::calculate(bool init, bool diff, bool pp) {
  d_init(&this->stars);
  d_calc(&this->stars, &this->map, this->mods);
  b_ppv2(&this->map, &this->pp, this->stars.aim, this->stars.speed, this->mods); }

Noppai::oppai::oppai() = default { }
Noppai::oppai::oppai(const char* path) {
  this->setMap(path);
  this->calculate(true, true, true); }
Noppai::oppai::oppai(const char* path, uint32_t mods) {
  this->setMap(path);
  this->calculate(true, false, false);
  this->setMods(mods); }
Noppai::oppai::oppai(const char* path, playModes mode) {
  this->setMap(path);
  this->calculate(true, false, false);
  this->setMode(mode); }
Noppai::oppai::oppai(const char* path, uint32_t mods, playModes mode) {
  this->setMap(path);
  this->calculate(true, false, false);
  this->setMode(mode);
  this->setMods(mods);
  calculate(true, true, true); }

void Noppai::oppai::setMods(uint32_t mods) {
  this->mods = mods; this->calculate(false, true, true); }
void Noppai::oppai::setMap(const char* path) {
  FILE* maposu = fopen(path, "r");
  p_init(&this->pstate);
  p_map(&this->pstate, &this->map, maposu);
  fclose(maposu);
}
void Noppai::oppai::setMode(playModes mode) {
  bool wasTaiko = false;
  bool wasntTaiko = false;
  switch(mode) {
    case playModes::osu:
      if (this->taiko)
        wasTaiko = true;
      if (wasTaiko) {
        this->taiko = false;
        this->calculate(false, true, true);
      }
      break;
    case playModes::taiko:
      if (!this->taiko)
        wasntTaiko = true;
      if (wasntTaiko) {
        this->taiko = true;
        this->calculate(false, true, true);
      }
      break;
    default:
      if (this->taiko)
        wasTaiko = true;
      if (wasTaiko) {
        this->taiko = false;
        this->calculate(false, true, true);
      }
      printf("Sorry, but %i isn't supported yet!", mode);
      break;
  }
  if(this->taiko) {
    this->pstate.mode_override = MODE_TAIKO;
    this->pstate.flags = PARSER_OVERRIDE_MODE;
  }
}

beatmap* Noppai::oppai::getMap() {
  return &this->map; }
pp_calc* Noppai::oppai::getPP() {
  return &this->pp; }
diff_calc* Noppai::oppai::getStars() {
  return &this->stars; }