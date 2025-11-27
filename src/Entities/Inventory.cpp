#include "Entities/Inventory.hpp"

#include <algorithm>

//Funcion Init
void Inventory::Init(const std::string& slotTexturePath, unsigned slotW,
					 unsigned slotH, unsigned capacity, float spacing)
{
	m_slotW = slotW;
	m_slotH = slotH;
	m_capacity = capacity;
	m_spacing = spacing;
	m_basePos = sf::Vector2f(16.f, 16.f);

	if(!m_slotTexture.loadFromFile(slotTexturePath)) {
		throw std::runtime_error("Error al cargar la textura del slot");
	}

	// Si se pasa 0 en ancho o alto, usar el tamaño de la textura
	if (m_slotW == 0 || m_slotH == 0) {
		sf::Vector2u texSize = m_slotTexture.getSize();
		if (m_slotW == 0) m_slotW = texSize.x;
		if (m_slotH == 0) m_slotH = texSize.y;
	}
}

unsigned Inventory::capacity() const { return m_capacity; }
unsigned Inventory::size() const { return (unsigned)m_items.size(); }

void Inventory::insertAt(unsigned index, const Item& item) {
	if (m_items.empty()) {
		m_items.push_back(item);
		if (m_items.size() > m_capacity) m_items.pop_back();
		return;
	}
	if (index >= m_items.size()) {
		if (m_items.size() < m_capacity) m_items.push_back(item);
		else {
			auto it = m_items.begin();
			std::advance(it, std::min(index, (unsigned)m_items.size()));
			m_items.insert(it, item);
			while (m_items.size() > m_capacity) m_items.pop_back();
		}
		return;
	}
	auto it = m_items.begin();
	std::advance(it, index);
	m_items.insert(it, item);
	while (m_items.size() > m_capacity) m_items.pop_back();
}

std::optional<Item> Inventory::pickAt(unsigned index) {
	if (index >= m_items.size()) return std::nullopt;
	auto it = m_items.begin();
	std::advance(it, index);
	Item copy = *it;
	m_items.erase(it);
	return copy;
}

void Inventory::removeAt(unsigned index) {
	if (index >= m_items.size()) return;
	auto it = m_items.begin();
	std::advance(it, index);
	m_items.erase(it);
}

void Inventory::move(unsigned fromIndex, unsigned toIndex) {
	if (fromIndex == toIndex) return;
	if (fromIndex >= m_items.size() || toIndex > m_items.size()) return;
	auto itFrom = m_items.begin();
	std::advance(itFrom, fromIndex);
	auto itTo = m_items.begin();
	std::advance(itTo, toIndex);
	m_items.splice(itTo, m_items, itFrom);
}

bool Inventory::add(const Item& item) {
    if (m_items.size() < m_capacity) {
        m_items.push_back(item);
        return true;
    }
    return false;
}

void Inventory::removeById(int id) {
    for (auto it = m_items.begin(); it != m_items.end(); ++it) {
        if (it->id() == id) {
            m_items.erase(it);
            return;
        }
    }
}

sf::Vector2f Inventory::slotPosition(unsigned index) const {
	float drawW = float(m_slotW) * m_displayScale;
	float drawSpacing = m_spacing * m_displayScale;
	float x = m_basePos.x + (drawW + drawSpacing) * index;
	float y = m_basePos.y;
	return { x, y };
}

void Inventory::setBasePosition(sf::Vector2f basePos) {
	m_basePos = basePos;
}

int Inventory::indexAtScreenPos(sf::Vector2i mousePos, const sf::RenderWindow& window) const {
	float drawW = float(m_slotW) * m_displayScale;
	float drawH = float(m_slotH) * m_displayScale;
	for (unsigned i = 0; i < m_capacity; ++i) {
		sf::Vector2f pos = slotPosition(i);
		sf::FloatRect r(pos.x, pos.y, drawW, drawH);
		if (r.contains(float(mousePos.x), float(mousePos.y))) return int(i);
	}
	return -1;
}

void Inventory::draw(sf::RenderWindow& window) const {
	// Dibuja ranuras a partir del atlas de slots
	// Tamaño de dibujo de cada slot (aplicando escala visual)
	float drawW = float(m_slotW) * m_displayScale;
	float drawH = float(m_slotH) * m_displayScale;

	for (unsigned i = 0; i < m_capacity; ++i) {
		sf::Vector2f pos = slotPosition(i);
		if (m_slotTexture.getSize().x > 0) {
			sf::Sprite slot;
			slot.setTexture(m_slotTexture);
			// Usamos la textura completa para la ranura y escalamos a drawW/drawH
			sf::Vector2u tsize = m_slotTexture.getSize();
			slot.setTextureRect(sf::IntRect(0, 0, int(tsize.x), int(tsize.y)));
			float sx = drawW / float(tsize.x);
			float sy = drawH / float(tsize.y);
			slot.setScale(sx, sy);
			slot.setPosition(pos);
			window.draw(slot);
		}
	}
	// Dibuja items: centrados y escalados para caber dentro del slot con padding
	unsigned idx = 0;
	const float padding = 4.f * m_displayScale; // padding adaptado a escala
	const float itemScaleFactor = 0.7f; // items ocuparán hasta el 70% del espacio disponible
	for (const auto& item : m_items) {
		if (idx >= m_capacity) break;
		sf::Sprite it = item.sprite();
		sf::Vector2f pos = slotPosition(idx);
		sf::FloatRect b = it.getLocalBounds();
		float maxW = drawW - 2.f * padding;
		float maxH = drawH - 2.f * padding;
		float sx = 1.f, sy = 1.f;
		if (b.width > 0 && b.height > 0) {
			sx = maxW / b.width;
			sy = maxH / b.height;
			float s = std::min(sx, sy) * itemScaleFactor;
			it.setScale(s, s);
			// Después de escalar, usar getGlobalBounds() para conocer el tamaño final en pantalla
			sf::FloatRect gb = it.getGlobalBounds();
			it.setPosition(pos.x + (drawW - gb.width) / 2.f, pos.y + (drawH - gb.height) / 2.f);
		} else {
			it.setPosition(pos.x + (drawW - b.width) / 2.f, pos.y + (drawH - b.height) / 2.f);
		}
		window.draw(it);
		++idx;
	}
}

void Inventory::drawSlotBackgroundAt(sf::RenderWindow& window, sf::Vector2f topLeft) const {
	if (m_slotTexture.getSize().x == 0) return;
	sf::Sprite slot;
	slot.setTexture(m_slotTexture);
	sf::Vector2u tsize = m_slotTexture.getSize();
	slot.setTextureRect(sf::IntRect(0, 0, int(tsize.x), int(tsize.y)));
	float drawW = float(m_slotW) * m_displayScale;
	float drawH = float(m_slotH) * m_displayScale;
	float sx = drawW / float(tsize.x);
	float sy = drawH / float(tsize.y);
	slot.setScale(sx, sy);
	slot.setPosition(topLeft);
	window.draw(slot);
}

const Item* Inventory::itemAt(unsigned index) const {
	if (index >= m_items.size()) return nullptr;
	auto it = m_items.begin();
	std::advance(it, index);
	return &(*it);
}

Item* Inventory::itemAt(unsigned index) {
	if (index >= m_items.size()) return nullptr;
	auto it = m_items.begin();
	std::advance(it, index);
	return &(*it);
}

