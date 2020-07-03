#include <iostream>

#include "v8.h"
#include "libplatform/libplatform.h"
#include "helper.h"

int main(int argc, char* argv[]) {
  helper::V8Context([](v8::Isolate* isolate, const v8::Local<v8::Context>& context) -> void {
    v8::Local<v8::String> source = v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");
    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();
    v8::String::Utf8Value utf8(isolate, result);
    std::cout << *utf8 << std::endl;
  });
  return 0;
}
