#include "VisualEffectManager.h"

#include "UIText.h"

VisualEffectManager::VisualEffectManager() {}

VisualEffectManager::~VisualEffectManager() {}

void VisualEffectManager::UpdateEffects(float adj)
{
	if (p_visualEffects.size() > 0)
		if (!p_visualEffects[0].first->UpdateEffect(adj))
			p_visualEffects.erase(p_visualEffects.begin());
		else if (!p_visualEffects[0].second->UpdateEffect(adj))
			p_visualEffects.erase(p_visualEffects.begin());
}

void VisualEffectManager::NewCombatEffect(Unit* tarUnit, Spell* spellCast)
{
	Solengine::ColourRGBA8 effectCol = { 0, 0, 0, 0 };
	std::string effectSymbol;

	if (spellCast->GetType() == SpellType::ATTACK)
	{
		effectCol = { 255, 0, 0, 255 };
		effectSymbol = "-";
	}
	else if (spellCast->GetType() == SpellType::HEAL)
	{
		effectCol = { 0, 255, 0, 255 };
		effectSymbol = "+";
	}

	glm::vec2 tarPos = tarUnit->GetPos();

	std::pair <Drawable*, Drawable*> visualEffect = { new UIText({ 0, 0 }, 1.0f,
		new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48), "", effectCol),
		new UIIcon({ 0, 0 }, 48, 48, spellCast->GetTextureID(), spellCast->GetColour()) };

	visualEffect.first->Activate(effectSymbol + std::to_string(spellCast->GetDamage()),
		{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);

	visualEffect.second->Activate({ tarPos.x + 0.1f*TILE_WIDTH, tarPos.y }, 15);

	p_visualEffects.push_back(visualEffect);
}

void VisualEffectManager::NewCombatEffect(Unit* tarUnit, std::map<StatusEffect*, int> activeStatusEffects)
{
	Solengine::ColourRGBA8 effectCol = { 0, 0, 0, 0 };
	std::string effectSymbol;

	for (std::map<StatusEffect*, int>::iterator it = activeStatusEffects.begin(); it != activeStatusEffects.end(); it++)
	{
		if (it->first->m_statusType == StatusType::DEBUFF)
		{
			effectCol = { 255, 0, 0, 255 };
			effectSymbol = "-";
		}
		else
		{
			effectCol = { 0, 255, 0, 255 };
			effectSymbol = "+";
		}

		glm::vec2 tarPos = tarUnit->GetPos();
		
		std::pair <Drawable*, Drawable*> visualEffect = { new UIText({ 0, 0 }, 1.0f,
	        new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48), "", effectCol),
	        new UIIcon({ 0, 0 }, 48, 48, it->first->GetTextureID(), it->first->GetColour()) };

		visualEffect.first->Activate(effectSymbol + std::to_string(it->first->GetDamage()),
			{ tarPos.x + 0.6f*TILE_WIDTH, tarPos.y + 0.6f*TILE_WIDTH }, 15);

		visualEffect.second->Activate({ tarPos.x + 0.1f*TILE_WIDTH, tarPos.y }, 15);

		p_visualEffects.push_back(visualEffect);
	}
}