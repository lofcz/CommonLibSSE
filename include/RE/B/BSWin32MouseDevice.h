#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSMouseDevice.h"

namespace RE
{
	struct __DIMOUSESTATE2
	{
		std::int32_t lX;
		std::int32_t lY;
		std::int32_t lZ;
		std::byte    rgbButtons[8];
	};

	class BSWin32MouseDevice : public BSMouseDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32MouseDevice;

		struct Keys
		{
			enum Key : std::uint32_t
			{
				kLeftButton,
				kRightButton,
				kMiddleButton,
				kButton3,
				kButton4,
				kButton5,
				kButton6,
				kButton7,
				kWheelUp,
				kWheelDown
			};
		};
		using Key = Keys::Key;

		~BSWin32MouseDevice() override;  // 00

		// override (BSMouseDevice)
		void Initialize() override;           // 01
		void Process(float a_arg1) override;  // 02
		void Release() override;              // 03
		void Reset() override;                // 08
		void Reinitialize(void) override;     // 09

		// members
		void*              dInputDevice;      // 78 - IDirectInputDevice8A*
		__DIMOUSESTATE2    dInputPrevState;   // 80
		__DIMOUSESTATE2    dInputNextState;   // 94
		bool               notInitialized;    // A8
		mutable BSSpinLock reinitializeLock;  // AC
	};
	static_assert(sizeof(BSWin32MouseDevice) == 0xB8);
}
