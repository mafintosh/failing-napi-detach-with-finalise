#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>

static void finalise (napi_env env, void *finalise_data, void *finalise_hint) {
}

napi_value alloc_with_finalise (napi_env env, napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  void *data = malloc(10);
  napi_value buf;
  napi_create_external_arraybuffer(env, data, 10, finalise, NULL, &buf);

  return buf;
}

napi_value alloc (napi_env env, napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  void *data = malloc(10);
  napi_value buf;
  napi_create_external_arraybuffer(env, data, 10, NULL, NULL, &buf);

  return buf;
}

napi_value detach (napi_env env, napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  napi_detach_arraybuffer(env, argv[0]);

  return NULL;
}

napi_value init_all (napi_env env, napi_value exports) {
  napi_value alloc_with_finalise_fn;
  napi_create_function(env, NULL, 0, alloc_with_finalise, NULL, &alloc_with_finalise_fn);
  napi_set_named_property(env, exports, "alloc_with_finalise", alloc_with_finalise_fn);

  napi_value alloc_fn;
  napi_create_function(env, NULL, 0, alloc, NULL, &alloc_fn);
  napi_set_named_property(env, exports, "alloc", alloc_fn);

  napi_value detach_fn;
  napi_create_function(env, NULL, 0, detach, NULL, &detach_fn);
  napi_set_named_property(env, exports, "detach", detach_fn);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)
