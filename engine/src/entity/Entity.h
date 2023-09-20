//
// Created by cx9ps3 on 14.05.2023.
//

#pragma once

#include "../components/Component.hpp"
#include "../core/Types.hpp"
#include "../core/uuid/uuid.hpp"
#include "../core/exceptions/ComponentNotFound.hpp"
#include <algorithm>
#include <iostream>

namespace hexen::engine::entity
{
	/**
 	* @class Entity
 	* @brief  This class represents a unique entity, identified by a UUID.
 	*/
	class Entity
	{
	public:

		/**
     	* @brief Default constructor for the Entity class.
     	*        By default, this will create an entity without a UUID.
     	*/

		Entity();

		/**
     	* @brief An explicit constructor for the Entity class that accepts a UUID.
     	* @param UUID A string representing the UUID of the entity.
     	*/

		explicit Entity(std::string UUID);

		/**
     	* @brief The default virtual destructor for the Entity class.
     	*        This destructor does nothing by default and is provided to allow child classes to override it if necessary.
     	*/

		virtual ~Entity() = default;

		/**
     	* @brief The move constructor for the Entity class is deleted to prevent instances of Entity from being movable.
     	* @param entity An rvalue reference to an Entity instance.
     	*/

		Entity(Entity &&entity) = delete;

		/**
     	* @brief The copy constructor for the Entity class is deleted to prevent instances of Entity from being copyable.
     	* @param entity A const reference to an Entity instance.
     	*/

		Entity(const Entity &entity) = delete;

		/**
     	* @brief The move assignment operator for the Entity class is deleted to prevent instances of Entity from being moved.
     	* @param entity An rvalue reference to an Entity instance.
     	* @return A reference to the current instance of Entity.
     	*/

		Entity &operator=(Entity &&entity) = delete;

		/**
     	* @brief  The copy assignment operator for the Entity class is deleted to prevent instances of Entity from being copied.
     	* @param  entity A const reference to an Entity instance.
     	* @return A reference to the current instance of Entity.
     	*/

		Entity &operator=(const Entity &entity) = delete;

		/**
 		* @brief A function that fetches a UUID.
 		*
 		* This function is marked as noexcept and [[nodiscard]] implying that exceptions are not thrown
 		* and the result must not be discarded.
 		*
 		* @return std::string Returns a string representation of a UUID.
 		*/

		[[nodiscard]] std::string getUUID() const noexcept;

		/**
 		* @brief Register a new component with a unique ID.
 		*
 		* This template function allows you to associate an instance
 		* of a class with a unique ID and store it in components structure.
 		*
 		* @tparam T The type of the component. The function can accept any class type.
 		* @param component The instance of the class that you want to store.
 		*/

		template<class T>
		void addComponent(T &&component)
		{
			components.set(generateUUIDV4(), std::forward<T>(component));
		}

		/**
 		* @brief Adds a new component of type T with the specified parameters
 		*
 		* This method instantiates a new component with the specified parameters
 		* and store it in the components map with a UUID generated by generateUUIDV4().
	 	*
 		* @tparam T The type of the component to add
 		* @tparam Ts The types of the arguments to pass to the constructor of the component
 		* @param params The parameters to pass to the constructor of the component
 		*/

		template<class T, class... Ts>
		void addComponent(Ts &&...params)
		{
			components.set(generateUUIDV4(), core::memory::make_shared<T>(params...));
		}

		/**
 		* @brief Gets a component of type T with the specified name
 		*
 		* This method finds a component in the components map using the specified name.
 		* If found, it attempts a dynamic cast to the requested type and returns the component.
 		* If no component is found with the specified name, it throws a ComponentNotFound exception.
 		*
 		* @tparam T The type of the component to get
 		* @param name The name of the component to get
 		* @return T The component of type T with the specified name
 		* @throws hexen::engine::exceptions::ComponentNotFound Thrown when no component is found with the specified name
 		*/

		template<class T>
		T getComponentByName(const std::string &name)
		{
			auto component = std::find_if(components.cbegin(), components.cend(), [name = name](auto &comp)
					{ return comp->getName() == name; });
			if (component != components.cend())
			{
				return dynamic_cast<T>(*component);
			}
			else
			{
				throw hexen::engine::exceptions::ComponentNotFound(name);
			}
		}

		/**
 		* @brief Gets a component of type T with the specified UUID
 		*
 		* This method gets a component from the components map using the specified UUID.
 		* It then attempts a dynamic cast to the requested type and returns the component.
 		*
 		* @tparam T The type of the component to get
 		* @param UUID The UUID of the component to get
 		* @return T The component of type T with the specified UUID
 		*/

		template<class T>
		T getComponentByUUID(const std::string &UUID)
		{
			return dynamic_cast<T>(components[UUID]);
		}

	private:
		std::string UUID;
		core::HashTable<std::string, std::shared_ptr<components::Component>> components;
	};

}// namespace hexen::engine::entity
