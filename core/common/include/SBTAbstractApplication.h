//
// Created by G750 on 12.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTAPPLICATION_H
#define GAME_PROTOTYPE_SBTAPPLICATION_H
#include "SBTGameWindow.h"
#include "SBTAbstractCommandManager.h"
#include "SBTStateStack.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "SBTContext.h"
#include "SBTAtlasHolder.h"
#include "SBTTileSheetHolder.h"

class SBTAbstractApplication
{
public:
    SBTAbstractApplication(SBTGameWindow* window, SBTAbstractCommandManager* manager, FontHolder* fonts, TextureHolder* txtrs,
    AtlasHolder* atl, TileSheetHolder* tsh);

    virtual ~SBTAbstractApplication();

    virtual void                        run();

protected:
    virtual void				        registerStates() = 0;

    virtual void				        update(sf::Time dt);

    virtual void				        draw();

    virtual void				        handleInput();

    void loadTexture(int id, const std::string& filepath);

    void loadFont(int id, const std::string& filepath);

    void pushState(int id, state_param_ptr param = state_param_ptr(nullptr) );

    template<class GameStateClass>
    void registerState(int stateID);
private:
    std::unique_ptr<SBTGameWindow>			mWindow;

    std::unique_ptr<SBTAbstractCommandManager>	mCommandManager;

    //resources
    std::unique_ptr<FontHolder>			mFontHolder;

    std::unique_ptr<TextureHolder>		mTextureHolder;

    std::unique_ptr<SBTStateStack>			mStateStack;

    std::unique_ptr<TileSheetHolder>    mTileSheetHolder;

    std::unique_ptr<AtlasHolder>        mAtlasHolder;

};

template<class GameStateClass>
void SBTAbstractApplication::registerState(int stateID)
{
    mStateStack->registerState<GameStateClass>(stateID);
}
#endif //GAME_PROTOTYPE_SBTAPPLICATION_H
