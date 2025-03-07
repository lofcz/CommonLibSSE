#pragma once

#include "RE/B/BSKeyboardDevice.h"

namespace RE
{
	struct __DIDEVICEOBJECTDATA
	{
		std::uint32_t  dwOfs;        // 00
		std::uint32_t  dwData;       // 04
		std::uint32_t  dwTimeStamp;  // 08
		std::uint32_t  dwSequence;   // 0C
		std::uint32_t* uAppData;     // 10
	};
	static_assert(sizeof(__DIDEVICEOBJECTDATA) == 0x18);

	class BSWin32KeyboardDevice : public BSKeyboardDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32KeyboardDevice;

		~BSWin32KeyboardDevice() override;  // 00

		// override (BSKeyboardDevice)
		void Initialize() override;           // 01
		void Process(float a_unk1) override;  // 02
		void Release() override;              // 03
		void Reset() override;                // 08 - { std::memset(&curState, 0, 0x200); }
		void Unk_09(void) override;           // 09 - { return; }
		void Unk_0A(void) override;           // 0A - { return; }

		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;

		// members
		void*                dInputDevice;      // 070 -- IDirectInputDevice8A*
		__DIDEVICEOBJECTDATA diObjData[10];     // 078
		std::uint8_t         prevState[0x100];  // 168
		std::uint8_t         curState[0x100];   // 268
		bool                 capsLockOn;        // 368
	};
	static_assert(offsetof(BSWin32KeyboardDevice, prevState) == 0x168);
	static_assert(offsetof(BSWin32KeyboardDevice, curState) == 0x268);
	static_assert(sizeof(BSWin32KeyboardDevice) == 0x370);
}
