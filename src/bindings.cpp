#include "noppai.hpp"

// Include nan.h (NodeJS Bindings)
#include <nan.h>

void f_main(const Nan::FunctionCallbackInfo<v8::Value>& info) {

}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::SetMethod(module, "exports", f_main);
}

NODE_MODULE(noppai, Init)