// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFCLIENT_COOKIE_VISITOR_H_
#define CEF_TESTS_CEFCLIENT_COOKIE_VISITOR_H_
#pragma once

#include <jni.h>
#include "include/cef_cookie.h"

// CookieVisitor implementation.
class CookieVisitor : public CefCookieVisitor {
 public:
  CookieVisitor(JNIEnv* env, jobject jvisitor);
  virtual ~CookieVisitor();

  // CookieVisitor methods
  virtual bool Visit(const CefCookie& cookie, int count, int total,
                     bool& deleteCookie) OVERRIDE;

 protected:
  jobject jvisitor_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(CookieVisitor);
};

#endif  // CEF_TESTS_CEFCLIENT_COOKIE_VISITOR_H_