#include <functional>

#include "v8.h"
#include "libplatform/libplatform.h"

namespace helper {

  void V8Isolate(std::function<void (v8::Isolate* isolate)> callback) {
    v8::V8::InitializeICUDefaultLocation(NULL);
    v8::V8::InitializeExternalStartupData(NULL);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);

    callback(isolate);

    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
  }

  void V8Context(std::function<void (const v8::Local<v8::Context>& context)> callback, v8::Isolate* isolate) {
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);
    callback(context);
  }

  void V8Context(std::function<void (v8::Isolate* isolate, const v8::Local<v8::Context>& context)> callback) {
    V8Isolate([&](v8::Isolate* isolate) -> void {
      V8Context([&](const v8::Local<v8::Context>& context) -> void {
        callback(isolate, context);
      }, isolate);
    });
  }

}
