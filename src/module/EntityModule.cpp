#include "EntityModule.hpp"
#include "../fight/Fight.hpp"
#include "WeaponModule.hpp"
#include "ChipModule.hpp"
#include "../fight/Simulator.hpp"
#include "../item/Weapon.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Team.hpp"
#include "../item/Chip.hpp"

const ls::LSClass* EntityModule::entity_clazz;
const ls::Type* EntityModule::type = new EntityType();
const ls::Type* EntityModule::const_type = type->add_constant();
const ls::Type* EntityModule::array_type = ls::Type::array(type);

EntityModule::EntityModule(ls::VM* vm) : Module(vm, "Entity") {

	EntityModule::entity_clazz = this->clazz;

	field("absoluteShield", ls::Type::integer, (void*) &Entity::getAbsoluteShield);
	field("agility", ls::Type::integer, (void*) &Entity::getAgility);
	field("cell", CellModule::type, (void*) &Entity::getCell);
	field("chips", ChipModule::array_type, (void*) &Entity::getChips);
	field("damageReturn", ls::Type::integer, (void*) &Entity::getDamageReturn);
	field("frequency", ls::Type::integer, (void*) &Entity::getFrequency);
	field("level", ls::Type::integer, (void*) &Entity::getLevel);
	field("life", ls::Type::integer, (void*) &Entity::getLife);
	field("name", ls::Type::string, (void*) &Entity::getName);
	field("magic", ls::Type::integer, (void*) &Entity::getMagic);
	field("mp", ls::Type::integer, (void*) &Entity::getMP);
	field("relativeShield", ls::Type::integer, (void*) &Entity::getRelativeShield);
	field("resistance", ls::Type::integer, (void*) &Entity::getResistance);
	field("science", ls::Type::integer, (void*) &Entity::getScience);
	field("strength", ls::Type::integer, (void*) &Entity::getStrength);
	field("talent", ls::Type::integer, (void*) &Entity::getTalent);
	field("totalMP", ls::Type::integer, (void*) &Entity::getTotalMP);
	field("totalTP", ls::Type::integer, (void*) &Entity::getTotalTP);
	field("tp", ls::Type::integer, (void*) &Entity::getTP);
	field("weapon", ls::Type::compound({WeaponModule::type, ls::Type::null}), (void*) &Entity::getWeapon);
	field("weapons", WeaponModule::array_type, (void*) &Entity::getWeapons);
	field("wisdom", ls::Type::integer, (void*) &Entity::getWisdom);

	method("getAliveAllies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_alive_allies}});
	method("getAliveEnemies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_alive_enemies}});
	method("getAllies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_allies}});
	method("getClosestAlly", {{EntityModule::type, {EntityModule::const_type}, (void*) &Entity::get_closest_ally}});
	method("getClosestEnemy", {{EntityModule::type, {EntityModule::const_type}, (void*) &Entity::get_closest_enemy}});
	method("getDeadAllies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_alive_allies}});
	method("getDeadEnemies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_alive_enemies}});
	method("getEnemies", {{EntityModule::array_type, {EntityModule::const_type}, (void*) &Entity::get_enemies}});
	method("getFarthestAlly", {{EntityModule::type, {EntityModule::const_type}, (void*) &Entity::get_farthest_ally}});
	method("getFarthestEnemy", {{EntityModule::type, {EntityModule::const_type}, (void*) &Entity::get_farthest_enemy}});
	method("isAlly", {{ls::Type::boolean, {EntityModule::const_type}, (void*) &Entity::isAlly}});
	method("isEnemy", {{ls::Type::boolean, {EntityModule::const_type}, (void*) &Entity::isEnemy}});
	method("moveToward", {
		{ls::Type::integer, {EntityModule::const_type, EntityModule::const_type, ls::Type::const_integer}, (void*) &Entity::moveTowardMP},
		{ls::Type::integer, {EntityModule::const_type, EntityModule::const_type}, (void*) &Entity::moveToward},
		{ls::Type::integer, {EntityModule::const_type, CellModule::const_type, ls::Type::const_integer}, (void*) &Entity::moveTowardCellMP},
		{ls::Type::integer, {EntityModule::const_type, CellModule::const_type}, (void*) &Entity::moveTowardCell},
		{ls::Type::integer, {ls::Type::any}, (void*) &entity__moveToward}
	});
	method("useChip", {
		{ls::Type::integer, {EntityModule::const_type, ChipModule::const_type, EntityModule::const_type}, (void*) &Entity::useChip},
		{ls::Type::integer, {ls::Type::any, ls::Type::any}, (void*) &entity__useChip}
	});
	method("useWeapon", {
		{ls::Type::integer, {EntityModule::const_type, EntityModule::const_type}, (void*) &Entity::useWeapon},
		{ls::Type::integer, {ls::Type::any}, (void*) &entity__useWeapon}
	});
	method("say", {{ls::Type::boolean, {EntityModule::const_type, ls::Type::const_any}, (void*) &Entity::say}});
	method("setWeapon", {
		{ls::Type::null, {EntityModule::const_type, WeaponModule::const_type}, (void*) &entity_setWeapon},
		{ls::Type::null, {EntityModule::const_type, ls::Type::const_integer}, (void*) &Entity::setWeaponInteger},
		{ls::Type::boolean, {ls::Type::any}, (void*) &entity__setWeapon}
	});

	/*
	 * V1 functions
	 */
	method("getAbsoluteShield", {
		{ls::Type::any, {}, (void*) &entity__getAbsoluteShield},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getAbsoluteShieldEntity}
	});
	method("getAgility", {
		{ls::Type::any, {}, (void*) &entity__getAgility},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getAgilityEntity}
	});
	method("getBirthTurn", {
		{ls::Type::integer, {}, (void*) &entity__getBirthTurn},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getBirthTurnEntity}
	});
	method("getCell", {
		{ls::Type::integer, {}, (void*) &entity__getCell},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getCellEntity}
	});
	method("getChips", {
		{ls::Type::array(ls::Type::integer), {}, (void*) &entity__getChips},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getChipsEntity},
	});
	method("getCores", {
		{ls::Type::integer, {}, (void*) &entity__getCores},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getCoresEntity},
	});
	method("getDamageReturn", {
		{ls::Type::integer, {}, (void*) &entity__getDamageReturn},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getDamageReturnEntity}
	});
	method("getEffects", {
		{ls::Type::array(), {}, (void*) &entity__getEffects},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getEffectsEntity}
	});
	method("getEntityTurnOrder", {
		{ls::Type::integer, {}, (void*) &entity__getEntityTurnOrder},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getEntityTurnOrderEntity}
	});
	method("getFrequency", {
		{ls::Type::integer, {}, (void*) &entity__getFrequency},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getFrequencyEntity}
	});
	method("getLaunchedEffects", {
		{ls::Type::array(), {}, (void*) &entity__getLaunchedEffects},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getLaunchedEffectsEntity}
	});
	method("getLeekID", {
		{ls::Type::integer, {}, (void*) &entity__getLeekID},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getLeekIDEntity}
	});
	method("getLevel", {
		{ls::Type::integer, {}, (void*) &entity__getLevel},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getLevelEntity}
	});
	method("getLife", {
		{ls::Type::integer, {}, (void*) &entity__getLife},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getLifeEntity}
	});
	method("getMagic", {
		{ls::Type::integer, {}, (void*) &entity__getMagic},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getMagicEntity}
	});
	method("getMP", {
		{ls::Type::integer, {}, (void*) &entity__getMP},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getMPEntity}
	});
	method("getName", {
		{ls::Type::string, {}, (void*) &entity__getName},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getNameEntity}
	});
	method("getNearestEnemy", {
		{ls::Type::integer, {}, (void*) &entity__getNearestEnemy}
	});
	method("getNearestAlly", {
		{ls::Type::integer, {}, (void*) &entity__getNearestAlly}
	});
	method("getRelativeShield", {
		{ls::Type::integer, {}, (void*) &entity__getRelativeShield},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getRelativeShieldEntity}
	});
	method("getResistance", {
		{ls::Type::integer, {}, (void*) &entity__getResistance},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getResistanceEntity}
	});
	method("getScience", {
		{ls::Type::integer, {}, (void*) &entity__getScience},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getScienceEntity}
	});
	method("getStrength", {
		{ls::Type::integer, {}, (void*) &entity__getStrength},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getStrengthEntity}
	});
	method("getSummoner", {
		{ls::Type::integer, {}, (void*) &entity__getSummoner},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getSummonerEntity}
	});
	method("getTeamID", {
		{ls::Type::integer, {}, (void*) &entity__getTeamID},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTeamIDEntity}
	});
	method("getTeamName", {
		{ls::Type::string, {}, (void*) &entity__getTeamName},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTeamNameEntity}
	});
	method("getTotalLife", {
		{ls::Type::integer, {}, (void*) &entity__getTotalLife},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTotalLifeEntity}
	});
	method("getTotalMP", {
		{ls::Type::integer, {}, (void*) &entity__getTotalMP},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTotalMPEntity}
	});
	method("getTotalTP", {
		{ls::Type::integer, {}, (void*) &entity__getTotalTP},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTotalTPEntity}
	});
	method("getTP", {
		{ls::Type::integer, {}, (void*) &entity__getTP},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTPEntity}
	});
	method("getType", {
		{ls::Type::integer, {}, (void*) &entity__getType},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getTypeEntity}
	});
	method("getWeapon", {
		{ls::Type::compound({ls::Type::number, ls::Type::null}), {}, (void*) &entity__getWeapon},
		{ls::Type::compound({ls::Type::number, ls::Type::null}), {ls::Type::any}, (void*) &entity__getWeaponEntity}
	});
	method("getWeapons", {
		{ls::Type::array(ls::Type::integer), {}, (void*) &entity__getWeapons},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getWeaponsEntity}
	});
	method("getWisdom", {
		{ls::Type::integer, {}, (void*) &entity__getWisdom},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getWisdomEntity}
	});
	method("isAlive", {{ls::Type::boolean, {ls::Type::any}, (void*) &entity__isAlive}});
	method("isAlly", {{ls::Type::boolean, {ls::Type::any}, (void*) &entity__isAlly}});
	method("isDead", {{ls::Type::boolean, {ls::Type::any}, (void*) &entity__isDead}});
	method("isEnemy", {{ls::Type::boolean, {ls::Type::any}, (void*) &entity__isEnemy}});
	method("isSummon", {
		{ls::Type::boolean, {}, (void*) &entity__isSummon},
		{ls::Type::any, {ls::Type::any}, (void*) &entity__isSummonEntity},
	});

	method("getCooldown", {
		{ls::Type::any, {ls::Type::any}, (void*) &entity__getCooldown},
		{ls::Type::any, {ls::Type::any, ls::Type::any}, (void*) &entity__getCooldownEntity},
	});

	method("listen", {{ls::Type::any, {ls::Type::any}, (void*) &entity__listen}});
	method("moveAwayFrom", {
		{ls::Type::integer, {ls::Type::any}, (void*) &entity__moveAwayFrom},
		{ls::Type::integer, {ls::Type::any, ls::Type::integer}, (void*) &entity__moveAwayFromMP},
	});
	method("say", {{ls::Type::any, {ls::Type::any}, (void*) &entity__say}});
}

