#pragma once
#include "core.hpp"

namespace mm {
    using Fn = void (*)(PlayLayer*);
    constexpr char const* FONT = "bigFont.fnt";

    inline CCLabelBMFont* label(CCNode* n, char const* t, float scale, CCPoint pos, ccColor3B col = pal::WHITE,
                                float rot = 0.f, char const* font = FONT, int z = 5) {
        auto l = CCLabelBMFont::create(t, font);
        l->setColor(col);
        l->setScale(scale);
        l->setRotation(rot);
        l->setPosition(pos);
        n->addChild(l, z);
        return l;
    }

    inline void fit(CCLabelBMFont* l, float maxW) {
        float w = l->getContentSize().width * l->getScale();
        if (w > maxW) l->setScale(l->getScale() * maxW / w);
    }

    inline void rect(CCDrawNode* d, float x, float y, float w, float h, ccColor4F c) {
        CCPoint v[4] = {{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}};
        d->drawPolygon(v, 4, c, 0.f, c);
    }

    inline void roundRect(CCDrawNode* d, float x, float y, float w, float h, float r, ccColor4F c) {
        r = std::min(r, std::min(w, h) / 2.f);
        rect(d, x + r, y, w - 2 * r, h, c);
        rect(d, x, y + r, w, h - 2 * r, c);
        d->drawDot({x + r, y + r}, r, c);
        d->drawDot({x + w - r, y + r}, r, c);
        d->drawDot({x + r, y + h - r}, r, c);
        d->drawDot({x + w - r, y + h - r}, r, c);
    }

    inline void later(CCNode* n, float hold) {
        n->runAction(CCSequence::create(CCDelayTime::create(hold), CCRemoveSelf::create(), nullptr));
    }

    inline void shake(CCNode* n, float amp, int times) {
        n->runAction(CCRepeat::create(CCSequence::create(
            CCMoveBy::create(0.03f, {amp, 0.f}), CCMoveBy::create(0.06f, {-2.f * amp, 0.f}), CCMoveBy::create(0.03f, {amp, 0.f}),
            nullptr), times));
    }

    // centred node with a soft drop shadow, a thin border and a rounded body
    inline CCNode* card(CCNode* parent, float w, float h, ccColor4F fill, ccColor4F border, float r = 12.f, int z = 2600) {
        auto n = CCNode::create();
        n->setContentSize({w, h});
        n->setAnchorPoint({0.5f, 0.5f});
        n->ignoreAnchorPointForPosition(false);
        auto d = CCDrawNode::create();
        d->setTag(1);
        n->addChild(d, 0);
        roundRect(d, 3.f, -5.f, w, h, r, ccc4f(0.f, 0.f, 0.f, 0.35f));
        roundRect(d, -1.5f, -1.5f, w + 3.f, h + 3.f, r + 1.5f, border);
        roundRect(d, 0.f, 0.f, w, h, r, fill);
        parent->addChild(n, z);
        return n;
    }

    inline CCDrawNode* drawOf(CCNode* n) { return static_cast<CCDrawNode*>(n->getChildByTag(1)); }

    inline void popCard(CCNode* n, float hold) {
        n->setScale(0.7f);
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.22f, 1.f)), CCDelayTime::create(hold),
            CCEaseBackIn::create(CCScaleTo::create(0.18f, 0.01f)), CCRemoveSelf::create(), nullptr));
    }

    // brand text: pink and cyan split behind the main colour, soft shadow below
    inline CCNode* glitch(CCNode* parent, char const* t, float scale, ccColor3B col, CCPoint pos, float rot = 0.f, int z = 5) {
        auto n = CCNode::create();
        n->setPosition(pos);
        n->setRotation(rot);
        parent->addChild(n, z);
        float o = std::max(1.5f, 3.f * scale);
        auto sh = label(n, t, scale, {0.f, -o * 1.6f}, ccc3(0, 0, 0), 0.f, FONT, 0);
        sh->setOpacity(110);
        label(n, t, scale, {-o, o * 0.4f}, pal::PINK, 0.f, FONT, 1);
        label(n, t, scale, {o, -o * 0.4f}, pal::CYAN, 0.f, FONT, 2);
        label(n, t, scale, {0.f, 0.f}, col, 0.f, FONT, 3);
        return n;
    }

    inline void burst(CCNode* parent, CCPoint at, int count = 10) {
        ccColor3B cols[5] = {pal::PINK, pal::CYAN, pal::LIME, pal::AMBER, pal::VIOLET};
        for (int i = 0; i < count; i++) {
            auto q = CCLayerColor::create(b4(cols[i % 5]), 8.f, 8.f);
            q->setPosition(at);
            q->setRotation(rndf(0.f, 90.f));
            parent->addChild(q, 2100);
            float a = rndf(0.f, 6.283f), r = rndf(50.f, 110.f);
            q->runAction(CCSequence::create(
                CCSpawn::create(CCEaseOut::create(CCMoveBy::create(0.6f, {std::cos(a) * r, std::sin(a) * r}), 2.f), CCFadeOut::create(0.6f), nullptr),
                CCRemoveSelf::create(), nullptr));
        }
    }

    // full-screen stage: vertical gradient, thin inner frame, pop in / pop out
    struct Stage { CCNode* n; CCDrawNode* d; };
    inline Stage stage(CCNode* parent, ccColor3B top, ccColor3B bottom, ccColor3B frameCol = pal::WHITE, float hold = 1.6f) {
        auto n = CCNode::create();
        n->setContentSize(W());
        n->setAnchorPoint({0.5f, 0.5f});
        n->ignoreAnchorPointForPosition(false);
        n->setPosition({W().width / 2, W().height / 2});
        n->setScale(0.6f);
        parent->addChild(n, 3000);
        n->addChild(CCLayerGradient::create(b4(top), b4(bottom)), 0);
        auto d = CCDrawNode::create();
        n->addChild(d, 1);
        auto fc = f4(frameCol, 0.35f);
        float w = W().width, h = W().height;
        rect(d, 12.f, 12.f, w - 24.f, 2.f, fc);
        rect(d, 12.f, h - 14.f, w - 24.f, 2.f, fc);
        rect(d, 12.f, 12.f, 2.f, h - 24.f, fc);
        rect(d, w - 14.f, 12.f, 2.f, h - 24.f, fc);
        n->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.22f, 1.f)), CCDelayTime::create(hold),
            CCEaseBackIn::create(CCScaleTo::create(0.2f, 0.01f)), CCRemoveSelf::create(), nullptr));
        return {n, d};
    }

    inline void scanlines(CCDrawNode* d, float alpha = 0.14f) {
        for (float y = 0.f; y < W().height; y += 4.f) rect(d, 0.f, y, W().width, 1.f, ccc4f(0.f, 0.f, 0.f, alpha));
    }

    inline void confetti(CCDrawNode* d, int count, ccColor3B const* cols, int ncols) {
        for (int i = 0; i < count; i++) {
            auto c = cols[rnd(ncols)];
            rect(d, rndf(20.f, W().width - 30.f), rndf(20.f, W().height - 30.f), rndf(5.f, 11.f), rndf(5.f, 11.f), f4(c, 0.9f));
        }
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
