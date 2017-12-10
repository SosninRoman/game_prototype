#pragma once
#include "SBTABstractAnimatedNode.h"
#include "LayerNode.h"
#include "RecieverTypeEnum.h"

class Paddle: public SBTAbstractAnimatedNode
{
public:
	enum class PaddleType
	{
		LeftPaddle = 0,
		RightPaddle = 1,
		NumOfTypes = 1 << 1,
	};

	//Paddle(RecieverType type , AtlasHolder& textures);
	Paddle(RecieverType type , GraphicResourceHolder& textures);
	
	sf::FloatRect			getGlobalBounds() const override;
	
	float					getSpeed() const;
		
	int				getNodeType() const override;
	int			getActionType() const override;

	void			centerOrigin() override;

private:
	void					updateCurrent(sf::Time dt) override;
	void					drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	RecieverType			mRecieverType;
	PaddleType				mType;
};

