#pragma once
#include "widgets.hpp"

namespace mm {
    inline std::vector<Fn> eventsC() {
        return {
            [](PlayLayer* p) { // crash
                auto s = stage(p, ccc3(10, 70, 170), ccc3(4, 28, 90), pal::WHITE, 1.7f);
                float w = W().width, h = W().height;
                glitch(s.n, "game has crashed", 0.62f, pal::WHITE, {w / 2, h * 0.66f});
                label(s.n, "error 0x0000", 0.4f, {w / 2, h * 0.48f}, ccc3(190, 215, 255));
                roundRect(s.d, w * 0.25f, h * 0.26f, w * 0.5f, 12.f, 6.f, f4(pal::INK, 0.5f));
                roundRect(s.d, w * 0.25f, h * 0.26f, w * 0.5f * 0.37f, 12.f, 6.f, f4(pal::WHITE));
                sfx("explode_11.ogg", 0.35f);
            },
            [](PlayLayer* p) { // 404
                auto s = stage(p, ccc3(246, 246, 250), ccc3(214, 216, 228), pal::GREY, 1.5f);
                float w = W().width, h = W().height;
                label(s.n, "404", 2.8f, {w / 2 + 4.f, h * 0.6f - 4.f}, ccc3(190, 192, 205));
                label(s.n, "404", 2.8f, {w / 2, h * 0.6f}, ccc3(110, 112, 130));
                label(s.n, "level not found", 0.6f, {w / 2, h * 0.3f}, pal::INK);
            },
            [](PlayLayer* p) { // no signal
                auto s = stage(p, ccc3(0, 0, 0), ccc3(0, 0, 0), pal::WHITE, 1.5f);
                float w = W().width, h = W().height;
                ccColor3B cols[7] = {ccc3(190, 190, 190), ccc3(190, 190, 0), ccc3(0, 190, 190), ccc3(0, 190, 0),
                                     ccc3(190, 0, 190), ccc3(190, 0, 0), ccc3(0, 0, 190)};
                for (int i = 0; i < 7; i++) rect(s.d, i * w / 7.f, 0.f, w / 7.f + 1.f, h, f4(cols[i]));
                scanlines(s.d, 0.18f);
                roundRect(s.d, w * 0.2f, h * 0.38f, w * 0.6f, h * 0.24f, 14.f, f4(pal::INK, 0.92f));
                glitch(s.n, "NO SIGNAL", 0.85f, pal::WHITE, {w / 2, h * 0.5f});
            },
            [](PlayLayer* p) { // loading
                auto s = stage(p, ccc3(14, 14, 22), ccc3(4, 4, 8), pal::CYAN, 1.7f);
                float w = W().width, h = W().height;
                auto ring = CCDrawNode::create();
                ring->setPosition({w / 2, h * 0.56f});
                s.n->addChild(ring, 2);
                ccColor3B cols[3] = {pal::PINK, pal::CYAN, pal::LIME};
                for (int i = 0; i < 10; i++) {
                    float a = i * 0.6283f;
                    ring->drawDot({std::cos(a) * 36.f, std::sin(a) * 36.f}, 3.f + i * 0.5f, f4(cols[i % 3], 0.15f + 0.085f * i));
                }
                ring->runAction(CCRepeatForever::create(CCRotateBy::create(0.9f, -360.f)));
                label(s.n, "loading", 0.45f, {w / 2, h * 0.2f}, pal::GREY);
            },
            [](PlayLayer* p) { // lock screen
                auto s = stage(p, ccc3(34, 30, 70), ccc3(8, 10, 26), pal::VIOLET, 1.6f);
                float w = W().width, h = W().height;
                glitch(s.n, "03:47", 1.9f, pal::WHITE, {w / 2, h * 0.66f});
                roundRect(s.d, w * 0.3f, h * 0.22f, w * 0.4f, 34.f, 17.f, f4(pal::WHITE, 0.14f));
                label(s.n, "1 notification", 0.34f, {w / 2, h * 0.22f + 17.f}, ccc3(200, 205, 225));
                roundRect(s.d, w / 2 - 50.f, 22.f, 100.f, 4.f, 2.f, f4(pal::WHITE, 0.5f));
            },
            [](PlayLayer* p) { // black with caption
                static char const* const CAPS[] = {"...", "one sec", "buffering", "no way", "hold on"};
                auto s = stage(p, ccc3(0, 0, 0), ccc3(0, 0, 0), pal::GREY, 1.4f);
                label(s.n, CAPS[rnd(5)], 0.8f, {W().width / 2, W().height / 2}, pal::WHITE);
                sfx("explode_11.ogg", 0.4f);
            },
            [](PlayLayer* p) { // prize popup
                auto s = stage(p, ccc3(226, 228, 238), ccc3(196, 200, 218), pal::VIOLET, 1.7f);
                float w = W().width, h = W().height;
                roundRect(s.d, w * 0.1f, h * 0.7f, w * 0.8f, h * 0.2f, 14.f, f4(pal::PINK));
                glitch(s.n, "YOU WON", 0.8f, pal::WHITE, {w / 2, h * 0.8f});
                label(s.n, "a free phone", 0.65f, {w / 2, h * 0.54f}, pal::INK);
                roundRect(s.d, w * 0.3f, h * 0.16f, w * 0.4f, h * 0.17f, h * 0.085f, f4(pal::BLUE));
                label(s.n, "CLAIM", 0.55f, {w / 2, h * 0.245f}, pal::WHITE);
                sfx("quitSound_01.ogg", 0.8f);
            },
            [](PlayLayer* p) { // game over
                auto s = stage(p, ccc3(8, 6, 22), ccc3(0, 0, 0), pal::AMBER, 1.8f);
                float w = W().width, h = W().height;
                scanlines(s.d, 0.22f);
                glitch(s.n, "GAME OVER", 1.3f, pal::RED, {w / 2, h * 0.64f});
                roundRect(s.d, w * 0.3f, h * 0.24f, w * 0.4f, 38.f, 19.f, f4(pal::AMBER, 0.18f));
                label(s.n, "CONTINUE?  9", 0.6f, {w / 2, h * 0.24f + 19.f}, pal::AMBER);
                sfx("quitSound_01.ogg", 0.6f);
            },
            [](PlayLayer* p) { // failed exam
                auto s = stage(p, ccc3(250, 244, 226), ccc3(236, 226, 196), pal::GREY, 1.7f);
                float w = W().width, h = W().height;
                for (int i = 1; i < 9; i++) rect(s.d, 0.f, i * h / 9.f, w, 1.5f, f4(pal::BLUE, 0.25f));
                rect(s.d, w * 0.12f, 0.f, 2.f, h, f4(pal::RED, 0.35f));
                s.d->drawDot({w / 2, h * 0.5f}, 62.f, f4(pal::RED, 0.16f));
                label(s.n, "F", 4.6f, {w / 2, h * 0.5f}, pal::RED, -12.f);
                label(s.n, "see me after class", 0.4f, {w / 2, h * 0.88f}, pal::INK);
            },
            [](PlayLayer* p) { // floor is lava
                auto s = stage(p, ccc3(255, 214, 40), ccc3(255, 150, 20), pal::INK, 1.7f);
                float w = W().width, h = W().height;
                for (int i = -2; i < 14; i++) {
                    CCPoint a[4] = {{i * 60.f, 14.f}, {i * 60.f + 30.f, 14.f}, {i * 60.f + 60.f, 54.f}, {i * 60.f + 30.f, 54.f}};
                    CCPoint b[4] = {{i * 60.f, h - 54.f}, {i * 60.f + 30.f, h - 54.f}, {i * 60.f + 60.f, h - 14.f}, {i * 60.f + 30.f, h - 14.f}};
                    s.d->drawPolygon(a, 4, f4(pal::INK), 0.f, f4(pal::INK));
                    s.d->drawPolygon(b, 4, f4(pal::INK), 0.f, f4(pal::INK));
                }
                roundRect(s.d, w * 0.2f, h * 0.24f, w * 0.6f, h * 0.52f, 18.f, f4(pal::INK, 0.9f));
                label(s.n, "the floor", 0.95f, {w / 2, h * 0.62f}, pal::AMBER);
                glitch(s.n, "is lava", 1.4f, pal::WHITE, {w / 2, h * 0.38f});
                sfx("playSound_01.ogg", 0.5f);
            },
            [](PlayLayer* p) { // fake level complete
                auto s = stage(p, ccc3(24, 120, 60), ccc3(8, 56, 30), pal::LIME, 1.7f);
                float w = W().width, h = W().height;
                ccColor3B cols[4] = {pal::LIME, pal::AMBER, pal::CYAN, pal::WHITE};
                confetti(s.d, 40, cols, 4);
                glitch(s.n, "LEVEL COMPLETE!", 0.8f, pal::WHITE, {w / 2, h * 0.68f});
                label(s.n, "100%", 1.7f, {w / 2, h * 0.45f}, pal::AMBER);
                auto no = glitch(s.n, "nope", 0.9f, pal::RED, {w / 2, h * 0.2f});
                no->setVisible(false);
                no->runAction(CCSequence::create(CCDelayTime::create(0.9f), CCShow::create(), nullptr));
                sfx("achievement_01.ogg", 1.f);
            },
        };
    }
}
