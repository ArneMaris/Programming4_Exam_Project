#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Script;
	class ScriptComponent : public BaseComponent
	{
	public:
		ScriptComponent(Script* script);
		~ScriptComponent();
		ScriptComponent(const ScriptComponent& other) = delete;
		ScriptComponent(ScriptComponent&& other) = delete;
		ScriptComponent& operator=(const ScriptComponent& other) = delete;
		ScriptComponent& operator=(ScriptComponent&& other) = delete;

		//carefull other will be deleted! dont use it anywhere else after this
		void SetNewScript(Script* newScript);

		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() const override;
		virtual void PostRender() const override;
	private:
		Script* m_pScript;
	};
}

