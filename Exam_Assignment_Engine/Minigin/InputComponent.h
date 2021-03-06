#pragma once
#include "BaseComponent.h"
#include <Xinput.h>
#include "InputAction.h"

namespace dae
{

	class InputComponent : public BaseComponent
	{
		friend class InputManager;
	public:
		InputComponent(int controllerId = -1, bool useKeyboardInput = true);
	    ~InputComponent();

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;

		void SetControllerId(int newId) { m_ControllerId = newId; };
		void AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode, ControllerInput controllerInput);
		void AddInputAction(InputResponse* response, SDL_Keycode keyBoardScanecode);
		void AddInputAction(InputResponse* response, ControllerInput controllerInput);
		void GetInputAction(const std::wstring& responseName);

		void DisableInput() {m_Enabled = false;};
		void EnableInput() { m_Enabled = true; };

		void SetScene(Scene* scene) { m_pScene = scene; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;

	private:
		void HandleControllerInput(XINPUT_STATE& gamePadState, XINPUT_STATE& prevGamePadState);
		void HandleKeyboardInput(const UINT8* keyboardState, const UINT8* prevKeyboardState);

		int m_ControllerId;
		bool m_UsingKeyboardInput;

		bool m_Enabled;

		std::vector<InputAction*> m_pInputActions;

		Scene* m_pScene;
	};

}
