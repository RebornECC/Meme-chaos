#pragma once
#include "ui.hpp"

namespace mm {
    inline void captcha(PlayLayer* p) {
        float w = 230.f, h = 190.f;
        auto box = CCLayerColor::create(ccc4(240, 240, 244, 255), w, h);
        auto d = CCDrawNode::create();
        box->addChild(d, 1);
        rect(d, 0.f, h - 28.f, w, 28.f, c4(0.1f, 0.35f, 0.9f));
        label(box, "select all spikes", 0.3f, {w / 2, h - 14.f}, ccc3(255, 255, 255), 0.f, "bigFont.fnt", 3);
        for (int i = 0; i < 9; i++) {
            float x = 12.f + (i % 3) * 70.f, y = h - 44.f - (i / 3) * 44.f - 36.f;
            rect(d, x, y, 66.f, 40.f, c4(0.55f, 0.58f, 0.65f));
            if (rnd(2)) {
                CCPoint t[3] = {{x + 18.f, y + 6.f}, {x + 48.f, y + 6.f}, {x + 33.f, y + 34.f}};
                d->drawPolygon(t, 3, c4(0.1f, 0.1f, 0.12f), 0.f, c4(0.1f, 0.1f, 0.12f));
            }
        }
        rect(d, w / 2 - 36.f, 4.f, 72.f, 18.f, c4(0.1f, 0.35f, 0.9f));
        label(box, "VERIFY", 0.26f, {w / 2, 13.f}, ccc3(255, 255, 255), 0.f, "bigFont.fnt", 3);
        box->setAnchorPoint({0.5f, 0.5f});
        box->ignoreAnchorPointForPosition(false);
        box->setPosition({W().width / 2, W().height / 2});
        box->setScale(0.1f);
        p->addChild(box, 2600);
        box->runAction(CCSequence::create(CCEaseBackOut::create(CCScaleTo::create(0.15f, 1.f)), CCDelayTime::create(2.f), CCRemoveSelf::create(), nullptr));
    }

