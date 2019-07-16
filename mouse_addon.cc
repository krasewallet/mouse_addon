#include <napi.h>
#include <Windows.h>

Napi::Value mouse_proc(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int type = info[0].As<Napi::Number>().Int32Value();
  int x = info[1].As<Napi::Number>().Int32Value();
  int y = info[2].As<Napi::Number>().Int32Value();
  
  switch (type)
  {
	case 0:
		SetCursorPos(x, y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		break;
	case 1:
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		break;
	case 2:
		SetCursorPos(x, y);
		break;
	default:
	  break;
  }

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "mouse_proc"),
              Napi::Function::New(env, mouse_proc));
  return exports;
}

NODE_API_MODULE(mouse_addon, Init)
