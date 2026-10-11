#pragma once
#include "ui.hpp"

namespace mm {
    inline void tint(CCNode* parent, ccColor4B c, float hold) {
        auto layer = CCLayerColor::create(c, W().width, W().height);
        parent->addChild(layer, 1400);
        layer->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.4f), CCRemoveSelf::create(), nullptr));
    }

    inline void flash(CCNode* parent) {
        ccColor3B cols[5] = {pal::PINK, pal::CYAN, pal::LIME, pal::AMBER, pal::VIOLET};
        tint(parent, b4(cols[rnd(5)], 90), 0.1f);
    }

    inline void splash(CCNode* parent, char const* text, ccColor3B color, float scale, float yFrac = 0.5f, bool shk = false) {
        CCPoint pos = {W().width / 2, W().height * yFrac};
        auto n = glitch(parent, text, scale, color, pos, (float)(rnd(9) - 4), 2000);
        n->setScale(0.1f);
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.22f, 1.f)), CCDelayTime::create(1.1f),
            CCEaseBackIn::create(CCScaleTo::create(0.2f, 0.01f)), CCRemoveSelf::create(), nullptr));
        burst(parent, pos, 8);
        if (shk) shake(n, 4.f, 8);
    }

    inline void pop(CCNode* parent, char const* text, ccColor3B color, float scale, CCPoint pos, float hold) {
        auto n = glitch(parent, text, scale, color, pos, (float)(rnd(13) - 6), 2000);
        n->setScale(0.1f);
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.25f, 1.f)), CCDelayTime::create(hold),
            CCEaseBackIn::create(CCScaleTo::create(0.2f, 0.01f)), CCRemoveSelf::create(), nullptr));
    }

    // dark ribbon that slides in from the left: accent edge, optional tag pill, caption
    inline void strip(CCNode* parent, char const* text, ccColor3B accent, float yFrac, float hold, char const* tag = nullptr) {
        float w = W().width * 0.86f, h = 46.f;
        auto n = card(parent, w, h, f4(pal::INK, 0.95f), f4(accent), 12.f, 2400);
        auto d = drawOf(n);
        float x0 = 14.f;
        if (tag) {
            auto t = label(n, tag, 0.3f, {0.f, h / 2}, pal::INK);
            float tw = t->getContentSize().width * 0.3f + 18.f;
            roundRect(d, 8.f, 8.f, tw, h - 16.f, 8.f, f4(accent));
            t->setPosition({8.f + tw / 2, h / 2});
            x0 = 8.f + tw + 14.f;
        }
        auto l = label(n, text, 0.5f, {x0, h / 2}, pal::WHITE);
        l->setAnchorPoint({0.f, 0.5f});
        fit(l, w - x0 - 14.f);
        float tx = W().width / 2;
        n->setPosition({-w, W().height * yFrac});
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCMoveTo::create(0.3f, {tx, W().height * yFrac})), CCDelayTime::create(hold),
            CCEaseIn::create(CCMoveTo::create(0.25f, {W().width + w, W().height * yFrac}), 2.f), CCRemoveSelf::create(), nullptr));
    }

    // notification card from the top corner with a draining timer line
    inline void toast(CCNode* parent, char const* title, char const* body, ccColor3B accent = pal::CYAN, bool left = true) {
        float w = 232.f, h = 56.f;
        auto n = card(parent, w, h, f4(pal::INK, 0.96f), f4(pal::GREY, 0.35f), 14.f, 2600);
        auto d = drawOf(n);
        d->drawDot({26.f, h / 2}, 12.f, f4(accent));
        d->drawDot({26.f, h / 2}, 5.f, f4(pal::INK));
        auto t = label(n, title, 0.28f, {50.f, h - 16.f}, pal::GREY);
        t->setAnchorPoint({0.f, 0.5f});
        fit(t, w - 64.f);
        auto b = label(n, body, 0.34f, {50.f, 20.f}, pal::WHITE);
        b->setAnchorPoint({0.f, 0.5f});
        fit(b, w - 64.f);
        auto bar = CCLayerColor::create(b4(accent), w - 28.f, 3.f);
        bar->setAnchorPoint({0.f, 0.f});
        bar->ignoreAnchorPointForPosition(false);
        bar->setPosition({14.f, 5.f});
        n->addChild(bar, 3);
        bar->runAction(CCScaleTo::create(1.9f, 0.f, 1.f));
        float x = left ? 12.f + w / 2 : W().width - 12.f - w / 2;
        float y = W().height - 10.f - h / 2;
        n->setPosition({x, W().height + h});
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCMoveTo::create(0.3f, {x, y})), CCDelayTime::create(1.7f),
            CCEaseIn::create(CCMoveTo::create(0.25f, {x, W().height + h}), 2.f), CCRemoveSelf::create(), nullptr));
        sfx("playSound_01.ogg", 1.6f, 0.6f);
    }

    // centred message card: accent title, white body, pill button
    inline CCNode* dialog(CCNode* parent, char const* title, char const* body, char const* button, ccColor3B accent, float hold = 2.f) {
        float w = 290.f, h = 140.f;
        auto n = card(parent, w, h, f4(pal::INK, 0.97f), f4(accent), 16.f, 2600);
        auto d = drawOf(n);
        roundRect(d, 0.f, h - 30.f, w, 30.f, 16.f, f4(accent, 0.22f));
        auto t = label(n, title, 0.3f, {16.f, h - 15.f}, accent);
        t->setAnchorPoint({0.f, 0.5f});
        auto b = label(n, body, 0.32f, {w / 2, h * 0.52f}, pal::WHITE);
        fit(b, w - 30.f);
        auto bt = label(n, button, 0.3f, {w / 2, 24.f}, pal::INK, 0.f, FONT, 6);
        float bw = bt->getContentSize().width * 0.3f + 34.f;
        roundRect(d, w / 2 - bw / 2, 10.f, bw, 28.f, 14.f, f4(accent));
        n->setPosition({W().width / 2, W().height / 2});
        popCard(n, hold);
        return n;
    }
}
