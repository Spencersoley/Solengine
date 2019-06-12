#include "EffectManager.h"

#include "UIText.h"

EffectManager::EffectManager() {}

EffectManager::~EffectManager() {}

void EffectManager::updateEffects(float adj)
{
	if (p_visualEffects.size() > 0)
		if (!p_visualEffects[0].first->updateEffect(adj))
			p_visualEffects.erase(p_visualEffects.begin());
		else if (!p_visualEffects[0].second->updateEffect(adj))
			p_visualEffects.erase(p_visualEffects.begin());
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

	glm::vec2 tarPos = tarUnit->getPos();

	std::pair <Drawable*, Drawable*> visualEffect = { new UIText({ 0, 0 }, 1.0f,
		new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48), "", effectCol),
		new UIIcon({ 0, 0 }, 48, 48, spellCast->getTextureID(), spellCast->getColour()) };

	visualEffect.first->activate(effectSymbol + std::to_string(spellCast->getDamage()),
		{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);

	visualEffect.second->activate({ tarPos.x + 0.1f*TILE_WIDTH, tarPos.y }, 15);

	p_visualEffects.push_back(visualEffect);
}

void EffectManager::newCombatEffect(Unit* tarUnit, std::map<Debuff*, int> activeDebuffs)
{
	Solengine::ColourRGBA8 effectCol = { 0, 0, 0, 0 };
	std::string effectSymbol;

	for (std::map<Debuff*, int>::iterator it = activeDebuffs.begin(); it != activeDebuffs.end(); it++)
	{
		effectCol = { 255, 0, 0, 255 };
		effectSymbol = "-";

		glm::vec2 tarPos = tarUnit->getPos();
		
		std::pair <Drawable*, Drawable*> visualEffect = { new UIText({ 0, 0 }, 1.0f,
	        new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48), "", effectCol),
	        new UIIcon({ 0, 0 }, 48, 48, it->first->getTextureID(), it->first->getColour()) };

		visualEffect.first->activate(effectSymbol + std::to_string(it->first->getDamage()),
			{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);

		visualEffect.second->activate({ tarPos.x + 0.1f*TILE_WIDTH, tarPos.y }, 15);

		p_visualEffects.push_back(visualEffect);
	}
}