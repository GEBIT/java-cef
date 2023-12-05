// Copyright (c) 2023 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef JCEF_NATIVE_AUTHENTICATOR_RESULT_HANDLER_H_
#define JCEF_NATIVE_AUTHENTICATOR_RESULT_HANDLER_H_
#pragma once

#include <jni.h>
#include "include/cef_authenticator_result_handler.h"

#include "jni_scoped_helpers.h"

// AuthenticatorResultHandler implementation.
class AuthenticatorResultHandler : public CefAuthenticatorResultHandler {
 public:
  AuthenticatorResultHandler(JNIEnv* env, jobject handler);

  // CefAuthenticatorResultHandler methods
  void OnFailure(const cef_authenticator_failure_reason_t reason) override;
  void OnSuccess() override;
  void OnFinishCollectToken() override;

 protected:
  ScopedJNIObjectGlobal handle_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(AuthenticatorResultHandler);
};

#endif  // JCEF_NATIVE_AUTHENTICATOR_RESULT_HANDLER_H_
