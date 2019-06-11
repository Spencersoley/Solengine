#include "EffectManager.h"

#include "UIText.h"

EffectManager::EffectManager() {}

EffectManager::~EffectManager() {}

void EffectManager::updateEffects(float adj)
{
	for (size_t i = 0; i < p_visualEffects.size(); i++)
		if (!p_visualEffects[i]->updateEffect(adj))
		{
			p_visualEffects[i] = p_visualEffects.back();
			p_visualEffects.pop_back();
			i--;
		}
}

void EffectManager::newCombatEffect(Unit* tarUnit, Spell* spellCast)
{
	Solengine::ColourRGBA8 effectCol = { 0, 0, 0, 0 };
	std::string effectSymbol;

	if (spellCast->getType() == SpellType::ATTACK)
	{
		effectCol = { 255, 0, 0, 255 };
		effectSymbol = "-";
	}
	else if (spellCast->getType() == SpellType::HEAL)
	{
		effectCol = { 0, 255, 0, 255 };
		effectSymbol = "+";
	}

	p_visualEffects.push_back(new UIText({ 0, 0 }, 1.0f,
		new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48),
		"", effectCol));

	glm::vec2 tarPos = tarUnit->getPos();

	p_visualEffects.back()->activate(effectSymbol + std::to_string(spellCast->getDamage()),
		{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);

	p_visualEffects.push_back(new UIIcon({ 0, 0 }, 48, 48,
		spellCast->getTextureID(),
		spellCast->getColour()));

	p_visualEffects.back()->activate({ tarPos.x + 0.1f*TILE_WIDTH, tarPos.y },
		15);
}

void EffectManager::newCombatEffect(Unit* tarUnit, std::map<Debuff*, int> activeDebuffs)
{
	Solengine::ColourRGBA8 effectCol = { 0, 0, 0, 0 };
	std::string effectSymbol;

	for (std::map<Debuff*, int>::iterator it = activeDebuffs.begin(); it != activeDebuffs.end(); it++)
	{

		effectCol = { 255, 0, 0, 255 };
		effectSymbol = "-";

		p_visualEffects.push_back(new UIText({ 0, 0 }, 1.0f,
			new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48),
			"", effectCol));

		glm::vec2 tarPos = tarUnit->getPos();

		p_visualEffects.back()->activate(effectSymbol + std::to_string(it->first->getDamage()),
			{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);
	}

}