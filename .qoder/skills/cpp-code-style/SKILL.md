---
name: cpp-code-style
description: Enforce C++ coding conventions for Qt-based ElaWidgetTools projects, including naming, formatting, D-pointer pattern, property macros, and comment style. Use when writing or modifying any C++ header or source file in this project.
---

# C++ Code Style (ElaWidgetTools)

## Naming Conventions

| Element | Convention | Example |
|---------|-----------|---------|
| Class | `Ela` prefix + PascalCase | `ElaPushButton` |
| Private class | `ElaXxxPrivate` | `ElaPushButtonPrivate` |
| File (.h/.cpp) | Same as class name | `ElaPushButton.h`, `ElaPushButton.cpp` |
| Private header | `ElaXxxPrivate.h` in `private/` dir | `private/ElaPushButtonPrivate.h` |
| Function | camelCase | `setLightTextColor()` |
| Getter | `get` + PascalCase | `getLightTextColor()` |
| Setter | `set` + PascalCase | `setLightTextColor()` |
| Member variable | `_` prefix + camelCase | `_isPressed`, `_themeMode` |
| Property backing | `_p` prefix + PascalCase | `_pBorderRadius`, `_pLightDefaultColor` |
| Enum namespace | `ElaXxxType` | `ElaThemeType`, `ElaNavigationType` |
| Enum value | PascalCase | `Light`, `Dark`, `Success` |
| Header guard | `ELAXXX_H` | `ELAPUSHBUTTON_H` |

## Code Formatting

- **Indent**: 4 spaces (no tabs)
- **Braces**: Allman style for functions (opening brace on new line); K&R for blocks (if/else/for)
- **Pointer**: Asterisk attached to type: `QWidget* parent`, not `QWidget *parent`
- **Include order**: own header → Qt headers → project headers
- **Forward declarations**: Use before includes when only references/pointers are needed

```cpp
// Header example
#ifndef ELAPUSHBUTTON_H
#define ELAPUSHBUTTON_H

#include <QPushButton>

#include "ElaProperty.h"
class ElaPushButtonPrivate;
class ELA_EXPORT ElaPushButton : public QPushButton
{
    Q_OBJECT
    // ...
};

#endif // ELAPUSHBUTTON_H
```

```cpp
// Source example
#include "ElaPushButton.h"

#include <QPainter>
#include <QPainterPath>

#include "ElaTheme.h"
#include "private/ElaPushButtonPrivate.h"
```

## Qt / Framework Patterns

### D-pointer (Private Implementation)

Public class header uses `Q_Q_CREATE` and property macros:

```cpp
class ELA_EXPORT ElaPushButton : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaPushButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_REF_CREATE_Q_H(QColor, LightDefaultColor)
public:
    explicit ElaPushButton(QWidget* parent = nullptr);
    ~ElaPushButton();
};
```

Private class header uses `Q_D_CREATE` and property macros:

```cpp
class ElaPushButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaPushButton)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(QColor, LightDefaultColor)
public:
    explicit ElaPushButtonPrivate(QObject* parent = nullptr);
    ~ElaPushButtonPrivate();

private:
    QColor _lightTextColor;
    bool _isPressed{false};
    int _shadowBorderWidth{3};
};
```

Source file property macro expansion (at top, before constructors):

```cpp
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, int, BorderRadius)
Q_PROPERTY_REF_CREATE_Q_CPP(ElaPushButton, QColor, LightDefaultColor)
```

### Constructor Pattern

```cpp
ElaPushButton::ElaPushButton(QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaPushButtonPrivate())
{
    Q_D(ElaPushButton);
    d->q_ptr = this;
    d->_pBorderRadius = 3;
    // initialization...
}
```

### Getter/Setter Pattern

```cpp
void ElaPushButton::setLightTextColor(const QColor& color)
{
    Q_D(ElaPushButton);
    d->_lightTextColor = color;
}

const QColor& ElaPushButton::getLightTextColor() const
{
    Q_D(const ElaPushButton);
    return d->_lightTextColor;
}
```

### Singleton Pattern

```cpp
class ELA_EXPORT ElaTheme : public QObject
{
    Q_OBJECT
    Q_Q_CREATE(ElaTheme)
    Q_SINGLETON_CREATE_H(ElaTheme)
private:
    explicit ElaTheme(QObject* parent = nullptr);
    ~ElaTheme();
public:
    // ...
};
// Usage: #define eTheme ElaTheme::getInstance()
```

### Signal Declaration

Use explicit `Q_SIGNAL` macro:

```cpp
Q_SIGNALS:
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void themeModeChanged(ElaThemeType::ThemeMode themeMode);
```

### Enum Definition

Use `Q_BEGIN_ENUM_CREATE` / `Q_END_ENUM_CREATE` macros:

```cpp
Q_BEGIN_ENUM_CREATE(ElaThemeType)
enum ThemeMode
{
    Light = 0x0000,
    Dark = 0x0001,
};
Q_ENUM_CREATE(ThemeMode)
Q_END_ENUM_CREATE(ElaThemeType)
```

### Export Macro

All public classes must use `ELA_EXPORT`:

```cpp
class ELA_EXPORT ElaPushButton : public QPushButton
```

## Comment Style

- **Language**: Chinese
- **Inline comments**: `//` placed before the code block
- **No space** between `//` and Chinese text

```cpp
// 高性能阴影
eTheme->drawEffectShadow(&painter, rect(), d->_shadowBorderWidth, d->_pBorderRadius);

// 背景绘制
painter.save();
```

## Override Keyword

Always use `override` for virtual function overrides:

```cpp
~ElaWindow() override;
virtual void paintEvent(QPaintEvent* event) override;
```

## Member Initialization

Use in-class initialization with braces for simple types:

```cpp
private:
    bool _isPressed{false};
    int _shadowBorderWidth{3};
```

## Explicit Constructor

Single-argument constructors must use `explicit`:

```cpp
explicit ElaPushButton(QWidget* parent = nullptr);
```
