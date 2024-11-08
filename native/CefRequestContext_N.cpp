// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "CefRequestContext_N.h"
#include "include/cef_request_context.h"
#include "jni_util.h"
#include "request_context_handler.h"

JNIEXPORT jobject JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1GetGlobalContext(JNIEnv* env,
                                                              jclass cls) {
  CefRefPtr<CefRequestContext> context = CefRequestContext::GetGlobalContext();
  if (!context.get())
    return nullptr;

  ScopedJNIObjectLocal jContext(env, NewJNIObject(env, cls));
  if (!jContext)
    return nullptr;

  SetCefForJNIObject(env, jContext, context.get(), "CefRequestContext");
  return jContext.Release();
}

JNIEXPORT jobject JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1CreateContext(JNIEnv* env,
                                                           jclass cls,
                                                           jobject jhandler) {
  CefRefPtr<CefRequestContextHandler> handler = nullptr;
  if (jhandler != nullptr) {
    handler = new RequestContextHandler(env, jhandler);
  }

  // TODO(JCEF): Expose CefRequestContextSettings.
  CefRequestContextSettings settings;
  CefRefPtr<CefRequestContext> context =
      CefRequestContext::CreateContext(settings, handler);
  if (!context.get())
    return nullptr;

  ScopedJNIObjectLocal jContext(env, NewJNIObject(env, cls));
  if (!jContext)
    return nullptr;

  SetCefForJNIObject(env, jContext, context.get(), "CefRequestContext");
  return jContext.Release();
}

JNIEXPORT jboolean JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1IsGlobal(JNIEnv* env,
                                                      jobject obj) {
  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return JNI_FALSE;
  return context->IsGlobal() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1HasPreference(JNIEnv* env,
                                                           jobject obj,
                                                           jstring jname) {
  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return JNI_FALSE;

  CefString name = GetJNIString(env, jname);
  return context->HasPreference(name) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jobject JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1GetPreference(JNIEnv* env,
                                                           jobject obj,
                                                           jstring jname) {
  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return nullptr;

  CefString name = GetJNIString(env, jname);
  CefRefPtr<CefValue> value = context->GetPreference(name);
  if (!value)
    return nullptr;

  return ScopedJNIObjectLocal(env, value).Release();
}

JNIEXPORT jobject JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1GetAllPreferences(
    JNIEnv* env,
    jobject obj,
    jboolean includeDefaults) {
  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return nullptr;

  CefRefPtr<CefDictionaryValue> value =
      context->GetAllPreferences(includeDefaults == JNI_TRUE);
  if (!value)
    return nullptr;

  ScopedJNIHashMap jmap(env);
  CefDictionaryValue::KeyList keys;
  value->GetKeys(keys);
  for (const CefString& key : keys) {
    ScopedJNIString jkey(env, key);
    ScopedJNIObjectLocal jvalue(env, value->GetValue(key));
    jmap.Put(jkey.Release(), jvalue.Release());
  }
  return jmap.Release();
}

JNIEXPORT jboolean JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1CanSetPreference(JNIEnv* env,
                                                              jobject obj,
                                                              jstring jname) {
  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return JNI_FALSE;

  CefString name = GetJNIString(env, jname);
  return context->CanSetPreference(name) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jstring JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1SetPreference(JNIEnv* env,
                                                           jobject obj,
                                                           jstring jname,
                                                           jobject jvalue) {
  if (!CefCurrentlyOn(TID_UI))
    return NewJNIString(env, "called on invalid thread");

  CefRefPtr<CefRequestContext> context =
      GetCefFromJNIObject<CefRequestContext>(env, obj, "CefRequestContext");
  if (!context.get())
    return NewJNIString(env, "no request context");

  CefString name = GetJNIString(env, jname);
  CefRefPtr<CefValue> value = GetCefValueFromJNIObject(env, jvalue);
  if (!value)
    return NewJNIString(env, "no value to set");

  CefString error;
  bool result = context->SetPreference(name, value, error);
  if (!result)
    return NewJNIString(env, error);

  return nullptr;
}

JNIEXPORT void JNICALL
Java_org_cef_browser_CefRequestContext_1N_N_1CefRequestContext_1DTOR(
    JNIEnv* env,
    jobject obj) {
  SetCefForJNIObject<CefRequestContext>(env, obj, nullptr, "CefRequestContext");
}
