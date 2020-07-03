#include <iostream>

#include "v8.h"
#include "libplatform/libplatform.h"
#include "helper.h"

void testString(v8::Isolate* isolate, const v8::Local<v8::Context>& context) {
  // char* -> String
  v8::Local<v8::String> s1 = v8::String::NewFromUtf8Literal(isolate, "Hello World");
  v8::Local<v8::String> s2 = v8::String::NewFromUtf8(isolate, "Hello World").ToLocalChecked();
  // String -> char*
  char* val = *v8::String::Utf8Value(isolate, s1);
  std::cout << val << std::endl;
}

void testNumber(v8::Isolate* isolate, const v8::Local<v8::Context>& context) {
  // double -> Number
  v8::Local<v8::Number> n1 = v8::Number::New(isolate, 1);
  // Number -> double
  double v1 = n1->Value();
  std::cout << v1 << std::endl;
}

int main(int argc, char* argv[]) {
  helper::V8Context([](v8::Isolate* isolate, const v8::Local<v8::Context>& context) -> void {
    // testString(isolate, context);
    testNumber(isolate, context);
  });
  return 0;
}
