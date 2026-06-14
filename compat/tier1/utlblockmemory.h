// Compatibility wrapper: Clang rejects V_swap() on bit-field members in the
// SDK's CUtlBlockMemory::Swap(). The template V_swap(T&, T&) takes non-const
// references, which cannot bind to bit-fields (m_nIndexMask : 27 and
// m_nIndexShift : 5). GCC and MSVC accept this in an uninstantiated template;
// Clang does not.
//
// Fix: pre-include mathlib.h (so its include guard prevents re-entry), then
// temporarily shadow V_swap with a copy-through-temporary macro that is
// bit-field-safe. After the real header is processed, restore V_swap so the
// rest of the codebase uses the original template. [APG]RoboCop[CL]

#ifndef RCBOT2_COMPAT_TIER1_UTLBLOCKMEMORY_H
#define RCBOT2_COMPAT_TIER1_UTLBLOCKMEMORY_H

#pragma push_macro("V_swap")
#undef V_swap
#define V_swap(a, b) do { auto rcbot_v_swap_tmp = (a); (a) = (b); (b) = rcbot_v_swap_tmp; } while (false)

#include_next "tier1/utlblockmemory.h"

#pragma pop_macro("V_swap")

#endif // RCBOT2_COMPAT_TIER1_UTLBLOCKMEMORY_H
