#pragma once
#include "ui.hpp"

namespace mm {
    inline std::vector<Fn> eventsC() {
        return {
            [](PlayLayer* p) { // crash
                auto n = screen(p);
                auto d = canvas(n, c4(0.f, 0.28f, 0.63f));
                labelF(n, "game has crashed", 0.5f, 0.68f, 0.85f);
                labelF(n, "error 0x0000", 0.5f, 0.5f, 0.4f, ccc3(190, 215, 255));
                rect(d, W().width * 0.25f, W().height * 0.25f, W().width * 0.5f, 10.f, c4(0.f, 0.15f, 0.4f));
                rect(d, W().width * 0.25f, W().height * 0.25f, W().width * 0.5f * 0.37f, 10.f, c4(1.f, 1.f, 1.f));
                sfx("explode_11.ogg", 0.35f);
            },
            [](PlayLayer* p) { // 404
                auto n = screen(p);
                canvas(n, c4(0.96f, 0.96f, 0.97f));
                labelF(n, "404", 0.5f, 0.62f, 2.8f, ccc3(120, 120, 130));
                labelF(n, "level not found", 0.5f, 0.34f, 0.7f, ccc3(40, 40, 50));
            },
            [](PlayLayer* p) { // no signal
                auto n = screen(p);
                auto d = canvas(n, c4(0.f, 0.f, 0.f));
                float cols[7][3] = {{.75f,.75f,.75f},{.75f,.75f,0.f},{0.f,.75f,.75f},{0.f,.75f,0.f},{.75f,0.f,.75f},{.75f,0.f,0.f},{0.f,0.f,.75f}};
                for (int i = 0; i < 7; i++) rect(d, i * W().width / 7.f, 0.f, W().width / 7.f + 1.f, W().height, c4(cols[i][0], cols[i][1], cols[i][2]));
                rect(d, W().width * 0.2f, W().height * 0.38f, W().width * 0.6f, W().height * 0.24f, c4(0.f, 0.f, 0.f));
                labelF(n, "NO SIGNAL", 0.5f, 0.5f, 1.1f);
            },
            [](PlayLayer* p) { // loading
                auto n = screen(p);
                canvas(n, c4(0.02f, 0.02f, 0.03f));
                auto ring = CCDrawNode::create();
                ring->setPosition({W().width / 2, W().height * 0.55f});
                n->addChild(ring, 1);
                for (int i = 0; i < 8; i++) ring->drawDot({std::cos(i * 0.7854f) * 34.f, std::sin(i * 0.7854f) * 34.f}, 6.f, c4(1.f, 1.f, 1.f, 0.15f + 0.1f * i));
                ring->runAction(CCRepeatForever::create(CCRotateBy::create(0.9f, -360.f)));
                labelF(n, "loading...", 0.5f, 0.2f, 0.5f);
            },
            [](PlayLayer* p) { // lock screen
                auto n = screen(p);
                canvas(n, c4(0.08f, 0.09f, 0.16f));
                labelF(n, "03:47", 0.5f, 0.64f, 2.3f);
                labelF(n, "1 notification", 0.5f, 0.38f, 0.4f, ccc3(170, 175, 200));
            },
            [](PlayLayer* p) { // black with caption
                static char const* const CAPS[] = {"...", "one sec", "buffering", "no way", "hold on"};
                auto n = screen(p, 1.5f);
                canvas(n, c4(0.f, 0.f, 0.f));
                labelF(n, CAPS[rnd(5)], 0.5f, 0.5f, 0.8f);
                sfx("explode_11.ogg", 0.4f);
            },
            [](PlayLayer* p) { // prize popup
                auto n = screen(p);
                auto d = canvas(n, c4(0.86f, 0.87f, 0.9f));
                rect(d, 0.f, W().height * 0.78f, W().width, W().height * 0.22f, c4(0.8f, 0.1f, 0.1f));
                labelF(n, "YOU WON", 0.5f, 0.89f, 0.9f);
                labelF(n, "a free phone", 0.5f, 0.6f, 0.7f, ccc3(40, 40, 50));
                rect(d, W().width * 0.28f, W().height * 0.2f, W().width * 0.44f, W().height * 0.16f, c4(0.1f, 0.4f, 0.9f));
                labelF(n, "CLAIM", 0.5f, 0.28f, 0.6f);
                sfx("quitSound_01.ogg", 0.8f);
            },
            [](PlayLayer* p) { // game over
                auto n = screen(p);
                auto d = canvas(n, c4(0.02f, 0.02f, 0.06f));
                float w = W().width, h = W().height;
                rect(d, 10.f, 10.f, w - 20.f, 4.f, c4(1.f, 0.85f, 0.1f));
                rect(d, 10.f, h - 14.f, w - 20.f, 4.f, c4(1.f, 0.85f, 0.1f));
                rect(d, 10.f, 10.f, 4.f, h - 20.f, c4(1.f, 0.85f, 0.1f));
                rect(d, w - 14.f, 10.f, 4.f, h - 20.f, c4(1.f, 0.85f, 0.1f));
                labelF(n, "GAME OVER", 0.5f, 0.64f, 1.5f, ccc3(255, 60, 60));
                labelF(n, "CONTINUE?  9", 0.5f, 0.4f, 0.8f, ccc3(255, 220, 60));
                sfx("quitSound_01.ogg", 0.6f);
            },
            [](PlayLayer* p) { // failed exam
                auto n = screen(p);
                auto d = canvas(n, c4(0.96f, 0.92f, 0.82f));
                for (int i = 1; i < 8; i++) rect(d, 0.f, i * W().height / 8.f, W().width, 1.5f, c4(0.7f, 0.8f, 0.95f));
                labelF(n, "F", 0.5f, 0.52f, 5.f, ccc3(200, 30, 30), -12.f);
                labelF(n, "see me after class", 0.5f, 0.88f, 0.4f, ccc3(60, 60, 80));
            },
            [](PlayLayer* p) { // floor is lava
                auto n = screen(p);
                auto d = canvas(n, c4(1.f, 0.82f, 0.05f));
                float h = W().height;
                for (int i = -2; i < 14; i++) {
                    CCPoint a[4] = {{i * 60.f, 0.f}, {i * 60.f + 30.f, 0.f}, {i * 60.f + 60.f, 44.f}, {i * 60.f + 30.f, 44.f}};
                    CCPoint b[4] = {{i * 60.f, h - 44.f}, {i * 60.f + 30.f, h - 44.f}, {i * 60.f + 60.f, h}, {i * 60.f + 30.f, h}};
                    d->drawPolygon(a, 4, c4(.05f, .05f, .05f), 0.f, c4(.05f, .05f, .05f));
                    d->drawPolygon(b, 4, c4(.05f, .05f, .05f), 0.f, c4(.05f, .05f, .05f));
                }
                labelF(n, "the floor", 0.5f, 0.64f, 1.2f, ccc3(15, 15, 15));
                labelF(n, "is lava", 0.5f, 0.38f, 1.7f, ccc3(15, 15, 15));
                sfx("playSound_01.ogg", 0.5f);
            },
            [](PlayLayer* p) { // fake level complete
                auto n = screen(p, 1.7f);
                canvas(n, c4(0.1f, 0.5f, 0.2f));
                labelF(n, "LEVEL COMPLETE!", 0.5f, 0.66f, 0.9f);
                labelF(n, "100%", 0.5f, 0.44f, 1.8f, ccc3(255, 240, 120));
                auto no = labelF(n, "nope", 0.5f, 0.22f, 0.9f, ccc3(255, 70, 70));
                no->setVisible(false);
                no->runAction(CCSequence::create(CCDelayTime::create(0.9f), CCShow::create(), nullptr));
                sfx("achievement_01.ogg", 1.f);
            },
        };
    }
}