EntityModule::~EntityModule() {}

const Weapon* entity_getWeapon(Entity* entity) {
	return (Weapon*) entity->getWeapon();
}

const ls::LSArray<Weapon*>* entity_getWeapons(Entity* entity) {
	return (const ls::LSArray<Weapon*>*) entity->getField("weapons");
}

const ls::LSNull* entity_setWeapon(Entity* entity, const Weapon* weapon) {
	entity->setWeapon(weapon);
	return (ls::LSNull*) ls::LSNull::get();
}

/*
 * LS v1 support functions (deprecated in v2)
 */

/*
 * Internal function to get an entity characteristic
 */
inline ls::LSValue* entity__getCharacteristic(const ls::LSValue* entity, Characteristic charac) {

	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();

	return ls::LSNumber::get(e->getCharacteristic(charac));
}

/*
 * Characteristics methods, all the same
 * Null if invalid entity, int otherwise
 */
int entity__getAbsoluteShield() {
	return Simulator::entity->getAbsoluteShield();
}
ls::LSValue* entity__getAbsoluteShieldEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::ABSOLUTE_SHIELD);
}
int entity__getAgility() {
	return Simulator::entity->getAgility();
}
ls::LSValue* entity__getAgilityEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::AGILITY);
}
int entity__getFrequency() {
	return Simulator::entity->getFrequency();
}
ls::LSValue* entity__getFrequencyEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::FREQUENCY);
}
int entity__getCores() {
	return 0; // was already deprecated in v1
}
ls::LSValue* entity__getCoresEntity(const ls::LSValue*) {
	return ls::LSNumber::get(0); // was already deprecated in v1
}
int entity__getDamageReturn() {
	return Simulator::entity->getDamageReturn();
}
ls::LSValue* entity__getDamageReturnEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::DAMAGE_RETURN);
}
int entity__getMagic() {
	return Simulator::entity->getMagic();
}
ls::LSValue* entity__getMagicEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MAGIC);
}
int entity__getRelativeShield() {
	return Simulator::entity->getRelativeShield();
}
ls::LSValue* entity__getRelativeShieldEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RELATIVE_SHIELD);
}
int entity__getResistance() {
	return Simulator::entity->getResistance();
}
ls::LSValue* entity__getResistanceEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::RESISTANCE);
}
int entity__getScience() {
	return Simulator::entity->getScience();
}
ls::LSValue* entity__getScienceEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::SCIENCE);
}
int entity__getStrength() {
	return Simulator::entity->getStrength();
}
ls::LSValue* entity__getStrengthEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::STRENGTH);
}
int entity__getTotalLife() {
	return Simulator::entity->getTotalLife();
}
ls::LSValue* entity__getTotalLifeEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::LIFE);
}
int entity__getTotalMP() {
	return Simulator::entity->getTotalMP();
}
ls::LSValue* entity__getTotalMPEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::MP);
}
int entity__getTotalTP() {
	return Simulator::entity->getTotalTP();
}
ls::LSValue* entity__getTotalTPEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::TP);
}
int entity__getWisdom() {
	return Simulator::entity->getWisdom();
}
ls::LSValue* entity__getWisdomEntity(const ls::LSValue* entity) {
	return entity__getCharacteristic(entity, Characteristic::WISDOM);
}

