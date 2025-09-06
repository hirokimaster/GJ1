#pragma once
#include <functional>
#include <application/GameObject/Unit/BaseUnit.h>
#include <map>

class UnitFactory {
public:

	using Unit = std::function<std::unique_ptr<BaseUnit>()>;

	// 登録
	static void Register(const std::string& name, Unit unit) {
		GetRegistryInstance()[name] = unit;
	}

	// 生成
	static std::unique_ptr<BaseUnit> Create(const std::string& name) {
		auto& instance = GetRegistryInstance();
		if (instance.find(name) != instance.end()) {
			return instance[name]();
		}
		return nullptr;
	}


private:
	static std::unordered_map<std::string, Unit>& GetRegistryInstance() {
		static std::unordered_map<std::string, Unit> instance;
		return instance;
	}
};
