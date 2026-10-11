#pragma once
#include <Geode/Geode.hpp>
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

using namespace geode::prelude;

namespace mm {
    inline std::mt19937 rng{std::random_device{}()};
    inline int rnd(int n) { return std::uniform_int_distribution<int>(0, n - 1)(rng); }
    inline float rndf(float a, float b) { return std::uniform_real_distribution<float>(a, b)(rng); }

    inline bool opt(char const* key) { return Mod::get()->getSettingValue<bool>(key); }
    inline float interval() { return (float)Mod::get()->getSettingValue<int64_t>("chaos-interval"); }

    inline char const* const ROASTS[] = {
        "ez", "uninstall", "nope", "skill issue", "lmao", "tf was that", "bro", "nu takoe",
        "ya ne ponyal", "zhest", "again", "not even close", "cope", "L", "next", "nice try"
    };
    inline char const* const EARLY[] = {"first jump bro", "ten percent speedrun", "did you even start", "ya ne ponyal"};
    inline char const* const CLOSE[] = {"so close", "pain", "that was the win", "spike said no", "zhest"};
    inline char const* const STREAK[] = {"touch grass", "drink water", "try practice mode", "go to sleep", "nu takoe"};
    inline char const* const WINS[] = {"gg", "ez", "W", "sheesh", "legend", "who let him cook"};
    inline char const* const WORDS[] = {
        "SUS", "BRUH", "OOF", "NOICE", "WHAT", "L", "W", "SHEESH", "FR", "COPE", "BASED", "NPC", "RATIO", "ZHEST"
    };

    template <size_t N>
    char const* pick(char const* const (&a)[N]) { return a[rnd((int)N)]; }

    inline int deaths = 0;
    inline float chaosTimer = 0.f;
    inline float rainbowLeft = 0.f;
    inline float hue = 0.f;
    inline float viewLeft = 0.f;
    inline int viewMode = 0;
    inline CCPoint viewOrigin = {0.f, 0.f};
    inline int recent[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    inline void sfx(char const* name, float speed, float volume = 1.f) {
        if (opt("sounds")) FMODAudioEngine::sharedEngine()->playEffect(name, speed, 0.f, volume);
    }

    inline ccColor3B fromHue(float h) {
        float r = 0.5f + 0.5f * std::sin(h);
        float g = 0.5f + 0.5f * std::sin(h + 2.094f);
        float b = 0.5f + 0.5f * std::sin(h + 4.188f);
        return {(GLubyte)(r * 255), (GLubyte)(g * 255), (GLubyte)(b * 255)};
    }

    inline ccColor4F c4(float r, float g, float b, float a = 1.f) { return ccc4f(r, g, b, a); }
    inline CCSize W() { return CCDirector::get()->getWinSize(); }
}
