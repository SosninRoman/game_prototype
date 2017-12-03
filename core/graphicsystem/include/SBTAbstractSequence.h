//
// Created by G750 on 03.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H
#define GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H
#include <string>
#include <vector>
#include "SBTFrame.h"

class SBTSequence
{
public:
    SBTSequence() = default;
    virtual ~SBTSequence() = default;
    virtual const SBTFrame& getSequenceStateFrame(int frameNum) const = 0;
    virtual int getSequenceStateAngle(int frameNum) const = 0;
    virtual const std::string& getMyResourceFileName() const = 0;
    virtual int size() const = 0;
};

template<class Resource, class SequenceState>
class SBTTemplateSequence: public SBTSequence
{
public:
    typedef std::string frameID;

    SBTTemplateSequence():m_resource(nullptr){}

    explicit SBTTemplateSequence(Resource* resource,
                                 std::vector<SequenceState> frames_basis = std::vector<SequenceState>() ):
    m_resource(resource), m_framesBasis(frames_basis){}

    void addFrame(const SequenceState& frame)
    {
        m_framesBasis.emplace_back(frame);
    }

    void addFramesSet(const std::vector<frameID>& set)
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

    const std::vector<SequenceState>& getBasis()
    {
        return m_framesBasis;
    }

    const SBTFrame& getSequenceStateFrame(int frameNum) const override
    {
        //return m_framesBasis[frameNum].m_frame;
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
    std::vector<SequenceState> m_framesBasis;

    Resource* m_resource;
};
#endif //GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H
