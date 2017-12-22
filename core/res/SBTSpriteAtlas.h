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
#include "SBTAbstractSequence.h"
#include "SBTAbstractGraphicResource.h"

class SBTSpriteSequence;
class SBTSequenceState;

//Сущность, представляющая абстракцию текстуры, состоящей из множества изображений.
//Текстура может содержать метаинформацию в формате xml, описывающую расположение конкретных кадров.
//Текстура также может содержать информацию в формате xml о составах логически
// связанных последовательностей - SBTSpriteSheetов.
//Данная сущность содержит непосредственно сам графический ресурс, полный набор кадров(опционально) и служит для
//создания сущностей, абстрагирующих последовательность кадров - SBTSpriteSheet'ов
//m_Texture - текстура, содержащая отрисовываемое изображение
//m_framesCollection - множество именованных последовательностей кадров, из которых состоит текстура
//m_spriteSequences - набор именованных последовательностей спрайтов
class SBTSpriteAtlas: public SBTAbstractGraphicResource
{
public:
    typedef std::string FrameID;
    typedef std::string SpriteSequenceID;

    SBTSpriteAtlas() = default;
    explicit SBTSpriteAtlas(const sf::Texture& texture):SBTAbstractGraphicResource(texture){}
    explicit SBTSpriteAtlas(const std::string& atlasMetaFilePath);
    SBTSpriteAtlas(const std::string& atlasMetaFilePath, const std::string& sequencesMetaFilePath);

    void clearAll();//выгрузить текстуру, удалить последовательности и кадры

    void clearFrames();//удвлить кадры и последовательности

    void clearSequences();//удалить заполненные последовательности

    void loadTexture(const std::string& textureFilePath);

    void addSequencesFromFile(const std::string& SpriteSequencesMetaFilePath );

    void addSequence(const SpriteSequenceID& sequenceID,
                     const std::vector<SBTSequenceState>& sequnceBasis = std::vector<SBTSequenceState>() );

    void addFrameToSequence(const SpriteSequenceID& seqID, const FrameID& frID);

    void addFrameToBasis(SBTFrame& frame);

    const SBTFrame& getFrame(const FrameID& frmID) const;

    const SBTSequence& getSequence(const SpriteSequenceID& seqID) const;

    bool loadFromFile(const std::string& sequencesMetaFilePath) override;

    bool loadFromFile(const std::string& atlasMetaFilePath, const std::string& sequencesMetaFilePath) override;

    const std::string& getFileName() const override;
private:
    void loadMetaInfo(const std::string& atlasMetaFilePath);
    void loadSequencesFromMetaFile(const std::string& sequencesMetaFilePath);

    std::map<FrameID, SBTFrame> m_framesCollection;

    std::string m_fileName;

    std::map<SpriteSequenceID, SBTSpriteSequence> m_spriteSequences;
};

//SBTSequenceState - класс, представляющий состояние кадра в последовательности
//Включает в себя имя кадра из текстурного атласа и угол, под которым он будет изображен.
//m_frameID - строковый идентификатор кадра в атласе
//m_angle - угол, под которым отрисовывается кадр
struct SBTSequenceState
{
    typedef std::string frameID;
    explicit SBTSequenceState(const frameID& frmID, int angl = 0):
            m_frameID(frmID), m_angle(angl)
    {}

    frameID m_frameID;

    int m_angle = 0;
};

//Класс представляет собой последовательность спрайтов, выделенную из множества кадров текстурного атласа
//m_resource - указатель на ресурс, из которого выделена последовательность
//m_frameBasis - непосредственно последовательность состояний SBTSequenceState, представляющих последовательность
//Каждый SBTSequenceState содержит в себе SBTFrame + угол поворота, под которым необходимо отрисовать кадр
class SBTSpriteSequence: public SBTSequence
{
public:
    typedef std::string frameID;

    SBTSpriteSequence():m_resource(nullptr){}

    explicit SBTSpriteSequence(SBTSpriteAtlas* resource,
                                 std::vector<SBTSequenceState> frames_basis = std::vector<SBTSequenceState>() ):
            m_resource(resource), m_framesBasis(frames_basis){}

    void addFrame(const SBTSequenceState& frame)
    {
        m_framesBasis.emplace_back(frame);
    }

    void addFramesSet(const std::vector<SBTSequenceState>& set)
    {
        for(auto& frame : set)
        {
            addFrame(frame);
        }
    }

    void clearBasis(sf::Texture* texture)
    {
        m_framesBasis.clear();
    }

    const std::vector<SBTSequenceState>& getBasis()
    {
        return m_framesBasis;
    }

    SBTFrame getSequenceStateFrame(int frameNum) const override
    {
        return m_resource->getFrame(m_framesBasis[frameNum].m_frameID);
    }

    int getSequenceStateAngle(int frameNum) const override
    {
        return m_framesBasis[frameNum].m_angle;
    }

    const std::string& getMyResourceFileName() const override
    {
        return m_resource->getFileName();
    }

    int size() const override
    {
        return m_framesBasis.size();
    }
private:
    std::vector<SBTSequenceState> m_framesBasis;

    SBTSpriteAtlas* m_resource;
};

#endif //GAME_PROTOTYPE_SBTSPRITEATLAS_H
