#pragma once

#include <map>
#include <memory>

#include <SFGUI\Widgets.hpp>

namespace FlappyBirdClone
{
	class Ui
	{
	private:
		std::map<int, std::shared_ptr<sfg::Widget>> elements;

	public:
		template <typename Widget, typename ...Args>
		std::shared_ptr<Widget> Add(int id, Args&&... args)
		{
			auto res = Widget::Create(std::forward<Args>(args)...);
			elements[id] = res;

			return res;
		}

		template <typename Widget>
		std::shared_ptr<Widget> Get(int id)
		{
			if (elements.count(id) == 0) {
				throw new std::exception("Element not found!");
			}

			return std::static_pointer_cast<Widget>(elements[id]);
		}

		void Update(float delta)
		{
			for (auto& el : elements) {
				el.second->Update(delta);
			}
		}

		void ProcessEvent(sf::Event& event)
		{
			for (auto& el : elements) {
				el.second->HandleEvent(event);
			}
		}
	};
}
