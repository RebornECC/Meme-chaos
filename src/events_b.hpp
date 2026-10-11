#pragma once
#include "widgets.hpp"

namespace mm {
    inline void captcha(PlayLayer* p) {
        float w = 250.f, h = 214.f;
        auto n = card(p, w, h, f4(pal::INK, 0.97f), f4(pal::BLUE), 16.f);
        auto d = drawOf(n);
        roundRect(d, 0.f, h - 32.f, w, 32.f, 16.f, f4(pal::BLUE, 0.3f));
        auto t = label(n, "select all spikes", 0.3f, {16.f, h - 16.f}, pal::CYAN);
        t->setAnchorPoint({0.f, 0.5f});
        for (int i = 0; i < 9; i++) {
            float x = 14.f + (i % 3) * 77.f, y = h - 44.f - (i / 3) * 49.f - 40.f;
            roundRect(d, x, y, 72.f, 44.f, 8.f, f4(ccc3(44, 48, 68)));
            if (rnd(2)) {
                CCPoint tri[3] = {{x + 22.f, y + 8.f}, {x + 50.f, y + 8.f}, {x + 36.f, y + 36.f}};
                d->drawPolygon(tri, 3, f4(pal::PAPER), 0.f, f4(pal::PAPER));
            }
        }
        auto v = label(n, "VERIFY", 0.28f, {w / 2, 17.f}, pal::INK, 0.f, FONT, 6);
        roundRect(d, w / 2 - 40.f, 6.f, 80.f, 22.f, 11.f, f4(pal::CYAN));
        (void)v;
        n->setPosition({W().width / 2, W().height / 2});
        popCard(n, 2.f);
    }

