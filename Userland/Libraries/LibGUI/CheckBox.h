/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, William JK Mentha <wjkmentha@gmail.com>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGUI/AbstractButton.h>

namespace GUI {

enum class CheckState {
    Unchecked = 0,
    PartiallyChecked = 1,
    Checked = 2,
};

class CheckBox : public AbstractButton {
    C_OBJECT(CheckBox);

public:
    virtual ~CheckBox() override = default;

    virtual void click(unsigned modifiers = 0) override;

    bool is_autosize() const { return m_autosize; }
    void set_autosize(bool);

    enum class CheckBoxPosition {
        Left,
        Right,
    };
    CheckBoxPosition checkbox_position() const { return m_checkbox_position; }
    void set_checkbox_position(CheckBoxPosition value) { m_checkbox_position = value; }

    bool is_tristate() const { return m_tristate; }
    void set_tristate(bool to_tristate = true) { m_tristate = to_tristate };
    void set_check_state (GUI::CheckState state) { m_check_state = state; }
    void set_check_state_direction(GUI::CheckStateDirection direction) { m_check_state_direction = direction; }
    GUI::CheckStateDirection get_check_state_direction() const { return m_check_state_direction; }

protected:
    explicit CheckBox(String = {});
    virtual void next_check_state() override;

private:
    void size_to_fit();

    // These don't make sense for a check box, so hide them.
    using AbstractButton::auto_repeat_interval;
    using AbstractButton::set_auto_repeat_interval;

    virtual void paint_event(PaintEvent&) override;

    bool m_autosize { false };
    bool m_tristate { false };
    GUI::CheckStateDirection m_check_state_direction { GUI::CheckStateDirection::Forward };
    GUI::CheckState m_check_state { GUI::CheckState::Unchecked };
    CheckBoxPosition m_checkbox_position { CheckBoxPosition::Left };
};

}
