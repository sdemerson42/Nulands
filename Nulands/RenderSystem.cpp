#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Entity.h"
#include "CameraComponent.h"

void RenderSystem::update()
{
	fillVas();
	drawVas();
}

void RenderSystem::fillVas()
{
	m_vaMap.clear();

	for (int i = 0; i < AutoList<RenderComponent>::size(); ++i)
	{
		RenderComponent *rcp = AutoList<RenderComponent>::get(i);
		if (rcp->active())
		{
			std::string fName{ rcp->fName() };

			auto tmp = m_textureMap.find(fName);
			if (tmp == m_textureMap.end())
			{
				m_textureMap[fName] = sf::Texture{};
				m_textureMap[fName].loadFromFile("data\\textures\\" + fName);
			}

			auto vap = m_vaMap.find(fName);
			if (vap == m_vaMap.end())
			{
				m_vaMap[fName] = sf::VertexArray{ sf::PrimitiveType::Quads, 0 };
				vap = m_vaMap.find(fName);
			}

			float w = rcp->m_texSize.x;
			float h = rcp->m_texSize.y;
			float tx = rcp->m_texCoord.x;
			float ty = rcp->m_texCoord.y;
			float x = rcp->getParent()->position().x;
			float y = rcp->getParent()->position().y;

			vap->second.append(sf::Vertex{ sf::Vector2f{x, y}, sf::Vector2f{tx, ty} });
			vap->second.append(sf::Vertex{ sf::Vector2f{ x + w, y }, sf::Vector2f{ tx + w, ty } });
			vap->second.append(sf::Vertex{ sf::Vector2f{ x + w, y + h }, sf::Vector2f{ tx + w, ty + h } });
			vap->second.append(sf::Vertex{ sf::Vector2f{ x, y + h }, sf::Vector2f{ tx, ty + h } });
		}
	}
}

void RenderSystem::drawVas()
{
	if (AutoList<CameraComponent>::size() == 0) return;
	auto c = AutoList<CameraComponent>::get(0);

	m_windowRef->clear();
	m_windowRef->setView(c->m_view);

	for (auto &p : m_vaMap)
		m_windowRef->draw(p.second, sf::RenderStates{ &m_textureMap.find(p.first)->second });

	m_windowRef->display();
}