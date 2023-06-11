#include <napi.h>

Napi::String ReadUtf8(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Uint8Array buf = info[0].As<Napi::Uint8Array>();
  int32_t offset = info[1].As<Napi::Number>().Int32Value();
  int32_t length = info[2].As<Napi::Number>().Int32Value();
  auto str = Napi::String::New(env, (char*)buf.Data() + offset, length);
  return str;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "readUtf8"), Napi::Function::New(env, ReadUtf8));
  return exports;
}

NODE_API_MODULE(addon, Init)
