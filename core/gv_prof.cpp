// Copyright (c) 2026 Skitzelles - part of Game Vault, https://github.com/skitzellez/xbox-game-vault
// Flycast for Game Vault: see gv_prof.h. GPL-2.0 like the rest of Flycast.
#include "gv_prof.h"
#include "log/Log.h"

namespace gvprof
{
std::atomic<int64_t> total[SlotCount];
std::atomic<int64_t> n2Calls, n2Uploads, draws;
std::atomic<int> swapInterval, refreshRate;
static int frames;
static int64_t since;

void frame()
{
	int64_t now = nowUs();
	if (since == 0)
		since = now;
	frames++;
	int64_t span = now - since;
	if (span < 2000000)
		return;
	double f = frames ? frames : 1;
	auto ms = [&](Slot s) { return total[s].exchange(0) / 1000.0 / f; };
	double waitRender = ms(EmuWaitRender), waitQueue = ms(EmuWaitQueue), elan = ms(Elan);
	double process = ms(RendProcess), render = ms(RendRender), present = ms(RendPresent), swap = ms(Swap);
	NOTICE_LOG(COMMON, "GVPROF fps %.1f | ms/frame: elan %.2f, emu waits render %.2f, emu waits queue %.2f | "
			"render thread: process %.2f, render %.2f, present %.2f | n2 consts/frame %.0f, uploaded %.0f | swap %.2f ms (interval %d at %d Hz) | draws/frame %.0f",
			frames * 1e6 / span, elan, waitRender, waitQueue, process, render, present,
			n2Calls.exchange(0) / f, n2Uploads.exchange(0) / f, swap, swapInterval.load(), refreshRate.load(), draws.exchange(0) / f);
	frames = 0;
	since = now;
}
}
