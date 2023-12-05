// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

package tests.detailed.dialog;

import org.cef.callback.CefAuthCallback;
import org.cef.callback.CefAuthenticatorRequestCallback;
import org.cef.misc.CefCollectPinOptions;

import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

@SuppressWarnings("serial")
public class AuthenticatorPinDialog extends JDialog implements Runnable {
    private final JLabel error_ = new JLabel();
    private final JPasswordField pin_ = new JPasswordField(20);
    private final CefCollectPinOptions options_;
    private final CefAuthenticatorRequestCallback callback_;

    public AuthenticatorPinDialog(
            Frame owner, CefCollectPinOptions options, CefAuthenticatorRequestCallback callback) {
        super(owner, "PIN required", true);
        options_ = options;
        callback_ = callback;
        setSize(500, 100);
        setLayout(new GridLayout(0, 2));
        add(new JLabel("Error:"));
        add(error_);
        add(new JLabel("PIN:"));
        add(pin_);

        error_.setText(options.getError().toString());

        JButton abortButton = new JButton("Abort");
        abortButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                callback_.cancel();
                setVisible(false);
                dispose();
            }
        });
        add(abortButton);

        JButton okButton = new JButton("OK");
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (pin_.getText().isEmpty()) return;
                String pin = new String(pin_.getPassword());
                callback_.Continue(pin);
                setVisible(false);
                dispose();
            }
        });
        add(okButton);
    }

    @Override
    public void run() {
        setVisible(true);
    }
}
