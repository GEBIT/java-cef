// Copyright (c) 2023 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "authenticator_result_handler.h"

#include "jni_util.h"

AuthenticatorResultHandler::AuthenticatorResultHandler(JNIEnv* env,
                                                       jobject handler)
    : handle_(env, handler) {}

void AuthenticatorResultHandler::OnFailure(
    const cef_authenticator_failure_reason_t reason) {
  ScopedJNIEnv env;
  if (!env)
    return;

  ScopedJNIObjectResult jreason(env);
  switch (reason) {
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_KEY_NOT_REGISTERED, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_KEY_ALREADY_REGISTERED, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_SOFT_PIN_BLOCK, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_HARD_PIN_BLOCK, jreason);
    JNI_CASE(
        env,
        "org/cef/handler/"
        "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_REMOVED_DURING_PIN_ENTRY,
        jreason);
    JNI_CASE(
        env,
        "org/cef/handler/"
        "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_RESIDENT_KEYS,
        jreason);
    JNI_CASE(
        env,
        "org/cef/handler/"
        "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_USER_VERIFICATION,
        jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_LARGE_BLOB,
             jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_NO_COMMON_ALGORITHMS, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_STORAGE_FULL, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_USER_CONSENT_DENIED, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_WIN_USER_CANCELLED, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_HYBRID_TRANSPORT_ERROR, jreason);
    JNI_CASE(env,
             "org/cef/handler/"
             "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
             CEF_AUTHENTICATOR_FAILURE_REASON_NO_PASSKEYS, jreason);
    default:
      JNI_CASE(env,
               "org/cef/handler/"
               "CefAuthenticatorResultHandler$AuthenticatorFailureReason",
               CEF_AUTHENTICATOR_FAILURE_REASON_TIMEOUT, jreason);
  }

  JNI_CALL_VOID_METHOD(
      env, handle_, "onFailure",
      "(Lorg/cef/handler/"
      "CefAuthenticatorResultHandler$AuthenticatorFailureReason;)V",
      jreason.get());
}

void AuthenticatorResultHandler::OnSuccess() {
  ScopedJNIEnv env;
  if (!env)
    return;

  JNI_CALL_VOID_METHOD(env, handle_, "onSuccess", "()V");
}

void AuthenticatorResultHandler::OnFinishCollectToken() {
  ScopedJNIEnv env;
  if (!env)
    return;

  JNI_CALL_VOID_METHOD(env, handle_, "onFinishCollectToken", "()V");
}
