#pragma once
#include "core.hpp"

namespace mm {
    using Fn = void (*)(PlayLayer*);

    inline CCLabelBMFont* label(CCNode* n, char const* t, float scale, CCPoint pos, ccColor3B col = ccc3(255, 255, 255),
                                float rot = 0.f, char const* font = "bigFont.fnt", int z = 5) {
        auto l = CCLabelBMFont::create(t, font);
        l->setColor(col);
        l->setScale(scale);
        l->setRotation(rot);
        l->setPosition(pos);
        n->addChild(l, z);
        return l;
    }

    inline CCLabelBMFont* labelF(CCNode* n, char const* t, float xf, float yf, float scale, ccColor3B col = ccc3(255, 255, 255), float rot = 0.f) {
        return label(n, t, scale, {W().width * xf, W().height * yf}, col, rot);
    }

    inline void rect(CCDrawNode* d, float x, float y, float w, float h, ccColor4F c) {
        CCPoint v[4] = {{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}};
        d->drawPolygon(v, 4, c, 0.f, c);
    }

    inline void slant(CCDrawNode* d, float x0, float w, float h, float shift, ccColor4F c) {
        CCPoint v[4] = {{x0, 0.f}, {x0 + w, 0.f}, {x0 + w + shift, h}, {x0 + shift, h}};
        d->drawPolygon(v, 4, c, 0.f, c);
    }

    inline void later(CCNode* n, float hold) {
        n->runAction(CCSequence::create(CCDelayTime::create(hold), CCRemoveSelf::create(), nullptr));
    }

    inline void shake(CCNode* n, float amp, int times) {
        n->runAction(CCRepeat::create(CCSequence::create(
            CCMoveBy::create(0.03f, {amp, 0.f}), CCMoveBy::create(0.06f, {-2.f * amp, 0.f}), CCMoveBy::create(0.03f, {amp, 0.f}),
            nullptr), times));
    }

