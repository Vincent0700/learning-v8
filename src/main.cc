#include <iostream>

#include "libplatform/libplatform.h"
#include "v8.h"

int main(int argc, char* argv[]) {
  // 初始化 V8
  v8::V8::InitializeICUDefaultLocation(argv[0]); // 初始化国际化模块，用于处理 Unicode
  v8::V8::InitializeExternalStartupData(argv[0]); // 加速启动 V8 引擎
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform(); // 初始化 V8 平台
  v8::V8::InitializePlatform(platform.get()); // 初始化 V8 管理平台
  v8::V8::Initialize();
  
  // 创建 V8 引擎实例
  v8::Isolate::CreateParams create_params; // 用于存储 V8 引擎的初始化参数
  create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate* isolate = v8::Isolate::New(create_params); // 实例化一个 V8 隔离实例

  // RAII 写法，作用域结束时析构并回收资源
  {
    v8::HandleScope handle_scope(isolate); // 创建句柄作用域
    v8::Local<v8::Context> context = v8::Context::New(isolate); // 创建上下文
    v8::Context::Scope context_scope(context); // 表示从此开始在当前上下文中创建的实例在离开作用域时回收

    {
      v8::Local<v8::String> source = v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");
      v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked(); // 解析 JS 代码，返回 AST 根节点
      v8::Local<v8::Value> result = script->Run(context).ToLocalChecked(); // 在当前上下文执行 JS 代码
      v8::String::Utf8Value utf8(isolate, result); // 将执行结果转换为 utf8 字符串
      std::cout << *utf8 << std::endl;
    }
  }

  // 析构 V8 实例
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete create_params.array_buffer_allocator;
  return 0;
}
