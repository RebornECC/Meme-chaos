// Meme Chaos - roasts, meme sounds and random chaos events. Visual only: never changes gameplay or physics.
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

using namespace geode::prelude;

namespace mm {
    inline std::mt19937 rng{std::random_device{}()};
    inline int rnd(int n) { return std::uniform_int_distribution<int>(0, n - 1)(rng); }
    inline float rndf(float a, float b) { return std::uniform_real_distribution<float>(a, b)(rng); }

    inline bool roast() { return Mod::get()->getSettingValue<bool>("roast"); }
    inline bool sounds() { return Mod::get()->getSettingValue<bool>("sounds"); }
    inline bool chaos() { return Mod::get()->getSettingValue<bool>("chaos"); }
    inline bool blackout() { return Mod::get()->getSettingValue<bool>("blackout"); }
    inline bool mirror() { return Mod::get()->getSettingValue<bool>("mirror"); }
    inline float interval() { return (float)Mod::get()->getSettingValue<int64_t>("chaos-interval"); }

    inline char const* const ROASTS[] = {
        "skill issue", "bro really died there", "L + ratio", "my grandma plays better",
        "not even close", "lag, right?", "that spike was free", "sir, this is a Wendy's",
        "bruh", "again? really?", "it's giving 0%", "you good?", "NPC behavior", "cooked."
    };
    inline char const* const EARLY[] = {
        "bro... it's the first jump", "10 percent speedrun any%", "warm up arc", "did you even start?"
    };
    inline char const* const CLOSE[] = {
        "SO CLOSE", "pain.", "that was your win", "the spike said no", "ouch. just ouch."
    };
    inline char const* const STREAK[] = {
        "touch grass?", "have some water", "maybe try practice mode", "this is fine. everything is fine."
    };
    inline char const* const WINS[] = {
        "GG EZ", "gg. who are you?", "POGGERS", "legend", "built different"
    };
    inline char const* const WORDS[] = {
        "SUS", "BRUH", "OOF", "NOICE", "WHAT", "VIBE", "L", "WOW", "SHEESH", "FR FR"
    };

    template <size_t N>
    char const* pick(char const* const (&a)[N]) { return a[rnd((int)N)]; }

    inline int deaths = 0;
    inline float chaosTimer = 0.f;
    inline float rainbowLeft = 0.f;
    inline float hue = 0.f;
    inline float viewLeft = 0.f;
    inline int viewMode = 0; // 0 normal, 1 mirrored, 2 upside down
    inline CCPoint viewOrigin = {0.f, 0.f};

    inline void sfx(char const* name, float speed, float volume = 1.f) {
        if (sounds()) FMODAudioEngine::sharedEngine()->playEffect(name, speed, 0.f, volume);
    }

    inline ccColor3B fromHue(float h) {
        float r = 0.5f + 0.5f * std::sin(h);
        float g = 0.5f + 0.5f * std::sin(h + 2.094f);
        float b = 0.5f + 0.5f * std::sin(h + 4.188f);
        return {(GLubyte)(r * 255), (GLubyte)(g * 255), (GLubyte)(b * 255)};
    }

    inline void pop(CCNode* parent, char const* text, ccColor3B color, float scale, CCPoint pos, float hold) {
        auto l = CCLabelBMFont::create(text, "bigFont.fnt");
        l->setColor(color);
        l->setScale(0.1f);
        l->setPosition(pos);
        l->setRotation((float)(rnd(17) - 8));
        parent->addChild(l, 2000);
        l->runAction(CCSequence::create(
            CCEaseBackOut::create(CCScaleTo::create(0.25f, scale)),
            CCDelayTime::create(hold),
            CCFadeOut::create(0.3f),
            CCRemoveSelf::create(),
            nullptr));
    }

    inline void flash(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        auto c = ccc4(60 + rnd(196), 60 + rnd(196), 60 + rnd(196), 110);
        auto layer = CCLayerColor::create(c, win.width, win.height);
        parent->addChild(layer, 1500);
        layer->runAction(CCSequence::create(CCFadeOut::create(0.5f), CCRemoveSelf::create(), nullptr));
    }

    inline void flyby(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        auto l = CCLabelBMFont::create(pick(WORDS), "bigFont.fnt");
        l->setColor(fromHue(rndf(0.f, 6.28f)));
        l->setScale(rndf(0.8f, 1.4f));
        float y = rndf(win.height * 0.2f, win.height * 0.8f);
        l->setPosition({win.width + 80.f, y});
        parent->addChild(l, 2000);
        l->runAction(CCSequence::create(
            CCSpawn::create(
                CCMoveTo::create(2.2f, {-120.f, y + rndf(-60.f, 60.f)}),
                CCRotateBy::create(2.2f, rndf(-540.f, 540.f)),
                nullptr),
            CCRemoveSelf::create(),
            nullptr));
    }

