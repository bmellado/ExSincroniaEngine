#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include <cstdint>
#include "../Core/Common.hpp"

//write the code here
namespace Sincronia {

	enum class EComponentType : uint8_t {
		AudioSourceComponent,
		ComponentTypeCount
	};

	constexpr uint8_t getComponentIndex(EComponentType type){
		return static_cast<uint8_t>(type);
	}

	constexpr uint8_t getComponentTypeCount(){
		return static_cast<uint8_t>(EComponentType::ComponentTypeCount);
	}

	class AudioSourceComponent;

	
	//figure out what does this line
	template <typename ...ComponentTypes> struct DependencyList {};
}
#endif