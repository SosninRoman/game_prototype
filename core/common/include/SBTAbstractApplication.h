//
// Created by G750 on 12.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTAPPLICATION_H
#define GAME_PROTOTYPE_SBTAPPLICATION_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "SBTContext.h"
#include "SBTGraphicResourceHolder.h"
#include "SBTGameWindow.h"
#include "SBTAbstractCommandManager.h"
#include "SBTStateStack.h"

class SBTAbstractApplication
{
public:
    typedef std::string GraphicResourceID;

    SBTAbstractApplication(SBTGameWindow* window, SBTAbstractCommandManager* manager, FontHolder* fonts,
    GraphicResourceHolder* grapRes);

    virtual ~SBTAbstractApplication() = default;

    virtual void                        run();

protected:
    virtual void				        registerStates() = 0;

    virtual void				        update(sf::Time dt);

    virtual void				        draw();

    virtual void				        handleInput();

    template<class ResourceClass>
    void loadGraphicResource(GraphicResourceID id, const std::string& filePath)
    {
        m_graphicResourcesHolder->load<ResourceClass>(id, filePath);
    }

    template<class ResourceClass>
    void loadGraphicResource(GraphicResourceID id, const std::string& filePath1, const std::string& filePath2)
    {
        m_graphicResourcesHolder->load<ResourceClass>(id, filePath1, filePath2);
    }

    template<class ConvertResource>
    void addGraphicResource(GraphicResourceID id, std::unique_ptr<ConvertResource> tilesheet)
    {
        m_graphicResourcesHolder->add(id, std::move(tilesheet) );
    }

    void loadFont(GraphicResourceID id, const std::string& filepath);

    void pushState(int id, state_param_ptr param = state_param_ptr(nullptr) );

    template<class GameStateClass>
    void registerState(int stateID);
private:
    std::unique_ptr<SBTGameWindow>			    m_window;

    std::unique_ptr<SBTAbstractCommandManager>	m_commandManager;

    //resources
    std::unique_ptr<FontHolder>			        m_fontHolder;

    std::unique_ptr<SBTStateStack>			    m_stateStack;

    std::unique_ptr<GraphicResourceHolder>      m_graphicResourcesHolder;

};

template<class GameStateClass>
void SBTAbstractApplication::registerState(int stateID)
{
    m_stateStack->registerState<GameStateClass>(stateID);
}
#endif //GAME_PROTOTYPE_SBTAPPLICATION_H
