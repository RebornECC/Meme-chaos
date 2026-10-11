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
        "the spike was right there", "gravity 1, you 0", "that was a choice", "hm.", "noted",
        "nu takoe", "ya ne ponyal", "zhest", "again", "the floor won", "pls no", "kosyak", "eh", "ok, again"
    };
    inline char const* const EARLY[] = {"that was the tutorial", "blink and it is over", "warm-up, right", "ya ne ponyal"};
    inline char const* const CLOSE[] = {"one pixel off", "the spike heard you", "almost, in a way", "so close it hurts", "zhest"};
    inline char const* const STREAK[] = {"ten. it is a number", "the level is not leaving", "drink some water", "try practice mode", "nu takoe"};
    inline char const* const WINS[] = {"finally", "nobody saw that", "ok, that was clean", "done. go outside", "again? no"};
    inline char const* const WORDS[] = {
        "OOF", "HMM", "UH", "AAA", "NOPE", "WAIT", "HELP", "NU", "YEP", "ZHEST", "KEK", "EH"
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
    inline float lagLeft = 0.f;
    inline double lagSaved = 1.0 / 60.0;
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

    inline void lagStart() {
        if (lagLeft > 0.f) return;
        lagSaved = CCDirector::get()->getAnimationInterval();
        CCDirector::get()->setAnimationInterval(1.0 / 5.0);
        lagLeft = 3.f;
    }

    inline void lagEnd() {
        if (lagLeft <= 0.f) return;
        lagLeft = 0.f;
        CCDirector::get()->setAnimationInterval(lagSaved);
    }

    namespace pal {
        inline ccColor3B const INK{16, 14, 30}, PAPER{244, 244, 250}, PINK{255, 64, 110}, CYAN{60, 210, 255}, LIME{140, 255, 120},
            AMBER{255, 196, 60}, VIOLET{160, 110, 255}, GREY{150, 156, 176}, RED{230, 50, 60}, BLUE{50, 100, 230}, WHITE{255, 255, 255};
    }
    inline ccColor4F f4(ccColor3B c, float a = 1.f) { return ccc4f(c.r / 255.f, c.g / 255.f, c.b / 255.f, a); }
    inline ccColor4B b4(ccColor3B c, int a = 255) { return ccc4(c.r, c.g, c.b, a); }
    inline ccColor4F c4(float r, float g, float b, float a = 1.f) { return ccc4f(r, g, b, a); }
    inline CCSize W() { return CCDirector::get()->getWinSize(); }
}
