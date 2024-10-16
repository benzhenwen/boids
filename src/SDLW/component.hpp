#pragma once

#include <SDL2/SDL.h>

#include <iostream>

namespace SDLW {

struct Color: public SDL_Color {
    bool operator==(Color other) {
        return
            r == other.r &&
            g == other.g &&
            b == other.b &&
            a == other.a;
    }
};

class Component {
friend class Window;

private:
    bool staged = false;

protected:
template <typename T>
struct Stagable {
protected:
    T value;
    Component & component;
public:
    Stagable(T _value, Component & _component):
    value(_value), component(_component) {}

    [[nodiscard]] operator const T&() const { 
        return value; 
    }
    inline void operator=(T other) {
        value = other;
        component.staged = true;
    }
    inline void operator+=(T other) {
        value += other;
        component.staged = true;
    }
    inline void operator-=(T other) {
        value -= other;
        component.staged = true;
    }
    inline void operator*=(T other) {
        value *= other;
        component.staged = true;
    }
    inline void operator/=(T other) {
        value /= other;
        component.staged = true;
    }
    inline void operator&=(T other) {
        value &= other;
        component.staged = true;
    }
    inline void operator|=(T other) {
        value |= other;
        component.staged = true;
    }
    inline void operator^=(T other) {
        value ^= other;
        component.staged = true;
    }
    inline void operator<<=(T other) {
        value <<= other;
        component.staged = true;
    }
    inline void operator>>=(T other) {
        value >>= other;
        component.staged = true;
    }
};

public:
    Stagable<float> x, y;

struct Rotated {
    Stagable<float> rotation;
    Rotated(float _rotation, Component & component): rotation(_rotation, component) {}
};
struct Colored {
    Stagable<Color> color;
    Colored(Color _color, Component & component): color(_color, component) {}
};

protected:
    Component(float _x, float _y):
    x(_x, *this), 
    y(_y, *this) {}

    virtual void push_stage() = 0;
    virtual void render_to(SDL_Renderer * renderer) = 0;
    inline void update(SDL_Renderer * renderer) {
        if (staged) {
            push_stage();
            staged = false;
        }
        render_to(renderer);
    }
};
}