int entity__getLife() {
	return Simulator::entity->getLife();
}
ls::LSValue* entity__getLifeEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->life);
}

int entity__getTP() {
	return Simulator::entity->getTP();
}
ls::LSValue* entity__getTPEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getTP());
}

int entity__getMP() {
	return Simulator::entity->getMP();
}
ls::LSValue* entity__getMPEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->getMP());
}

int entity__getBirthTurn() {
	return 0;
}
ls::LSValue* entity__getBirthTurnEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(0);
}

int entity__getCell() {
	return Simulator::entity->cell->id;
}
ls::LSValue* entity__getCellEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->cell->id);
}

ls::LSArray<int>* entity__getChips() {
	auto ret = new ls::LSArray<int>(Simulator::entity->chips.size());
	for (const auto& chip : Simulator::entity->chips) {
		ret->push_back(((Chip*) chip)->id);
	}
	return ret;

}
ls::LSValue* entity__getChipsEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->chips.clone();
}

ls::LSArray<ls::LSValue*>* entity__getEffects() {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getEffectsEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getEntityTurnOrder() {
	// TODO
}
ls::LSValue* entity__getEntityTurnOrderEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSArray<ls::LSValue*>* entity__getLaunchedEffects() {
	// TODO
//	return LSNull::null_var;
}
ls::LSValue* entity__getLaunchedEffectsEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLeekID() {
	return Simulator::entity->id;
}
ls::LSValue* entity__getLeekIDEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

int entity__getLevel() {
	return Simulator::entity->level;
}
ls::LSValue* entity__getLevelEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->level);
}