    inline void crack(PlayLayer* p) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        CCPoint c = {W().width * rndf(0.3f, 0.7f), W().height * rndf(0.3f, 0.7f)};
        for (int i = 0; i < 9; i++) {
            float a = i * 0.698f + rndf(-0.2f, 0.2f);
            CCPoint prev = c;
            float len = 0.f;
            while (len < 360.f) {
                float step = rndf(30.f, 60.f);
                a += rndf(-0.25f, 0.25f);
                CCPoint next = {prev.x + std::cos(a) * step, prev.y + std::sin(a) * step};
                d->drawSegment(prev, next, 1.1f, c4(1.f, 1.f, 1.f, 0.9f));
                prev = next;
                len += step;
            }
        }
        for (int r = 1; r < 4; r++) d->drawSegment({c.x - 30.f * r, c.y - 10.f * r}, {c.x + 25.f * r, c.y + 18.f * r}, 0.8f, c4(1.f, 1.f, 1.f, 0.6f));
        p->addChild(n, 2800);
        later(n, 2.2f);
        sfx("explode_11.ogg", 1.9f);
    }

    inline void cursor(PlayLayer* p) {
        auto d = CCDrawNode::create();
        CCPoint a[3] = {{0.f, 0.f}, {0.f, -34.f}, {24.f, -24.f}};
        CCPoint b[4] = {{8.f, -22.f}, {16.f, -26.f}, {24.f, -44.f}, {16.f, -48.f}};
        CCPoint a2[3] = {{-2.f, 3.f}, {-2.f, -38.f}, {29.f, -25.f}};
        d->drawPolygon(a2, 3, c4(0.f, 0.f, 0.f), 0.f, c4(0.f, 0.f, 0.f));
        d->drawPolygon(a, 3, c4(1.f, 1.f, 1.f), 0.f, c4(1.f, 1.f, 1.f));
        d->drawPolygon(b, 4, c4(1.f, 1.f, 1.f), 1.f, c4(0.f, 0.f, 0.f));
        d->setPosition({-40.f, W().height * 0.7f});
        p->addChild(d, 2900);
        d->runAction(CCSequence::create(
            CCMoveTo::create(1.2f, {W().width * 0.5f, W().height * 0.45f}), CCDelayTime::create(0.3f),
            CCMoveTo::create(0.6f, {W().width + 60.f, W().height * 0.2f}), CCRemoveSelf::create(), nullptr));
        sfx("playSound_01.ogg", 2.f, 0.5f);
    }

    inline void bounce(PlayLayer* p) {
        auto box = CCLayerColor::create(ccc4(rnd(200) + 55, rnd(200) + 55, rnd(200) + 55, 255), 96.f, 48.f);
        label(box, "GD", 0.8f, {48.f, 24.f}, ccc3(255, 255, 255));
        float w = W().width - 96.f, h = W().height - 48.f;
        box->setPosition({rndf(0.f, w), rndf(0.f, h)});
        p->addChild(box, 2300);
        box->runAction(CCSequence::create(
            CCMoveTo::create(0.9f, {w, h * 0.5f}), CCMoveTo::create(0.9f, {w * 0.5f, 0.f}), CCMoveTo::create(0.9f, {0.f, h}),
            CCMoveTo::create(0.9f, {w, h * 0.2f}), CCMoveTo::create(0.9f, {w * 0.3f, h}), CCRemoveSelf::create(), nullptr));
    }

    inline void ticker(PlayLayer* p) {
        static char const* const NEWS[] = {
            "player dies again, sources say", "local man blames lag, lag denies it",
            "spike unharmed in incident", "experts confirm: it was the spike", "breaking: nothing happened"
        };
        auto bar = CCLayerColor::create(ccc4(20, 20, 24, 235), W().width, 26.f);
        bar->setPosition({0.f, 0.f});
        auto tag = CCLayerColor::create(ccc4(200, 20, 20, 255), 84.f, 26.f);
        auto t = label(bar, NEWS[rnd(5)], 0.34f, {W().width + 20.f, 13.f});
        t->setAnchorPoint({0.f, 0.5f});
        t->runAction(CCMoveTo::create(3.6f, {-W().width, 13.f}));
        bar->addChild(tag, 10);
        label(tag, "BREAKING", 0.26f, {42.f, 13.f});
        p->addChild(bar, 2500);
        later(bar, 3.7f);
    }

    inline void rec(PlayLayer* p) {
        auto n = CCDrawNode::create();
        n->drawDot({22.f, W().height - 20.f}, 7.f, c4(1.f, 0.1f, 0.1f));
        auto l = label(n, "REC", 0.4f, {38.f, W().height - 20.f}, ccc3(255, 255, 255));
        l->setAnchorPoint({0.f, 0.5f});
        p->addChild(n, 2700);
        n->runAction(CCBlink::create(2.4f, 4));
        later(n, 2.5f);
    }

    inline void cinema(PlayLayer* p, char const* caption) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        rect(d, 0.f, W().height - 46.f, W().width, 46.f, c4(0.f, 0.f, 0.f));
        rect(d, 0.f, 0.f, W().width, 46.f, c4(0.f, 0.f, 0.f));
        label(n, caption, 0.4f, {W().width / 2, 23.f}, ccc3(255, 255, 255));
        p->addChild(n, 2800);
        later(n, 2.f);
    }

    inline void pauseIcon(PlayLayer* p) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        rect(d, 0.f, 0.f, W().width, W().height, c4(0.f, 0.f, 0.f, 0.35f));
        rect(d, W().width / 2 - 38.f, W().height / 2 - 46.f, 28.f, 92.f, c4(1.f, 1.f, 1.f, 0.9f));
        rect(d, W().width / 2 + 10.f, W().height / 2 - 46.f, 28.f, 92.f, c4(1.f, 1.f, 1.f, 0.9f));
        p->addChild(n, 2800);
        later(n, 1.8f);
    }

    inline void wordRain(PlayLayer* p) {
        for (int i = 0; i < 9; i++) {
            auto l = CCLabelBMFont::create(pick(WORDS), "bigFont.fnt");
            l->setColor(fromHue(rndf(0.f, 6.28f)));
            l->setScale(rndf(0.5f, 0.9f));
            float x = rndf(40.f, W().width - 40.f);
            l->setPosition({x, W().height + 30.f});
            l->setVisible(false);
            p->addChild(l, 2000);
            l->runAction(CCSequence::create(
                CCDelayTime::create(i * 0.18f), CCShow::create(),
                CCSpawn::create(CCMoveTo::create(1.6f, {x + rndf(-40.f, 40.f), -40.f}), CCRotateBy::create(1.6f, rndf(-360.f, 360.f)), nullptr),
                CCRemoveSelf::create(), nullptr));
        }
    }

    inline void flyby(PlayLayer* p) {
        auto l = CCLabelBMFont::create(pick(WORDS), "bigFont.fnt");
        l->setColor(fromHue(rndf(0.f, 6.28f)));
        l->setScale(rndf(0.8f, 1.4f));
        float y = rndf(W().height * 0.2f, W().height * 0.8f);
        l->setPosition({W().width + 80.f, y});
        p->addChild(l, 2000);
        l->runAction(CCSequence::create(
            CCSpawn::create(CCMoveTo::create(2.2f, {-120.f, y + rndf(-60.f, 60.f)}), CCRotateBy::create(2.2f, rndf(-540.f, 540.f)), nullptr),
            CCRemoveSelf::create(), nullptr));
    }

    inline std::vector<Fn> eventsB() {
        return {
            [](PlayLayer* p) { dialog(p, "Error", "An error has occurred.\nThe error is: error.", "OK", ccc4(20, 60, 150, 255)); sfx("quitSound_01.ogg", 0.8f); },
            [](PlayLayer* p) { dialog(p, "Incoming call", "nobody is calling\nanswer anyway", "Accept", ccc4(30, 130, 60, 255)); sfx("playSound_01.ogg", 1.4f); },
            [](PlayLayer* p) { dialog(p, "Storage full", "delete 3 photos to keep playing", "Delete", ccc4(200, 110, 20, 255)); },
            [](PlayLayer* p) { dialog(p, "Cookies", "we use cookies. accept?\n[ yes ]     [ yes ]", "Accept", ccc4(70, 70, 76, 255)); },
            [](PlayLayer* p) { dialog(p, "Update available", "restart now to update", "Later", ccc4(20, 60, 150, 255)); },
            [](PlayLayer* p) { dialog(p, "Hello?", "are you still playing?", "Yes", ccc4(190, 30, 30, 255)); },
            [](PlayLayer* p) { dialog(p, "Terms", "scroll to accept\npage 1 of 9999", "Scroll", ccc4(70, 70, 76, 255)); },
            [](PlayLayer* p) { captcha(p); },
            [](PlayLayer* p) { crack(p); },
            [](PlayLayer* p) { cursor(p); },
            [](PlayLayer* p) { bounce(p); },
            [](PlayLayer* p) { ticker(p); },
            [](PlayLayer* p) { rec(p); },
            [](PlayLayer* p) { cinema(p, "[vine boom]"); sfx("explode_11.ogg", 0.4f); },
            [](PlayLayer* p) { cinema(p, "[sad violin]"); },
            [](PlayLayer* p) { cinema(p, "[tense music]"); },
            [](PlayLayer* p) { pauseIcon(p); },
            [](PlayLayer* p) { wordRain(p); },
            [](PlayLayer* p) { flyby(p); flyby(p); },
            [](PlayLayer* p) { flash(p); sfx("playSound_01.ogg", rndf(0.4f, 1.6f)); },
            [](PlayLayer* p) { rainbowLeft = 4.f; },
            [](PlayLayer* p) {
                if (!opt("lag")) { flash(p); return; }
                lagStart();
                auto l = label(p, "FPS: 5", 0.5f, {60.f, W().height - 20.f}, ccc3(255, 80, 80));
                later(l, 2.8f);
            },
            [](PlayLayer* p) { if (opt("mirror") && viewMode == 0) setView(p, 1); else flash(p); },
            [](PlayLayer* p) { if (opt("mirror") && viewMode == 0) setView(p, 2); else flash(p); },
        };
    }
}
