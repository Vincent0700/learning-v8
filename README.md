# Learning V8

本仓库的目的是搭建 V8 的学习和测试环境，如有问题请提 [Issue](https://github.com/Vincent0700/learning-v8/issues/new)。

## 环境

仅在 macOS 环境上测试过，如需在别的平台执行，请自行下载 V8 源码编译，方法参考我之前的文章[《V8 编译踩坑》](https://vincentstudio.info/2020/05/18/054_V8_compilation/)。编译好后将头文件和静态库放在 `./src/third-party/v8` 目录下，并修改 `Makefile` 相应的变量。

## 起步

### Clone

```
$ git clone https://github.com/Vincent0700/learning-v8.git
```

### 下载依赖

```
$ make check

[INFO] Installing Deps.

x 8.3-lkgr/
x 8.3-lkgr/include/
x 8.3-lkgr/lib/
x 8.3-lkgr/lib/osx/
x 8.3-lkgr/lib/osx/libv8_libplatform.a
x 8.3-lkgr/lib/osx/libv8_libbase.a
x 8.3-lkgr/lib/osx/libv8_monolith.a
x 8.3-lkgr/include/v8-platform.h
x 8.3-lkgr/include/v8-version.h
x 8.3-lkgr/include/libplatform/
x 8.3-lkgr/include/.DS_Store
x 8.3-lkgr/include/v8-inspector-protocol.h
x 8.3-lkgr/include/v8-profiler.h
x 8.3-lkgr/include/v8.h
x 8.3-lkgr/include/v8-fast-api-calls.h
x 8.3-lkgr/include/js_protocol-1.2.json
x 8.3-lkgr/include/v8-util.h
x 8.3-lkgr/include/v8-wasm-trap-handler-win.h
x 8.3-lkgr/include/js_protocol-1.3.json
x 8.3-lkgr/include/v8-wasm-trap-handler-posix.h
x 8.3-lkgr/include/OWNERS
x 8.3-lkgr/include/DEPS
x 8.3-lkgr/include/js_protocol.pdl
x 8.3-lkgr/include/APIDesign.md
x 8.3-lkgr/include/v8-value-serializer-version.h
x 8.3-lkgr/include/v8config.h
x 8.3-lkgr/include/v8-version-string.h
x 8.3-lkgr/include/v8-inspector.h
x 8.3-lkgr/include/v8-internal.h
x 8.3-lkgr/include/cppgc/
x 8.3-lkgr/include/cppgc/gc-info.h
x 8.3-lkgr/include/cppgc/allocation.h
x 8.3-lkgr/include/cppgc/internals.h
x 8.3-lkgr/include/cppgc/garbage-collected.h
x 8.3-lkgr/include/cppgc/README.md
x 8.3-lkgr/include/cppgc/heap.h
x 8.3-lkgr/include/cppgc/finalizer-trait.h
x 8.3-lkgr/include/cppgc/platform.h
x 8.3-lkgr/include/libplatform/libplatform.h
x 8.3-lkgr/include/libplatform/libplatform-export.h
x 8.3-lkgr/include/libplatform/DEPS
x 8.3-lkgr/include/libplatform/v8-tracing.h

Done!
```

### 测试

如果测试代码没有报错，就说明测试环境搭建好了。

```
$ make test 

[TEST] src/test/hello-world.cc
-------------------------------------
Hello, World!
3 + 4 = 7
```
