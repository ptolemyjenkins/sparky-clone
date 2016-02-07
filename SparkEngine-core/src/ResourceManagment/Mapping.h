#pragma once
#include <unordered_map>
#include "../maths/vec3.h"

namespace sparky { namespace resource {
	class Mapping {
	private:
		std::unordered_map<std::string, maths::vec3> vec3HashMap;
		std::unordered_map<std::string, float> floatHashMap;
	public:
		Mapping() {

		}
		void addVec3(std::string name, maths::vec3 vector) {
			vec3HashMap[name] = vector;
		}
		
		void addFloat(std::string name, float floatValue) {
			floatHashMap[name] = floatValue;
		}

		maths::vec3 getVec3(std::string name) {
			auto result = vec3HashMap.find(name);
			if (result != vec3HashMap.end()) {
				return *(&result->second);
			}

			return maths::vec3();
		}

		float getFloat(std::string name) {
			auto result = floatHashMap.find(name);
			if (result != floatHashMap.end()) {
				return *(&result->second);
			}

			return 0;
		}
	};
} }