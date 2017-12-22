//
// Created by G750 on 21.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTFRAME_H
#define GAME_PROTOTYPE_SBTFRAME_H
#include <SFML/Graphics.hpp>
#include <string>

class SBTFrame
{
public:
    SBTFrame() = default;

    SBTFrame(std::string name, int rectLeft, int rectTop, int rectWidth, int rectHeight):
            m_name(std::move(name) ),
            m_frame_rectangle(rectLeft, rectTop, rectWidth, rectHeight){}

    SBTFrame(int rectLeft, int rectTop, int rectWidth, int rectHeight):
            m_name(""),
            m_frame_rectangle(rectLeft, rectTop, rectWidth, rectHeight){}

    SBTFrame(sf::IntRect rect):m_name(""), m_frame_rectangle(rect){}

    SBTFrame(const SBTFrame& rhs){m_frame_rectangle = rhs.m_frame_rectangle;}

    int left() {return m_frame_rectangle.left;}
    int top() {return m_frame_rectangle.top;}
    int height() {return m_frame_rectangle.height;}
    int width() {return m_frame_rectangle.width;}
    const std::string& name() {return m_name;}

    const sf::IntRect getRect() const {return m_frame_rectangle;}
private:
    std::string m_name;
    sf::IntRect m_frame_rectangle;
};
#endif //GAME_PROTOTYPE_SBTFRAME_H
