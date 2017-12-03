//
// Created by G750 on 23.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTSPRITEATLAS_H
#define GAME_PROTOTYPE_SBTSPRITEATLAS_H
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>

#include "SBTFrame.h"
#include "SBTSpriteSequence.h"
#include "SBTSequenceState.h"
//class SBTFrame;
//class SBTSpriteSequence;

//Сущность, представляющая абстракцию текстуры, состоящей из множества изображений.
//Текстура может содержать метаинформацию в формате xml, описывающую расположение конкретных кадров.
//Текстура также может содержать информацию в формате xml о составах логически
// связанных последовательностей - SBTSpriteSheetов.
//Данная сущность содержит непосредственно сам графический ресурс, полный набор кадров(опционально) и служит для
//создания сущностей, абстрагирующих последовательность кадров - SBTSpriteSheet'ов
//m_Texture - текстура, содержащая отрисовываемое изображение
//m_framesCollection - множество именованных последовательностей кадров, из которых состоит текстура
//m_spriteSequences - набор именованных последовательностей спрайтов
class SBTSpriteAtlas
{
public:
    typedef std::string FrameID;
    typedef std::string SpriteSequenceID;
    typedef std::string AnimationID;

    SBTSpriteAtlas() = default;
    explicit SBTSpriteAtlas(const sf::Texture& texture):m_texture(new sf::Texture(texture)){}
    explicit SBTSpriteAtlas(const std::string& atlasMetaFilePath);
    SBTSpriteAtlas(const std::string& atlasMetaFilePath, const std::string& sequencesMetaFilePath);

    void clearAll();//выгрузить текстуру, удалить последовательности и кадры

    void clearFrames();//удвлить кадры и последовательности

    void clearSequences();//удалить заполненные последовательности

    void loadTexture(const std::string& textureFilePath);

    void  addSequencesFromFile(const std::string& SpriteSequencesMetaFilePath );

    void addSequence(const SpriteSequenceID& sequenceID, const std::vector<SBTSequenceState>& sequnceBasis = std::vector<SBTSequenceState>());

    void addFrameToSequence(const SpriteSequenceID& seqID, const FrameID& frID);

    void addFrame(SBTFrame& frame);

    const sf::Texture& getTexture()const {return *m_texture;}

    const SBTFrame& getFrame(const FrameID& frmID) const;

    const SBTSpriteSequence& getSequence(const SpriteSequenceID& seqID) const;

    bool loadFromFile(const std::string& sequencesMetaFilePath);

    bool loadFromFile(const std::string& atlasMetaFilePath, const std::string& sequencesMetaFilePath);

    const std::string& getFileName() const;
private:
    void loadMetaInfo(const std::string& atlasMetaFilePath);
    void loadSequencesFromMetaFile(const std::string& sequencesMetaFilePath);

    std::unique_ptr<sf::Texture> m_texture;

    std::map<FrameID, SBTFrame> m_framesCollection;

    std::string m_fileName;

    std::map<SpriteSequenceID, SBTSpriteSequence> m_spriteSequences;
};
#endif //GAME_PROTOTYPE_SBTSPRITEATLAS_H
