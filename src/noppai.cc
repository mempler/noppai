#include <nan.h>
#include <fstream>

#define OPPAI_IMPLEMENTATION

#include "oppai-ng/oppai.c"
#include "helper.h"

uint32_t mods;
struct parser pstate;
struct beatmap map;
struct diff_calc stars;
struct pp_calc pp;

void CalculatePP(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  d_init(&stars);
  d_calc(&stars, &map, mods);
    
  b_ppv2(&map, &pp, stars.aim, stars.speed, mods);

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  obj->Set(Nan::New("total").ToLocalChecked(), Nan::New(pp.total));
  obj->Set(Nan::New("aim").ToLocalChecked(), Nan::New(pp.aim));
  obj->Set(Nan::New("speed").ToLocalChecked(), Nan::New(pp.speed));
  obj->Set(Nan::New("acc").ToLocalChecked(), Nan::New(pp.acc));

  info.GetReturnValue().Set(obj);
}

void CalculateStars(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  d_init(&stars);
  d_calc(&stars, &map, mods);

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  obj->Set(Nan::New("total").ToLocalChecked(), Nan::New(stars.total));
  obj->Set(Nan::New("aim").ToLocalChecked(), Nan::New(stars.aim));
  obj->Set(Nan::New("speed").ToLocalChecked(), Nan::New(stars.speed));

  info.GetReturnValue().Set(obj);
}

void ParseBeatmap(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if ( info.Length() < 1 ) {
    Nan::ThrowTypeError("No Beatmap path is Provided! please use E.G \"const oppai = noppai(__dirname + \"/map.osu\");\"");
    return;
  }

  if ( info.Length() < 2 && !info[1]->IsUint32()) {
    mods = 0;
  } else {
    mods = info[1]->Uint32Value();
  }

  if ( !info[0]->IsString() ) {
    Nan::ThrowTypeError("Argument 1 (Beatmap Path) is not a String!");
    return;
  }

  v8::String::Utf8Value filename(info[0]);

  FILE * osufile;
  osufile = fopen(ToCString(filename), "r");
  if (osufile){

    p_init(&pstate);
    p_map(&pstate, &map, osufile);

    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    obj->Set(Nan::New("CalculatePP").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(CalculatePP)->GetFunction());
    obj->Set(Nan::New("CalculateStars").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(CalculateStars)->GetFunction());

    info.GetReturnValue().Set(obj);
    fclose(osufile);
  }else{
    Nan::ThrowTypeError("No such BeatmapFile!");
    return;
  }
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::SetMethod(module, "exports", ParseBeatmap);
}

NODE_MODULE(noppai, Init)