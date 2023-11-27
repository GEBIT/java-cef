// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

package org.cef.misc;

/**
 * Handle to observer registration, As long as this object is alive, the observer will stay
 * registered.
 */
public abstract class CefRegistration {
    /**
     * Removes the native reference from an unused object.
     */
    public abstract void dispose();

    @Override
    public void finalize() throws Throwable {
        dispose();
        super.finalize();
    }
}