ls::LSString* entity__getName() {
	return new ls::LSString(Simulator::entity->name);
}
ls::LSValue* entity__getNameEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->name);
}

int entity__getNearestEnemy() {
	return Simulator::entity->get_closest_enemy()->id;
}
int entity__getNearestAlly() {
	return Simulator::entity->get_closest_ally()->id;
}

ls::LSValue* entity__getSummoner() {
	// TODO
}
ls::LSValue* entity__getSummonerEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getTeamID() {
	// TODO
//	return LSNumber::get(e->team_id);
}
ls::LSValue* entity__getTeamIDEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNumber::get(e->team_id);
}

/*
 * Null or string
 */
ls::LSValue* entity__getTeamName() {
//	return new LSString(e->team_name);
}
ls::LSValue* entity__getTeamNameEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return new ls::LSString(e->team_name);
}

ls::LSValue* entity__getType() {
	// TODO
}
ls::LSValue* entity__getTypeEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

ls::LSValue* entity__getWeapon() {
	return Simulator::entity->weapon == nullptr ? ls::LSNull::get() : ls::LSNumber::get(Simulator::entity->weapon->id);
}
ls::LSValue* entity__getWeaponEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapon->clone();
}

ls::LSArray<int>* entity__getWeapons() {
	auto ret = new ls::LSArray<int>(Simulator::entity->weapons.size());
	for (const auto& weapon : Simulator::entity->weapons) {
		ret->push_back(((Weapon*) weapon)->id);
	}
	return ret;
}
ls::LSValue* entity__getWeaponsEntity(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->weapons.clone();
}

