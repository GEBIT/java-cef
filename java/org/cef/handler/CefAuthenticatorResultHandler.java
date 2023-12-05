// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

package org.cef.handler;

/**
 * Implement this interface to handle Webauthn authentication results.
 */
public interface CefAuthenticatorResultHandler {
    /**
     * Failure reasons.
     */
    enum AuthenticatorFailureReason {
        CEF_AUTHENTICATOR_FAILURE_REASON_TIMEOUT,
        CEF_AUTHENTICATOR_FAILURE_REASON_KEY_NOT_REGISTERED,
        CEF_AUTHENTICATOR_FAILURE_REASON_KEY_ALREADY_REGISTERED,
        CEF_AUTHENTICATOR_FAILURE_REASON_SOFT_PIN_BLOCK,
        CEF_AUTHENTICATOR_FAILURE_REASON_HARD_PIN_BLOCK,
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_REMOVED_DURING_PIN_ENTRY,
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_RESIDENT_KEYS,
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_USER_VERIFICATION,
        CEF_AUTHENTICATOR_FAILURE_REASON_AUTHENTICATOR_MISSING_LARGE_BLOB,
        CEF_AUTHENTICATOR_FAILURE_REASON_NO_COMMON_ALGORITHMS,
        // kStorageFull indicates that a resident credential could not be created
        // because the authenticator has insufficient storage.
        CEF_AUTHENTICATOR_FAILURE_REASON_STORAGE_FULL,
        CEF_AUTHENTICATOR_FAILURE_REASON_USER_CONSENT_DENIED,
        // kWinUserCancelled means that the user clicked "Cancel" in the native
        // Windows UI.
        CEF_AUTHENTICATOR_FAILURE_REASON_WIN_USER_CANCELLED,
        CEF_AUTHENTICATOR_FAILURE_REASON_HYBRID_TRANSPORT_ERROR,
        CEF_AUTHENTICATOR_FAILURE_REASON_NO_PASSKEYS;
    }

    /**
     * The authentication attempt has failed. This is a final call.
     *
     * @param reason the failure reason
     */
    public void onFailure(AuthenticatorFailureReason reason);

    /**
     * The authentication attempt has succeeded. This is a final call.
     */
    public void onSuccess();

    /**
     * The authentication requires the user to conclude token generation (typically by physically
     * tapping the hardware token again). This communicates an intermediate stage of the
     * authentication (so a call to onSuccess or onFailure will follow later).
     */
    public void onFinishCollectToken();
}
