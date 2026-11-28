#include "../include/foxAndDot-SDK/Components/Group.h"

const sf::Drawable* const Group::as_drawable() const
{
    return nullptr;
}

void Group::update_resource(const std::variant<sf::Texture*, sf::Font*>&)
{
}

sf::FloatRect Group::get_component_bounds() const
{
    return sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(0,0));
}

sf::FloatRect Group::get_component_render_bounds() const
{
    return get_component_bounds();
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


void Group::set_margin(sf::Transformable* comp, const sf::Vector2f& margin)
{
    auto tr_comp = data.find(comp);
    if (tr_comp != data.end())
    {
        tr_comp->second = margin;
    }
    else
    {
        printf("Group WARNING: Group <%s> doesn't have the requested transformable component.\n",get_name().data());
    }
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
    else
    {
        printf("Group WARNING: Group <%s> doesn't have the requested transformable component.\n",get_name().data());
    }
}

