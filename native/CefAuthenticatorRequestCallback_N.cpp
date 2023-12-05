// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "CefAuthenticatorRequestCallback_N.h"
#include "include/cef_request_handler.h"
#include "jni_scoped_helpers.h"
#include "jni_util.h"

namespace {

CefRefPtr<CefAuthenticatorRequestCallback> GetSelf(jlong self) {
  return reinterpret_cast<CefAuthenticatorRequestCallback*>(self);
}

void ClearSelf(JNIEnv* env, jobject obj) {
  // Clear the reference added in RequestHandler::GetAuthCredentials.
  SetCefForJNIObject<CefAuthenticatorRequestCallback>(
      env, obj, nullptr, "CefAuthenticatorRequestCallback");
}

}  // namespace

JNIEXPORT void JNICALL
Java_org_cef_callback_CefAuthenticatorRequestCallback_1N_N_1Continue(
    JNIEnv* env,
    jobject obj,
    jlong self,
    jstring pin) {
  CefRefPtr<CefAuthenticatorRequestCallback> callback = GetSelf(self);
  if (!callback)
    return;
  callback->Continue(GetJNIString(env, pin));
  ClearSelf(env, obj);
}

JNIEXPORT void JNICALL
Java_org_cef_callback_CefAuthenticatorRequestCallback_1N_N_1Cancel(JNIEnv* env,
                                                                   jobject obj,
                                                                   jlong self) {
  CefRefPtr<CefAuthenticatorRequestCallback> callback = GetSelf(self);
  if (!callback)
    return;
  callback->Cancel();
  ClearSelf(env, obj);
}
