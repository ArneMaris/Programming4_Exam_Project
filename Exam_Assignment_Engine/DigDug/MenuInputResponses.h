#pragma once
#include <InputResponse.h>

namespace MenuInput
{

	class KeyUp final : public dae::InputResponse
	{
	public:
		KeyUp() = default;
		~KeyUp() = default;

		//override these 3 functions to handle the input with your custom actions
		virtual void ExecuteOnPress() override;
		virtual void ExecuteOnRelease() override;
	};
	class KeyDown final : public dae::InputResponse
	{
	public:
		KeyDown() = default;
		~KeyDown() = default;

		//override these 3 functions to handle the input with your custom actions
		virtual void ExecuteOnPress() override;
		virtual void ExecuteOnRelease() override;
	};

	class Stick final : public dae::InputResponse
	{
	public:
		Stick() = default;
		~Stick() = default;

		//override these 3 functions to handle the input with your custom actions
		virtual void ExecuteOnPress() override;
		virtual void ExecuteOnRelease() override;
	};

}
