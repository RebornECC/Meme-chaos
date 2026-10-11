#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "events_a.hpp"
#include "events_b.hpp"
#include "screens.hpp"

namespace mm {
    inline void chaosEvent(PlayLayer* pl) {
        static std::vector<Fn> all;
        if (all.empty()) {
            for (auto const& v : {eventsA(), eventsB(), eventsC()}) all.insert(all.end(), v.begin(), v.end());
        }
        int idx = 0;
        for (int tries = 0; tries < 12; tries++) {
            idx = rnd((int)all.size());
            if (std::find(std::begin(recent), std::end(recent), idx) == std::end(recent)) break;
        }
        for (int i = 7; i > 0; i--) recent[i] = recent[i - 1];
        recent[0] = idx;
        all[idx](pl);
    }
}

class $modify(MmPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        mm::lagEnd();
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

        if (mm::lagLeft > 0.f) {
            mm::lagLeft -= dt;
            if (mm::lagLeft <= 0.f) {
                mm::lagLeft = 0.01f;
                mm::lagEnd();
            }
        }

        if (mm::viewMode != 0) {
            mm::viewLeft -= dt;
            if (mm::viewLeft <= 0.f) mm::setView(this, 0);
        }

        if (mm::opt("chaos")) {
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

        mm::lagEnd();
        mm::deaths++;
        mm::rainbowLeft = 0.f;
        if (mm::viewMode != 0) mm::setView(this, 0);
        if (!mm::opt("roast")) return;

        float pct = this->getCurrentPercent();
        char const* text = mm::pick(mm::ROASTS);
        if (mm::deaths % 10 == 0) text = mm::pick(mm::STREAK);
        else if (pct < 10.f) text = mm::pick(mm::EARLY);
        else if (pct >= 85.f) text = mm::pick(mm::CLOSE);

        mm::pop(this, text, ccc3(255, 90, 90), 0.55f, {mm::W().width / 2, mm::W().height * 0.72f}, 0.9f);
        mm::sfx("explode_11.ogg", mm::rndf(0.35f, 0.8f));
        if (mm::rnd(3) == 0) mm::sfx("quitSound_01.ogg", 0.5f, 0.8f);
    }

    void levelComplete() {
        mm::lagEnd();
        if (mm::viewMode != 0) mm::setView(this, 0);
        PlayLayer::levelComplete();
        if (mm::opt("roast")) mm::pop(this, mm::pick(mm::WINS), ccc3(110, 255, 150), 1.1f, {mm::W().width / 2, mm::W().height * 0.62f}, 1.4f);
        mm::sfx("achievement_01.ogg", 1.f);
        mm::restoreColors(this);
    }

    void onQuit() {
        mm::lagEnd();
        mm::rainbowLeft = 0.f;
        if (mm::viewMode != 0) mm::setView(this, 0);
        PlayLayer::onQuit();
    }
};

class $modify(MmPauseLayer, PauseLayer) {
    void customSetup() {
        mm::lagEnd();
        PauseLayer::customSetup();
    }
};