bool entity__isAlive(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isAlive();
}

bool entity__isDead(const ls::LSValue* entity) {
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return e->isDead();
}

bool entity__isAlly(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isEnemy(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return ls::LSNull::get();
	return ls::LSNull::get();
}

bool entity__isSummon() {
	// TODO
	return false;
}
bool entity__isSummonEntity(const ls::LSValue* entity) {
	// TODO
	Entity* e = Simulator::getEntity(entity);
	if (e == nullptr) return false;
	return false;
}

ls::LSArray<ls::LSValue*>* entity__listen() {
	// TODO
	return new ls::LSArray<ls::LSValue*>();
}

int entity__moveAwayFrom(const ls::LSValue* entity) {
	auto e = Simulator::getEntity(entity);
	if (e == nullptr) {
		return 0;
	}
	return Simulator::entity->moveAwayFrom(e);
}

int entity__moveAwayFromMP(const ls::LSValue* entity, int mp) {
	auto e = Simulator::getEntity(entity);
	if (e == nullptr) {
		return 0;
	}
	return Simulator::entity->moveAwayFrom(e);
}

int entity__moveToward(const ls::LSValue* entity) {
	auto e = Simulator::getEntity(entity);
	if (e == nullptr) {
		return 0;
	}
	return Simulator::entity->moveToward(e);
}

bool entity__say(const ls::LSValue* message) {
	return Simulator::entity->say(message);
}

bool entity__setWeapon(const ls::LSNumber* weapon) {
	if (weapon == nullptr) return false;
	return Simulator::entity->setWeaponInteger(weapon->value);
}

/*
 * Null or int
 */
ls::LSValue* entity__getCooldown(const ls::LSValue* chip) {
	// TODO
}
ls::LSValue* entity__getCooldownEntity(const ls::LSValue* chip, const ls::LSValue* entity) {
	// TODO
}

ls::LSValue* entity__resurrect() {
	// TODO
}
ls::LSValue* entity__summon() {
	// TODO
}
int entity__useChip(ls::LSValue* chip, ls::LSValue* target) {
	auto e = Simulator::getEntity(target);
	return Simulator::entity->useChip((Chip*) chip, e);
}
ls::LSValue* entity__useChipOnCell() {
	// TODO
}

int entity__useWeapon(ls::LSValue* target) {
	auto e = Simulator::getEntity(target);
	return Simulator::entity->useWeapon(e);
}