    inline void crack(PlayLayer* p) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        CCPoint c = {W().width * rndf(0.3f, 0.7f), W().height * rndf(0.3f, 0.7f)};
        for (int i = 0; i < 10; i++) {
            float a = i * 0.628f + rndf(-0.2f, 0.2f);
            CCPoint prev = c;
            float len = 0.f;
            while (len < 380.f) {
                float step = rndf(30.f, 60.f);
                a += rndf(-0.25f, 0.25f);
                CCPoint next = {prev.x + std::cos(a) * step, prev.y + std::sin(a) * step};
                d->drawSegment(prev, next, 1.1f, ccc4f(1.f, 1.f, 1.f, 0.9f));
                d->drawSegment({prev.x + 2.f, prev.y - 2.f}, {next.x + 2.f, next.y - 2.f}, 0.7f, ccc4f(0.f, 0.f, 0.f, 0.35f));
                prev = next;
                len += step;
            }
        }
        d->drawDot(c, 5.f, ccc4f(1.f, 1.f, 1.f, 0.9f));
        p->addChild(n, 2800);
        later(n, 2.2f);
        sfx("explode_11.ogg", 1.9f);
    }

    inline void cursor(PlayLayer* p) {
        auto d = CCDrawNode::create();
        CCPoint outline[3] = {{-2.f, 3.f}, {-2.f, -38.f}, {29.f, -25.f}};
        CCPoint a[3] = {{0.f, 0.f}, {0.f, -34.f}, {24.f, -24.f}};
        CCPoint b[4] = {{8.f, -22.f}, {16.f, -26.f}, {24.f, -44.f}, {16.f, -48.f}};
        d->drawPolygon(outline, 3, ccc4f(0.f, 0.f, 0.f, 1.f), 0.f, ccc4f(0.f, 0.f, 0.f, 1.f));
        d->drawPolygon(a, 3, f4(pal::WHITE), 0.f, f4(pal::WHITE));
        d->drawPolygon(b, 4, f4(pal::WHITE), 1.f, ccc4f(0.f, 0.f, 0.f, 1.f));
        d->setScale(1.4f);
        d->setPosition({-50.f, W().height * 0.7f});
        p->addChild(d, 2900);
        d->runAction(CCSequence::create(
            CCEaseInOut::create(CCMoveTo::create(1.2f, {W().width * 0.5f, W().height * 0.45f}), 2.f), CCDelayTime::create(0.3f),
            CCMoveTo::create(0.6f, {W().width + 70.f, W().height * 0.2f}), CCRemoveSelf::create(), nullptr));
        sfx("playSound_01.ogg", 2.f, 0.5f);
    }

    inline void bounce(PlayLayer* p) {
        ccColor3B cols[4] = {pal::PINK, pal::CYAN, pal::LIME, pal::AMBER};
        auto col = cols[rnd(4)];
        auto n = card(p, 104.f, 52.f, f4(pal::INK, 0.95f), f4(col), 12.f, 2300);
        glitch(n, "GD", 0.8f, col, {52.f, 26.f});
        float x0 = 52.f, x1 = W().width - 52.f, y0 = 26.f, y1 = W().height - 26.f;
        n->setPosition({rndf(x0, x1), rndf(y0, y1)});
        n->runAction(CCSequence::create(
            CCMoveTo::create(0.9f, {x1, (y0 + y1) * 0.5f}), CCMoveTo::create(0.9f, {(x0 + x1) * 0.5f, y0}), CCMoveTo::create(0.9f, {x0, y1}),
            CCMoveTo::create(0.9f, {x1, y0 + 30.f}), CCMoveTo::create(0.9f, {x0 + 80.f, y1}), CCRemoveSelf::create(), nullptr));
    }

    inline void ticker(PlayLayer* p) {
        static char const* const NEWS[] = {
            "a man pressed jump, and it ended", "the spike has no comment",
            "lag blamed, lag denies", "witness saw the whole thing, says nothing", "today: slightly bad weather"
        };
        auto bar = CCLayerColor::create(b4(pal::INK, 240), W().width, 28.f);
        auto t = label(bar, NEWS[rnd(5)], 0.34f, {W().width + 20.f, 14.f});
        t->setAnchorPoint({0.f, 0.5f});
        t->runAction(CCMoveTo::create(3.6f, {-W().width, 14.f}));
        auto tag = CCLayerColor::create(b4(pal::PINK), 74.f, 28.f);
        bar->addChild(tag, 10);
        label(tag, "LIVE", 0.3f, {37.f, 14.f}, pal::WHITE);
        auto line = CCLayerColor::create(b4(pal::PINK), W().width, 2.f);
        line->setPosition({0.f, 28.f});
        bar->addChild(line, 1);
        p->addChild(bar, 2500);
        later(bar, 3.7f);
    }

    inline void rec(PlayLayer* p) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        d->drawDot({22.f, W().height - 22.f}, 8.f, f4(pal::RED));
        d->drawDot({22.f, W().height - 22.f}, 13.f, f4(pal::RED, 0.25f));
        auto l = label(n, "REC", 0.4f, {40.f, W().height - 22.f}, pal::WHITE);
        l->setAnchorPoint({0.f, 0.5f});
        p->addChild(n, 2700);
        n->runAction(CCBlink::create(2.4f, 4));
        later(n, 2.5f);
    }

    inline void cinema(PlayLayer* p, char const* caption) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        rect(d, 0.f, W().height - 44.f, W().width, 44.f, ccc4f(0.f, 0.f, 0.f, 1.f));
        rect(d, 0.f, 0.f, W().width, 44.f, ccc4f(0.f, 0.f, 0.f, 1.f));
        auto l = label(n, caption, 0.42f, {W().width / 2, 22.f}, pal::PAPER);
        (void)l;
        n->setPositionY(0.f);
        p->addChild(n, 2800);
        later(n, 2.f);
    }

    inline void pauseIcon(PlayLayer* p) {
        auto n = CCNode::create();
        auto d = CCDrawNode::create();
        n->addChild(d);
        rect(d, 0.f, 0.f, W().width, W().height, ccc4f(0.f, 0.f, 0.f, 0.35f));
        roundRect(d, W().width / 2 - 40.f, W().height / 2 - 48.f, 30.f, 96.f, 8.f, f4(pal::PAPER, 0.95f));
        roundRect(d, W().width / 2 + 10.f, W().height / 2 - 48.f, 30.f, 96.f, 8.f, f4(pal::PAPER, 0.95f));
        p->addChild(n, 2800);
        later(n, 1.8f);
    }

    inline void wordRain(PlayLayer* p) {
        ccColor3B cols[5] = {pal::PINK, pal::CYAN, pal::LIME, pal::AMBER, pal::VIOLET};
        for (int i = 0; i < 9; i++) {
            float x = rndf(40.f, W().width - 40.f);
            auto g = glitch(p, pick(WORDS), rndf(0.5f, 0.9f), cols[rnd(5)], {x, W().height + 30.f}, 0.f, 2000);
            g->setVisible(false);
            g->runAction(CCSequence::create(
                CCDelayTime::create(i * 0.18f), CCShow::create(),
                CCSpawn::create(CCMoveTo::create(1.6f, {x + rndf(-40.f, 40.f), -40.f}), CCRotateBy::create(1.6f, rndf(-360.f, 360.f)), nullptr),
                CCRemoveSelf::create(), nullptr));
        }
    }

    inline void flyby(PlayLayer* p) {
        ccColor3B cols[5] = {pal::PINK, pal::CYAN, pal::LIME, pal::AMBER, pal::VIOLET};
        float y = rndf(W().height * 0.2f, W().height * 0.8f);
        auto g = glitch(p, pick(WORDS), rndf(0.8f, 1.4f), cols[rnd(5)], {W().width + 80.f, y}, 0.f, 2000);
        g->runAction(CCSequence::create(
            CCSpawn::create(CCMoveTo::create(2.2f, {-120.f, y + rndf(-60.f, 60.f)}), CCRotateBy::create(2.2f, rndf(-540.f, 540.f)), nullptr),
            CCRemoveSelf::create(), nullptr));
    }

    inline std::vector<Fn> eventsB() {
        return {
            [](PlayLayer* p) { dialog(p, "Error", "Something went wrong.\nWe know. You know.", "OK", pal::RED); sfx("quitSound_01.ogg", 0.8f); },
            [](PlayLayer* p) { dialog(p, "Incoming call", "nobody is calling\nstill ringing", "Answer", pal::LIME); sfx("playSound_01.ogg", 1.4f); },
            [](PlayLayer* p) { dialog(p, "Storage full", "free up 3 gigabytes\nor 3 attempts", "Delete", pal::AMBER); },
            [](PlayLayer* p) { dialog(p, "Cookies", "we use cookies\nthe other option is also cookies", "Accept", pal::VIOLET); },
            [](PlayLayer* p) { dialog(p, "Update available", "restart to finish\nyour update, 1 of 412", "Later", pal::CYAN); },
            [](PlayLayer* p) { dialog(p, "Hello", "it is quiet\ndid something break", "No", pal::PINK); },
            [](PlayLayer* p) { dialog(p, "Terms", "scroll to accept\npage 1 of 9999", "Scroll", pal::GREY); },
            [](PlayLayer* p) { captcha(p); },
            [](PlayLayer* p) { crack(p); },
            [](PlayLayer* p) { cursor(p); },
            [](PlayLayer* p) { bounce(p); },
            [](PlayLayer* p) { ticker(p); },
            [](PlayLayer* p) { rec(p); },
            [](PlayLayer* p) { cinema(p, "[loud noise]"); sfx("explode_11.ogg", 0.4f); },
            [](PlayLayer* p) { cinema(p, "[a door closes]"); },
            [](PlayLayer* p) { cinema(p, "[someone breathes]"); },
            [](PlayLayer* p) { pauseIcon(p); },
            [](PlayLayer* p) { wordRain(p); },
            [](PlayLayer* p) { flyby(p); flyby(p); },
            [](PlayLayer* p) { flash(p); sfx("playSound_01.ogg", rndf(0.4f, 1.6f)); },
            [](PlayLayer* p) { rainbowLeft = 4.f; },
            [](PlayLayer* p) {
                if (!opt("lag")) { flash(p); return; }
                lagStart();
                auto n = card(p, 96.f, 30.f, f4(pal::INK, 0.95f), f4(pal::RED), 10.f, 2700);
                label(n, "FPS: 5", 0.38f, {48.f, 15.f}, pal::RED);
                n->setPosition({64.f, W().height - 24.f});
                n->runAction(CCSequence::create(CCDelayTime::create(2.8f), CCRemoveSelf::create(), nullptr));
            },
            [](PlayLayer* p) { if (opt("mirror") && viewMode == 0) setView(p, 1); else flash(p); },
            [](PlayLayer* p) { if (opt("mirror") && viewMode == 0) setView(p, 2); else flash(p); },
        };
    }
}