    // short blackout (1.5 s) and long black screen with a caption (2 s)
    inline void darkness(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        auto layer = CCLayerColor::create(ccc4(0, 0, 0, 235), win.width, win.height);
        parent->addChild(layer, 2500);
        layer->runAction(CCSequence::create(CCDelayTime::create(1.1f), CCFadeOut::create(0.4f), CCRemoveSelf::create(), nullptr));
        pop(parent, "lights out", ccc3(255, 255, 255), 0.6f, {win.width / 2, win.height / 2}, 0.8f);
    }

    inline void blackScreen(CCNode* parent) {
        static char const* const CAPTIONS[] = {
            "loading...", "you have been trolled", "no signal", "skill issue", "please wait", "buffering 99%"
        };
        auto win = CCDirector::get()->getWinSize();
        auto layer = CCLayerColor::create(ccc4(0, 0, 0, 255), win.width, win.height);
        parent->addChild(layer, 3000);
        layer->runAction(CCSequence::create(CCDelayTime::create(1.7f), CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
        auto t = CCLabelBMFont::create(CAPTIONS[rnd(6)], "bigFont.fnt");
        t->setScale(0.7f);
        t->setPosition({win.width / 2, win.height / 2});
        parent->addChild(t, 3001);
        t->runAction(CCSequence::create(CCDelayTime::create(1.7f), CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
        sfx("explode_11.ogg", 0.4f);
    }

    // coloured strip across the screen with a caption
    inline void banner(CCNode* parent, char const* text, ccColor4B bg, ccColor3B fg, float yFrac, float hold, float scale = 0.8f) {
        auto win = CCDirector::get()->getWinSize();
        auto strip = CCLayerColor::create(bg, win.width, 56.f);
        strip->setPosition({0.f, win.height * yFrac - 28.f});
        parent->addChild(strip, 2400);
        auto t = CCLabelBMFont::create(text, "bigFont.fnt");
        t->setColor(fg);
        t->setScale(scale);
        t->setPosition({win.width / 2, 28.f});
        strip->addChild(t);
        strip->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
        t->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.3f), nullptr));
    }

    inline void tint(CCNode* parent, ccColor4B c, float hold) {
        auto win = CCDirector::get()->getWinSize();
        auto layer = CCLayerColor::create(c, win.width, win.height);
        parent->addChild(layer, 1400);
        layer->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.4f), CCRemoveSelf::create(), nullptr));
    }

    inline void corner(CCNode* parent, char const* text, CCPoint pos, float hold, ccColor3B color = ccc3(255, 255, 255)) {
        auto l = CCLabelBMFont::create(text, "bigFont.fnt");
        l->setColor(color);
        l->setScale(0.45f);
        l->setPosition(pos);
        parent->addChild(l, 2700);
        l->runAction(CCSequence::create(CCDelayTime::create(hold), CCFadeOut::create(0.3f), CCRemoveSelf::create(), nullptr));
    }

    inline void memeText(CCNode* parent, int which) {
        auto win = CCDirector::get()->getWinSize();
        switch (which) {
            case 0: // dark-souls style
                tint(parent, ccc4(0, 0, 0, 90), 1.6f);
                banner(parent, "YOU DIED", ccc4(0, 0, 0, 200), ccc3(190, 20, 20), 0.5f, 1.8f, 1.3f);
                sfx("explode_11.ogg", 0.3f);
                break;
            case 1: // to be continued, sepia
                tint(parent, ccc4(150, 95, 30, 110), 2.f);
                corner(parent, "To be continued >", {win.width * 0.25f, win.height * 0.1f}, 2.f, ccc3(255, 190, 70));
                sfx("magicExplosion.ogg", 0.6f, 0.8f);
                break;
            case 2:
                banner(parent, "MISSION FAILED", ccc4(0, 0, 0, 180), ccc3(240, 240, 240), 0.5f, 1.6f, 1.1f);
                corner(parent, "we'll get 'em next time", {win.width / 2, win.height * 0.4f}, 1.6f);
                break;
            case 3:
                banner(parent, "Updating... 99%", ccc4(0, 90, 190, 235), ccc3(255, 255, 255), 0.5f, 1.8f, 0.9f);
                corner(parent, "do not turn off your phone", {win.width / 2, win.height * 0.38f}, 1.8f);
                break;
            case 4: // fake ad
                corner(parent, "Ad  0:05  [skip]", {win.width - 100.f, win.height - 20.f}, 2.2f, ccc3(255, 220, 80));
                banner(parent, "BUY NOW: 0 sleep", ccc4(200, 30, 120, 220), ccc3(255, 255, 255), 0.18f, 2.2f, 0.6f);
                break;
            case 5:
                banner(parent, "Battery 1%", ccc4(200, 30, 30, 230), ccc3(255, 255, 255), 0.5f, 1.4f, 1.f);
                sfx("playSound_01.ogg", 0.5f);
                break;
            case 6:
                pop(parent, "STONKS", ccc3(110, 255, 150), 1.4f, {win.width / 2, win.height * 0.55f}, 1.f);
                pop(parent, "NOT STONKS", ccc3(255, 90, 90), 1.f, {win.width / 2, win.height * 0.3f}, 1.f);
                break;
            case 7:
                banner(parent, "never gonna give you up", ccc4(20, 20, 20, 220), ccc3(255, 255, 255), 0.5f, 1.8f, 0.6f);
                sfx("crystal01.ogg", 0.8f);
                break;
            case 8:
                banner(parent, "Like and subscribe", ccc4(220, 20, 20, 230), ccc3(255, 255, 255), 0.82f, 1.8f, 0.7f);
                break;
            default:
                corner(parent, "FPS: 3", {60.f, win.height - 20.f}, 1.8f, ccc3(255, 90, 90));
                banner(parent, "LAG", ccc4(0, 0, 0, 160), ccc3(255, 255, 255), 0.5f, 1.4f, 1.f);
                break;
        }
    }

    inline void fakeError(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        auto box = CCLayerColor::create(ccc4(30, 60, 140, 245), 280.f, 90.f);
        box->setPosition({win.width / 2 - 140.f, win.height / 2 - 45.f});
        auto t = CCLabelBMFont::create("Geometry Dash has\nstopped working", "bigFont.fnt");
        t->setScale(0.4f);
        t->setPosition({140.f, 52.f});
        box->addChild(t);
        auto ok = CCLabelBMFont::create("[ just kidding ]", "chatFont.fnt");
        ok->setPosition({140.f, 16.f});
        box->addChild(ok);
        parent->addChild(box, 2600);
        box->runAction(CCSequence::create(CCDelayTime::create(1.6f), CCRemoveSelf::create(), nullptr));
        sfx("quitSound_01.ogg", 0.7f);
    }

    inline void fakeAchievement(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        auto box = CCLayerColor::create(ccc4(20, 20, 20, 235), 300.f, 36.f);
        box->setPosition({win.width / 2 - 150.f, win.height + 4.f});
        auto t = CCLabelBMFont::create("Achievement unlocked: Skill issue", "bigFont.fnt");
        t->setScale(0.36f);
        t->setPosition({150.f, 18.f});
        box->addChild(t);
        parent->addChild(box, 2600);
        box->runAction(CCSequence::create(
            CCMoveBy::create(0.35f, {0.f, -44.f}),
            CCDelayTime::create(1.6f),
            CCMoveBy::create(0.35f, {0.f, 44.f}),
            CCRemoveSelf::create(),
            nullptr));
        sfx("achievement_01.ogg", 1.f, 0.8f);
    }

    inline void wordRain(CCNode* parent) {
        auto win = CCDirector::get()->getWinSize();
        for (int i = 0; i < 9; i++) {
            auto l = CCLabelBMFont::create(pick(WORDS), "bigFont.fnt");
            l->setColor(fromHue(rndf(0.f, 6.28f)));
            l->setScale(rndf(0.5f, 0.9f));
            float x = rndf(40.f, win.width - 40.f);
            l->setPosition({x, win.height + 30.f});
            l->setVisible(false);
            parent->addChild(l, 2000);
            l->runAction(CCSequence::create(
                CCDelayTime::create(i * 0.18f),
                CCShow::create(),
                CCSpawn::create(CCMoveTo::create(1.6f, {x + rndf(-40.f, 40.f), -40.f}), CCRotateBy::create(1.6f, rndf(-360.f, 360.f)), nullptr),
                CCRemoveSelf::create(),
                nullptr));
        }
    }

    inline void setView(PlayLayer* pl, int mode) {
        auto win = CCDirector::get()->getWinSize();
        if (mode != 0 && viewMode == 0) viewOrigin = pl->getPosition();
        viewMode = mode;
        pl->setScaleX(mode == 1 ? -1.f : 1.f);
        pl->setScaleY(mode == 2 ? -1.f : 1.f);
        pl->setPosition({viewOrigin.x + (mode == 1 ? win.width : 0.f), viewOrigin.y + (mode == 2 ? win.height : 0.f)});
        viewLeft = mode == 0 ? 0.f : 3.f;
    }

    inline void chaosEvent(PlayLayer* pl) {
        auto win = CCDirector::get()->getWinSize();
        switch (rnd(15)) {
            case 0: flash(pl); sfx("playSound_01.ogg", rndf(0.4f, 1.6f)); break;
            case 1: flyby(pl); flyby(pl); break;
            case 2: rainbowLeft = 4.f; pop(pl, "RAINBOW TIME", fromHue(rndf(0.f, 6.28f)), 0.7f, {win.width / 2, win.height * 0.8f}, 1.2f); break;
            case 3: pop(pl, pick(WORDS), fromHue(rndf(0.f, 6.28f)), 1.6f, {win.width / 2, win.height / 2}, 0.5f); sfx("explode_11.ogg", rndf(0.3f, 0.6f), 0.7f); break;
            case 4: flash(pl); flyby(pl); sfx("crystal01.ogg", rndf(0.5f, 2.f)); break;
            case 5: if (blackout()) blackScreen(pl); else flash(pl); break;
            case 6: fakeError(pl); break;
            case 7: if (blackout()) darkness(pl); else flash(pl); break;
            case 8: if (mirror() && viewMode == 0) { setView(pl, 1); pop(pl, "MIRROR", ccc3(120, 200, 255), 0.6f, {win.width / 2, win.height * 0.85f}, 1.f); } else flyby(pl); break;
            case 9: if (mirror() && viewMode == 0) { setView(pl, 2); pop(pl, "UPSIDE DOWN", ccc3(255, 200, 120), 0.6f, {win.width / 2, win.height * 0.15f}, 1.f); } else flash(pl); break;
            case 10: wordRain(pl); break;
            case 11: fakeAchievement(pl); break;
            default: memeText(pl, rnd(10)); break;
        }
    }

    inline void restoreColors(PlayLayer* pl) {
        auto gm = GameManager::sharedState();
        if (pl->m_player1) {
            pl->m_player1->setColor(gm->colorForIdx(gm->getPlayerColor()));
            pl->m_player1->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
        }
    }
}

