/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGUI/Widget.h>
#include <LibGfx/TextWrapping.h>

namespace GUI {

enum class CheckState {
    Unchecked = 0,
    PartiallyChecked = 1,
    Checked = 2,
};

class AbstractButton : public Widget {
    C_OBJECT_ABSTRACT(AbstractButton);

public:
    virtual ~AbstractButton() override = default;

    Function<void(CheckState)> on_checked;

    virtual void set_text(String);
    String const& text() const { return m_text; }

    bool is_exclusive() const { return m_exclusive; }
    void set_exclusive(bool b) { m_exclusive = b; }

    bool is_unchecked_state() const { return m_check_state == CheckState::Unchecked; }
    bool is_partially_checked_state() const { return m_check_state == CheckState::PartiallyChecked; }
    bool is_checked_state() const { return m_check_state == CheckState::Checked; }

    CheckState check_state() const { return m_check_state; }
    void set_check_state(CheckState, AllowCallback = AllowCallback::Yes);

    bool is_checkable() const { return m_checkable; }
    void set_checkable(bool);

    bool is_hovered() const { return m_hovered; }
    bool is_being_pressed() const { return m_being_pressed; }

    unsigned allowed_mouse_buttons_for_pressing() const { return m_allowed_mouse_buttons_for_pressing; }
    void set_allowed_mouse_buttons_for_pressing(unsigned allowed_buttons) { m_allowed_mouse_buttons_for_pressing = allowed_buttons; }

    virtual void click(unsigned modifiers = 0) = 0;
    virtual void middle_mouse_click(unsigned) {};
    virtual bool is_uncheckable() const { return true; }

    int auto_repeat_interval() const { return m_auto_repeat_interval; }
    void set_auto_repeat_interval(int interval) { m_auto_repeat_interval = interval; }

protected:
    explicit AbstractButton(String = {});

    virtual void mousedown_event(MouseEvent&) override;
    virtual void mousemove_event(MouseEvent&) override;
    virtual void mouseup_event(MouseEvent&) override;
    virtual void keydown_event(KeyEvent&) override;
    virtual void keyup_event(KeyEvent&) override;
    virtual void enter_event(Core::Event&) override;
    virtual void leave_event(Core::Event&) override;
    virtual void focusout_event(GUI::FocusEvent&) override;
    virtual void change_event(Event&) override;

    void paint_text(Painter&, Gfx::IntRect const&, Gfx::Font const&, Gfx::TextAlignment, Gfx::TextWrapping = Gfx::TextWrapping::DontWrap);

private:
    String m_text;
    CheckState m_check_state { CheckState::Unchecked };
    bool m_checkable { false };
    bool m_hovered { false };
    bool m_being_pressed { false };
    bool m_being_keyboard_pressed { false };
    bool m_exclusive { false };

    MouseButton m_pressed_mouse_button { MouseButton::None };
    unsigned m_allowed_mouse_buttons_for_pressing { MouseButton::Primary };

    int m_auto_repeat_interval { 0 };
    RefPtr<Core::Timer> m_auto_repeat_timer;
};

}
