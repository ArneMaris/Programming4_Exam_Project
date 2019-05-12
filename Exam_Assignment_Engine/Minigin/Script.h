#pragma once

namespace dae
{

class Script
{
	friend class ScriptComponent;
	public:
		Script() = default;
		virtual ~Script() = default;
		Script(const Script& other) = delete;
		Script(Script&& other) = delete;
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void PostRender() const = 0;
		virtual void Initialize() = 0;
	protected:
		GameObject* m_pOwnerObject;
	};
}

