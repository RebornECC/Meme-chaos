#pragma once
#include "ui.hpp"

namespace mm {
    inline std::vector<Fn> eventsA() {
        auto white = ccc3(255, 255, 255);
        (void)white;
        return {
            [](PlayLayer* p) { splash(p, "BONK", ccc3(255, 230, 90), 1.8f, 0.5f, true); shake(p, 6.f, 6); sfx("explode_11.ogg", 1.8f); },
            [](PlayLayer* p) { splash(p, "EMOTIONAL DAMAGE", ccc3(255, 70, 70), 0.9f); tint(p, ccc4(200, 0, 0, 70), 1.f); sfx("explode_11.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "bruh", ccc3(255, 255, 255), 1.7f); sfx("explode_11.ogg", 0.3f); },
            [](PlayLayer* p) { splash(p, "SHEEEEESH", ccc3(120, 230, 255), 0.95f); sfx("crystal01.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "nu takoe", ccc3(255, 255, 255), 1.3f); },
            [](PlayLayer* p) { splash(p, "ya ne ponyal", ccc3(255, 225, 90), 1.0f); },
            [](PlayLayer* p) { splash(p, "ZHEST", ccc3(255, 60, 60), 2.2f, 0.5f, true); sfx("explode_11.ogg", 0.6f); },
            [](PlayLayer* p) { splash(p, "vot eto povorot", ccc3(255, 160, 60), 0.95f); },
            [](PlayLayer* p) { splash(p, "L", ccc3(255, 60, 60), 4.5f); sfx("quitSound_01.ogg", 0.5f); },
            [](PlayLayer* p) { splash(p, "ratio", ccc3(255, 255, 255), 1.7f); },
            [](PlayLayer* p) { splash(p, "cope.", ccc3(160, 160, 170), 1.5f); },
            [](PlayLayer* p) { splash(p, "W", ccc3(90, 255, 130), 4.5f); sfx("achievement_01.ogg", 1.2f, 0.8f); },
            [](PlayLayer* p) { splash(p, "tf was that", ccc3(255, 255, 255), 1.1f, 0.6f); sfx("playSound_01.ogg", 0.4f); },
            [](PlayLayer* p) { splash(p, "NPC behavior", ccc3(200, 200, 210), 1.0f); },

            [](PlayLayer* p) { strip(p, "LEVEL RATED: INSANE DEMON", ccc4(200, 150, 20, 235), ccc3(30, 20, 0), 0.5f, 1.8f, 0.6f); sfx("achievement_01.ogg", 0.8f); },
            [](PlayLayer* p) { strip(p, "you are banned from leaderboards", ccc4(190, 20, 20, 235), ccc3(255, 255, 255), 0.5f, 1.9f, 0.5f); },
            [](PlayLayer* p) { strip(p, "gd 2.3 is out", ccc4(40, 150, 70, 235), ccc3(255, 255, 255), 0.62f, 1.8f); strip(p, "lol no", ccc4(20, 20, 20, 235), ccc3(255, 255, 255), 0.36f, 1.8f); },
            [](PlayLayer* p) { strip(p, "demoted to practice mode", ccc4(80, 80, 90, 235), ccc3(255, 255, 255), 0.5f, 1.8f, 0.6f); },
            [](PlayLayer* p) { strip(p, "attempt 9999", ccc4(15, 15, 18, 240), ccc3(255, 255, 255), 0.5f, 1.6f, 1.0f); },
            [](PlayLayer* p) { strip(p, "task failed successfully", ccc4(30, 90, 170, 235), ccc3(255, 255, 255), 0.5f, 1.9f, 0.6f); },
            [](PlayLayer* p) { strip(p, "works on my machine", ccc4(100, 50, 160, 235), ccc3(255, 255, 255), 0.5f, 1.9f, 0.6f); },
            [](PlayLayer* p) { strip(p, "it's not a bug, it's a feature", ccc4(30, 30, 30, 235), ccc3(120, 255, 140), 0.5f, 1.9f, 0.5f); },
            [](PlayLayer* p) { strip(p, "sponsored by nobody", ccc4(220, 220, 225, 240), ccc3(20, 20, 25), 0.18f, 2.f, 0.6f); },
            [](PlayLayer* p) { strip(p, "next level: harder", ccc4(20, 20, 20, 235), ccc3(255, 90, 90), 0.5f, 1.8f, 0.7f); },

            [](PlayLayer* p) { toast(p, "Discord  @everyone", "new gd update is out"); },
            [](PlayLayer* p) { toast(p, "Mom", "come eat"); },
            [](PlayLayer* p) { toast(p, "Battery", "15% remaining"); },
            [](PlayLayer* p) { toast(p, "Unknown number", "your car warranty expired"); },
            [](PlayLayer* p) { toast(p, "Wi-Fi", "1 bar, good luck", false); },
            [](PlayLayer* p) { toast(p, "Calendar", "exam in 5 minutes", false); },
        };
    }
}
