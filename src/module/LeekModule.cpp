#include "LeekModule.hpp"
#include "../entity/Leek.hpp"
#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../fight/Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* LeekModule::leek_clazz;
const ls::Type* LeekModule::type = new LeekType();

LeekModule::LeekModule(ls::VM* vm) : Module(vm, "Leek") {

	method("getFarmerID", {
		{ls::Type::integer, {LeekModule::type}, (void*) &leek_getFarmerID}
	});
	method("getFarmerName", {
		{ls::Type::string, {LeekModule::type}, (void*) &leek_getFarmerName}
	});

	// V1 methods
	method("getAIID", {
		{ls::Type::integer, {}, (void*) &leek__getAIID},
		{ls::Type::any, {ls::Type::any}, (void*) &leek__getAIIDEntity},
	});
	method("getAIName", {
		{ls::Type::string, {}, (void*) &leek__getAIName},
		{ls::Type::any, {ls::Type::any}, (void*) &leek__getAINameEntity},
	});
	method("getFarmerID", {
		{ls::Type::integer, {}, (void*) &leek__getFarmerID},
		{ls::Type::any, {ls::Type::any}, (void*) &leek__getFarmerIDEntity},
	});
	method("getFarmerName", {
		{ls::Type::string, {}, (void*) &leek__getFarmerName},
		{ls::Type::any, {ls::Type::any}, (void*) &leek__getFarmerNameEntity},
	});
}

LeekModule::~LeekModule() {}

int leek_getFarmerID(Leek* leek) {
	return leek->farmer;
}

const ls::LSString* leek_getFarmerName(Leek* leek) {
	return (ls::LSString*) leek->getField("farmerName");
}


/*
 * V1 methods
 */
inline Entity* leek__getEntity(const ls::LSValue* entity) {

	if (dynamic_cast<const ls::LSNull*>(entity)) {
		return Simulator::entity;
	}
	if (const ls::LSNumber* n = dynamic_cast<const ls::LSNumber*>(entity)) {
		return Simulator::fight->getEntity(n->value);
	}
	return nullptr;
}

int leek__getAIID() {
	return Simulator::entity->ai->id;
}
ls::LSValue* leek__getAIIDEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->ai->id);
}

ls::LSString* leek__getAIName() {
	return new ls::LSString(Simulator::entity->ai->name);
}
ls::LSValue* leek__getAINameEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->ai->name);
}

int leek__getFarmerID() {
	// TODO
	return 0;
}
ls::LSValue* leek__getFarmerIDEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSString* leek__getFarmerName() {
	// TODO
	return new ls::LSString(Simulator::entity->farmer_name);
}
ls::LSValue* leek__getFarmerNameEntity(const ls::LSValue* entity) {
	Entity* e = leek__getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->farmer_name);
}
