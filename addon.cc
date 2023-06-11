#include <assert.h>
#include <node_api.h>

static napi_value ReadUtf8(napi_env env, napi_callback_info info) {
  size_t argc = 3;
	napi_value args[3];
	napi_get_cb_info(env, info, &argc, args, NULL, NULL);
	uint8_t* buf;
	uint32_t offset;
	uint32_t length;
	size_t buffer_size;
	napi_get_buffer_info(env, args[0], (void**) &buf, &buffer_size);
	napi_get_value_uint32(env, args[1], &offset);
	napi_get_value_uint32(env, args[2], &length);
  bool ascii = true;
  auto position = offset;
  auto end = position + length;
  if (length > 32) {
    ascii = false;
  } else {
    while(position < end)
      if (buf[position++] >= 0x80) {
        ascii = false;
        break;
      }
  }
  napi_value str;
  if (ascii) napi_create_string_latin1(env, (const char*) buf + offset, (int) length, &str);
  else napi_create_string_utf8(env, (const char*) buf + offset, (int) length, &str);
  return str;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("readUtf8", ReadUtf8);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