    inline CCNode* screen(CCNode* parent, float hold = 1.6f) {
        auto n = CCNode::create();
        n->setContentSize(W());
        n->setAnchorPoint({0.5f, 0.5f});
        n->ignoreAnchorPointForPosition(false);
        n->setPosition({W().width / 2, W().height / 2});
        n->setScale(0.6f);
        parent->addChild(n, 3000);
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.22f, 1.f)), CCDelayTime::create(hold),
            CCEaseBackIn::create(CCScaleTo::create(0.2f, 0.01f)), CCRemoveSelf::create(), nullptr));
        return n;
    }

    inline CCDrawNode* canvas(CCNode* n, ccColor4F bg) {
        auto d = CCDrawNode::create();
        n->addChild(d, 0);
        rect(d, 0.f, 0.f, W().width, W().height, bg);
        return d;
    }

    inline void splash(CCNode* parent, char const* text, ccColor3B color, float scale, float yFrac = 0.5f, bool shk = false) {
        auto l = CCLabelBMFont::create(text, "bigFont.fnt");
        l->setColor(color);
        l->setScale(0.1f);
        l->setPosition({W().width / 2, W().height * yFrac});
        l->setRotation((float)(rnd(13) - 6));
        parent->addChild(l, 2000);
        l->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.2f, scale)), CCDelayTime::create(1.1f),
            CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
        if (shk) shake(l, 4.f, 8);
    }

    inline void pop(CCNode* parent, char const* text, ccColor3B color, float scale, CCPoint pos, float hold) {
        auto l = CCLabelBMFont::create(text, "bigFont.fnt");
        l->setColor(color);
        l->setScale(0.1f);
        l->setPosition(pos);
        l->setRotation((float)(rnd(17) - 8));
        parent->addChild(l, 2000);
        l->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.25f, scale)), CCDelayTime::create(hold),
            CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
    }

    inline void tint(CCNode* parent, ccColor4B c, float hold) {
        auto layer = CCLayerColor::create(c, W().width, W().height);
        parent->addChild(layer, 1400);
        layer->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.4f), CCRemoveSelf::create(), nullptr));
    }

    inline void flash(CCNode* parent) {
        tint(parent, ccc4(60 + rnd(196), 60 + rnd(196), 60 + rnd(196), 110), 0.1f);
    }

    inline void strip(CCNode* parent, char const* text, ccColor4B bg, ccColor3B fg, float yFrac, float hold, float scale = 0.7f) {
        auto s = CCLayerColor::create(bg, W().width, 56.f);
        s->setPosition({0.f, W().height * yFrac - 28.f});
        parent->addChild(s, 2400);
        label(s, text, scale, {W().width / 2, 28.f}, fg);
        later(s, hold);
    }

    inline void toast(CCNode* parent, char const* title, char const* body, bool left = true) {
        float w = 220.f, h = 52.f;
        auto card = CCLayerColor::create(ccc4(28, 28, 34, 240), w, h);
        float x = left ? 8.f : W().width - w - 8.f;
        card->setPosition({x, W().height + 4.f});
        label(card, title, 0.3f, {w / 2, h - 14.f}, ccc3(150, 160, 190));
        label(card, body, 0.34f, {w / 2, 16.f}, ccc3(255, 255, 255));
        parent->addChild(card, 2600);
        card->runAction(CCSequence::create(
            CCMoveBy::create(0.25f, {0.f, -(h + 12.f)}), CCDelayTime::create(1.7f),
            CCMoveBy::create(0.25f, {0.f, h + 12.f}), CCRemoveSelf::create(), nullptr));
        sfx("playSound_01.ogg", 1.6f, 0.6f);
    }

    inline CCNode* dialog(CCNode* parent, char const* title, char const* body, char const* button, ccColor4B bar = ccc4(20, 60, 150, 255), float hold = 2.f) {
        float w = 270.f, h = 120.f;
        auto box = CCLayerColor::create(ccc4(214, 214, 218, 255), w, h);
        box->setPosition({W().width / 2 - w / 2, W().height / 2 - h / 2});
        auto head = CCLayerColor::create(bar, w, 22.f);
        head->setPosition({0.f, h - 22.f});
        box->addChild(head, 1);
        label(head, title, 0.28f, {w / 2, 11.f});
        label(box, body, 0.3f, {w / 2, h * 0.55f}, ccc3(20, 20, 24));
        auto b = CCLayerColor::create(ccc4(170, 170, 178, 255), 84.f, 22.f);
        b->setPosition({w / 2 - 42.f, 10.f});
        box->addChild(b, 1);
        label(b, button, 0.28f, {42.f, 11.f}, ccc3(10, 10, 10));
        box->setScale(0.1f);
        box->setAnchorPoint({0.5f, 0.5f});
        box->ignoreAnchorPointForPosition(false);
        box->setPosition({W().width / 2, W().height / 2});
        parent->addChild(box, 2600);
        box->runAction(CCSequence::create(CCEaseBackOut::create(CCScaleTo::create(0.15f, 1.f)), CCDelayTime::create(hold), CCRemoveSelf::create(), nullptr));
        return box;
    }

    inline void setView(PlayLayer* pl, int mode) {
        if (mode != 0 && viewMode == 0) viewOrigin = pl->getPosition();
        viewMode = mode;
        pl->setScaleX(mode == 1 ? -1.f : 1.f);
        pl->setScaleY(mode == 2 ? -1.f : 1.f);
        pl->setPosition({viewOrigin.x + (mode == 1 ? W().width : 0.f), viewOrigin.y + (mode == 2 ? W().height : 0.f)});
        viewLeft = mode == 0 ? 0.f : 3.f;
    }

    inline void restoreColors(PlayLayer* pl) {
        auto gm = GameManager::sharedState();
        if (pl->m_player1) {
            pl->m_player1->setColor(gm->colorForIdx(gm->getPlayerColor()));
            pl->m_player1->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
        }
    }
}
