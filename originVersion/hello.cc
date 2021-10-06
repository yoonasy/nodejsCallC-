#include <node.h>

using namespace v8;

// 一个能返回JS字符串"Hello World!"的函数
void sayHello(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Hello World!"));
}

// 和js模块一样，有两种初始化函数
// 导出方式类似  exports.Hello = sayHello;
void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "Hello", sayHello);
    NODE_SET(exports, "string", "Hello world");
}

// 导出方式类似 module.exports = sayHello;
void Initialize2(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(module, "exports", sayHello);
}

// 注意:
// NODE_MODULE()后面没有分号，因为它不是一个函数
// 官方文档说模块名称(这里是hello)必须与最终二进制文件的文件名匹配(不包括.node后缀)，不过不匹配好像也行
NODE_MODULE(hello, Initialize)  // 这里我们使用第一种导出方法进行注册