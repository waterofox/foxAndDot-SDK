#include "../include/foxAndDot-SDK/Components/Group.h"

sf::Drawable* Group::as_drawable()
{
    return nullptr;
}

void Group::update_resource(const std::variant<sf::Texture*, sf::Font*>&)
{
}

sf::FloatRect Group::get_component_bounds()
{
    return sf::FloatRect();
}

sf::FloatRect Group::get_component_render_bounds()
{
    return sf::FloatRect();
}

Group::Group()
{
    set_visble(false);
    set_intersection(false);

    set_resource_and_type(-1, Resource_Types::Undefined);
}

void Group::update()
{
    for (auto& comp : data)
    {
        comp.first->setPosition(this->getPosition());
        comp.first->move(comp.second);
    }
}

const Scene_Component* Group::as_component()
{
    return static_cast<Scene_Component*>(this);
}

void Group::add(sf::Transformable* trbl, const sf::Vector2f& margin)
{
    data[trbl] = margin;
}

void Group::remove(sf::Transformable* trbl)
{
    if (data.find(trbl) != data.end())
    {
        data.erase(trbl);
    }
}