class $modify(MmPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        mm::deaths = 0;
        mm::chaosTimer = 0.f;
        mm::rainbowLeft = 0.f;
        mm::viewMode = 0;
        mm::viewOrigin = this->getPosition();
        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);
        if (!m_player1 || m_player1->m_isDead) return;

        if (mm::rainbowLeft > 0.f) {
            mm::rainbowLeft -= dt;
            mm::hue += dt * 8.f;
            m_player1->setColor(mm::fromHue(mm::hue));
            m_player1->setSecondColor(mm::fromHue(mm::hue + 3.f));
            if (mm::rainbowLeft <= 0.f) mm::restoreColors(this);
        }

        if (mm::viewMode != 0) {
            mm::viewLeft -= dt;
            if (mm::viewLeft <= 0.f) mm::setView(this, 0);
        }

        if (mm::chaos()) {
            mm::chaosTimer += dt;
            if (mm::chaosTimer >= mm::interval() * mm::rndf(0.5f, 1.5f)) {
                mm::chaosTimer = 0.f;
                mm::chaosEvent(this);
            }
        }
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        bool wasDead = player->m_isDead;
        PlayLayer::destroyPlayer(player, object);
        if (wasDead || !player->m_isDead || player != m_player1) return;

        mm::deaths++;
        mm::rainbowLeft = 0.f;
        if (mm::viewMode != 0) mm::setView(this, 0);
        if (!mm::roast()) return;

        auto win = CCDirector::get()->getWinSize();
        float pct = this->getCurrentPercent();
        char const* text = mm::pick(mm::ROASTS);
        if (mm::deaths % 10 == 0) text = mm::pick(mm::STREAK);
        else if (pct < 10.f) text = mm::pick(mm::EARLY);
        else if (pct >= 85.f) text = mm::pick(mm::CLOSE);

        mm::pop(this, text, ccc3(255, 90, 90), 0.55f, {win.width / 2, win.height * 0.72f}, 0.9f);
        mm::sfx("explode_11.ogg", mm::rndf(0.35f, 0.8f));
        if (mm::rnd(3) == 0) mm::sfx("quitSound_01.ogg", 0.5f, 0.8f);
    }

    void levelComplete() {
        if (mm::viewMode != 0) mm::setView(this, 0);
        PlayLayer::levelComplete();
        if (mm::roast()) {
            auto win = CCDirector::get()->getWinSize();
            mm::pop(this, mm::pick(mm::WINS), ccc3(110, 255, 150), 1.1f, {win.width / 2, win.height * 0.62f}, 1.4f);
            mm::flash(this);
        }
        mm::sfx("achievement_01.ogg", 1.f);
        mm::restoreColors(this);
    }

    void onQuit() {
        mm::rainbowLeft = 0.f;
        if (mm::viewMode != 0) mm::setView(this, 0);
        PlayLayer::onQuit();
    }
};
