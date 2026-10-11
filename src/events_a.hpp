#pragma once
#include "widgets.hpp"

namespace mm {
    inline std::vector<Fn> eventsA() {
        return {
            [](PlayLayer* p) { splash(p, "BONK", pal::AMBER, 1.8f, 0.5f, true); shake(p, 6.f, 6); sfx("explode_11.ogg", 1.8f); },
            [](PlayLayer* p) { splash(p, "EMOTIONAL DAMAGE", pal::PINK, 0.9f); tint(p, b4(pal::RED, 60), 1.f); sfx("explode_11.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "bruh", pal::WHITE, 1.7f); sfx("explode_11.ogg", 0.3f); },
            [](PlayLayer* p) { splash(p, "SHEEEEESH", pal::CYAN, 0.95f); sfx("crystal01.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "nu takoe", pal::WHITE, 1.3f); },
            [](PlayLayer* p) { splash(p, "ya ne ponyal", pal::AMBER, 1.0f); },
            [](PlayLayer* p) { splash(p, "ZHEST", pal::RED, 2.2f, 0.5f, true); sfx("explode_11.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "vot eto povorot", pal::VIOLET, 0.95f); },
            [](PlayLayer* p) { splash(p, "L", pal::RED, 4.5f); sfx("quitSound_01.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "ratio", pal::WHITE, 1.7f); },
            [](PlayLayer* p) { splash(p, "cope.", pal::GREY, 1.5f); },
            [](PlayLayer* p) { splash(p, "W", pal::LIME, 4.5f); sfx("achievement_01.ogg", 1.2f, 0.8f); },
            [](PlayLayer* p) { splash(p, "tf was that", pal::WHITE, 1.1f, 0.6f); sfx("playSound_01.ogg", 0.4f); },
            [](PlayLayer* p) { splash(p, "NPC behavior", pal::GREY, 1.0f); },

            [](PlayLayer* p) { strip(p, "LEVEL RATED: INSANE DEMON", pal::AMBER, 0.5f, 1.8f, "RATED"); sfx("achievement_01.ogg", 0.8f); },
            [](PlayLayer* p) { strip(p, "you are banned from leaderboards", pal::RED, 0.5f, 1.9f, "BAN"); },
            [](PlayLayer* p) { strip(p, "gd 2.3 is out", pal::LIME, 0.62f, 1.8f, "NEWS"); strip(p, "lol no", pal::GREY, 0.36f, 1.8f, "UPDATE"); },
            [](PlayLayer* p) { strip(p, "demoted to practice mode", pal::VIOLET, 0.5f, 1.8f, "DEMOTED"); },
            [](PlayLayer* p) { strip(p, "attempt 9999", pal::CYAN, 0.5f, 1.6f, "STATS"); },
            [](PlayLayer* p) { strip(p, "task failed successfully", pal::BLUE, 0.5f, 1.9f, "OK?"); },
            [](PlayLayer* p) { strip(p, "works on my machine", pal::VIOLET, 0.5f, 1.9f, "DEV"); },
            [](PlayLayer* p) { strip(p, "it's not a bug, it's a feature", pal::LIME, 0.5f, 1.9f, "NOTE"); },
            [](PlayLayer* p) { strip(p, "sponsored by nobody", pal::GREY, 0.18f, 2.f, "AD"); },
            [](PlayLayer* p) { strip(p, "next level: harder", pal::PINK, 0.5f, 1.8f, "NEXT"); },

            [](PlayLayer* p) { toast(p, "Discord  @everyone", "new gd update is out", pal::VIOLET); },
            [](PlayLayer* p) { toast(p, "Mom", "come eat", pal::LIME); },
            [](PlayLayer* p) { toast(p, "Battery", "15% remaining", pal::RED); },
            [](PlayLayer* p) { toast(p, "Unknown number", "your car warranty expired", pal::AMBER); },
            [](PlayLayer* p) { toast(p, "Wi-Fi", "1 bar, good luck", pal::CYAN, false); },
            [](PlayLayer* p) { toast(p, "Calendar", "exam in 5 minutes", pal::PINK, false); },
        };
    }
}
