// Copyright (c) 2023 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

package org.cef.misc;

import java.awt.Dimension;
import java.awt.Rectangle;
import java.util.Vector;

/**
 * Class representing PIN collection options.
 */
public class CefCollectPinOptions {
    /**
     * The reasons for prompting for a pin.
     */
    public enum PinEntryReason {
        /**
         * Indicates a new PIN is being set.
         */
        CEF_PIN_ENTRY_REASON_SET,

        /**
         * The existing PIN must be changed before using this authenticator.
         */
        CEF_PIN_ENTRY_REASON_CHANGE,

        /**
         * The existing PIN is being collected to prove user verification.
         */
        CEF_PIN_ENTRY_REASON_CHALLENGE,
    }

    /**
     * The errors that may prompt asking for a PIN.
     */
    public enum PinEntryError {
        /**
         * No error has occurred.
         */
        CEF_PIN_ENTRY_ERROR_NO_ERROR,

        /**
         * Internal UV is locked, so we are falling back to PIN.
         */
        /// Internal UV is locked, so we are falling back to PIN.
        CEF_PIN_ENTRY_ERROR_INTERNAL_UV_LOCKED,

        /**
         * The PIN the user entered does not match the authenticator PIN.
         */
        CEF_PIN_ENTRY_ERROR_WRONG_PIN,

        /**
         * The new PIN the user entered is too short.
         */
        CEF_PIN_ENTRY_ERROR_TOO_SHORT,

        /**
         * The new PIN the user entered contains invalid characters.
         */
        CEF_PIN_ENTRY_ERROR_INVALID_CHARACTERS,

        /**
         * The new PIN the user entered is the same as the currently set PIN.
         */
        CEF_PIN_ENTRY_ERROR_SAME_AS_CURRENT_PIN,
    }

    private PinEntryReason reason_;
    private PinEntryError error_;
    private long min_pin_length_;
    private int attempts_;

    public CefCollectPinOptions(
            PinEntryReason reason, PinEntryError error, long min_pin_length, int attempts) {
        reason_ = reason;
        error_ = error;
        min_pin_length_ = min_pin_length;
        attempts_ = attempts;
    }

    /**
     * Why this PIN is being collected.
     */
    public PinEntryReason getReason() {
        return reason_;
    }

    /**
     * The error for which we are prompting for a PIN.
     */
    public PinEntryError getError() {
        return error_;
    }

    /**
     * The minimum PIN length the authenticator will accept for the PIN.
     */
    public long getMinPinLength() {
        return min_pin_length_;
    }

    /**
     * The number of attempts remaining before a hard lock. Should be ignored
     * unless |reason| is PIN_ENTRY_REASON_CHALLENGE.
     */
    public int getAttempts() {
        return attempts_;
    }
}
