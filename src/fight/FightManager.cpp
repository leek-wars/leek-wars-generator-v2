#include "FightManager.hpp"
#include "../module/FightModule.hpp"
#include "../module/EntityModule.hpp"
#include "../module/MapModule.hpp"
#include "../module/CellModule.hpp"
#include "../module/LeekModule.hpp"
#include "../module/WeaponModule.hpp"
#include "../module/ColorModule.hpp"
#include "../module/ChipModule.hpp"

FightManager::FightManager() : vm(), vm_v1(true) {
	vm.add_module(new FightModule());
	vm.add_module(new EntityModule());
	vm.add_module(new LeekModule());
	vm.add_module(new MapModule());
	vm.add_module(new CellModule());
	vm.add_module(new WeaponModule());
	vm.add_module(new ColorModule());
	vm.add_module(new ChipModule());
	vm_v1.add_module(new FightModule());
	vm_v1.add_module(new EntityModule());
	vm_v1.add_module(new LeekModule());
	vm_v1.add_module(new MapModule());
	vm_v1.add_module(new CellModule());
	vm_v1.add_module(new WeaponModule());
	vm_v1.add_module(new ColorModule());
	vm_v1.add_module(new ChipModule());
}

Report* FightManager::start(Fight& fight) {
	return fight.start(vm, vm_v1);
}