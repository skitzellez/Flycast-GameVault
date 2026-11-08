// Copyright (c) 2026 Skitzelles - part of Game Vault, https://github.com/skitzellez/xbox-game-vault
// Flycast for Game Vault: a small timer to find what makes a game slow on the Xbox. Each 2 s one log line:
// frames per second and milliseconds per frame spent in each timed part. GPL-2.0 like the rest of Flycast.
#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>

namespace gvprof
{
enum Slot { EmuWaitRender, EmuWaitQueue, Elan, RendProcess, RendRender, RendPresent, Swap, SlotCount };

extern std::atomic<int64_t> total[SlotCount];
extern std::atomic<int64_t> n2Calls, n2Uploads, draws;
extern std::atomic<int> swapInterval, refreshRate;   // the last swap-chain Present: its interval, the display's Hz   // NAOMI 2 per-polygon constants: asked for, really uploaded

inline int64_t nowUs()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::steady_clock::now().time_since_epoch()).count();
}

struct Scope
{
	Slot slot;
	int64_t t0;
	explicit Scope(Slot s) : slot(s), t0(nowUs()) {}
	~Scope() { total[slot] += nowUs() - t0; }
};

// once per presented frame (render thread)
void frame();
}
