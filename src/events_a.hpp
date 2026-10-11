#pragma once
#include "widgets.hpp"

namespace mm {
    inline std::vector<Fn> eventsA() {
        return {
            [](PlayLayer* p) { splash(p, "BONK", pal::AMBER, 1.8f, 0.5f, true); shake(p, 6.f, 6); sfx("explode_11.ogg", 1.8f); },
            [](PlayLayer* p) { splash(p, "OUCH", pal::PINK, 1.9f); tint(p, b4(pal::RED, 60), 1.f); sfx("explode_11.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "hm.", pal::WHITE, 2.2f); sfx("explode_11.ogg", 0.3f); },
            [](PlayLayer* p) { splash(p, "WOOOOSH", pal::CYAN, 1.2f); sfx("crystal01.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "nu takoe", pal::WHITE, 1.3f); },
            [](PlayLayer* p) { splash(p, "ya ne ponyal", pal::AMBER, 1.0f); },
            [](PlayLayer* p) { splash(p, "ZHEST", pal::RED, 2.2f, 0.5f, true); sfx("explode_11.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "vot eto povorot", pal::VIOLET, 0.95f); },
            [](PlayLayer* p) { splash(p, "L", pal::RED, 4.5f); sfx("quitSound_01.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "wait what", pal::WHITE, 1.2f); },
            [](PlayLayer* p) { splash(p, "meh", pal::GREY, 1.8f); },
            [](PlayLayer* p) { splash(p, "W", pal::LIME, 4.5f); sfx("achievement_01.ogg", 1.2f, 0.8f); },
            [](PlayLayer* p) { splash(p, "what was that", pal::WHITE, 1.0f, 0.6f); sfx("playSound_01.ogg", 0.4f); },
            [](PlayLayer* p) { splash(p, "ne nado", pal::GREY, 1.4f); },

            [](PlayLayer* p) { strip(p, "this level is now rated: tuesday", pal::AMBER, 0.5f, 1.8f, "RATED"); sfx("achievement_01.ogg", 0.8f); },
            [](PlayLayer* p) { strip(p, "you have been banned from the floor", pal::RED, 0.5f, 1.9f, "BAN"); },
            [](PlayLayer* p) { strip(p, "update 2.3 is out", pal::LIME, 0.62f, 1.8f, "NEWS"); strip(p, "it was a typo", pal::GREY, 0.36f, 1.8f, "NEWS"); },
            [](PlayLayer* p) { strip(p, "your skill level was moved to: cardboard", pal::VIOLET, 0.5f, 1.8f, "DEMOTED"); },
            [](PlayLayer* p) { strip(p, "attempt 9999, still counting", pal::CYAN, 0.5f, 1.6f, "STATS"); },
            [](PlayLayer* p) { strip(p, "result: a little bit of everything", pal::BLUE, 0.5f, 1.9f, "OK?"); },
            [](PlayLayer* p) { strip(p, "the dev has seen this before", pal::VIOLET, 0.5f, 1.9f, "DEV"); },
            [](PlayLayer* p) { strip(p, "this part is on purpose, probably", pal::LIME, 0.5f, 1.9f, "NOTE"); },
            [](PlayLayer* p) { strip(p, "this ad space is empty on purpose", pal::GREY, 0.18f, 2.f, "AD"); },
            [](PlayLayer* p) { strip(p, "next level: same, but longer", pal::PINK, 0.5f, 1.8f, "NEXT"); },

            [](PlayLayer* p) { toast(p, "Messages", "u there? it is about the level", pal::VIOLET); },
            [](PlayLayer* p) { toast(p, "Mom", "dinner is getting cold", pal::LIME); },
            [](PlayLayer* p) { toast(p, "Battery", "15%, find a charger", pal::RED); },
            [](PlayLayer* p) { toast(p, "Unknown number", "i know what you did", pal::AMBER); },
            [](PlayLayer* p) { toast(p, "Wi-Fi", "one bar, think it over", pal::CYAN, false); },
            [](PlayLayer* p) { toast(p, "Calendar", "exam in 5 minutes. which one", pal::PINK, false); },
        };
    }
}
