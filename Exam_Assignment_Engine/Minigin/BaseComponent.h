#pragma once


namespace dae
{
	class GameObject;
	class TransformComponent;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		virtual ~BaseComponent() = default;
		BaseComponent() = default;;

		GameObject* GetGameObject() const { return m_pGameObject; }
		TransformComponent* GetTransform() const;

	protected:
		virtual void Update() = 0;
		virtual void Render() const = 0;

		GameObject* m_pGameObject;
	};
};

