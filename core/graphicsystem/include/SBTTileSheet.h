#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "SFML\Graphics.hpp"
#include "tinyxml2.h"
#include "SBTAbstractGraphicResource.h"
#include "SBTFrame.h"
#include "SBTAbstractSequence.h"

using std::vector;
using std::string;
using std::map;

class SBTTileSheet;
class SBTTileSequence;

//Представляет набор тайлов. Поскольку тайлы имеют одинаковый размер, можно не хранить набор кадров в виде именованных
//mFrame, а хранить количество колонок, размер тайла и общее количество тайлов. К отдкльному тайлу из коллекции можно
//обращаться по его порядковому номеру в наборе. Данный класс создается в предположении, что его загрузка будет
// производиться из файла с расширением tsx, созданного в редакторе TileMapEditor.
//m_name - имя набора тайлов, задаваемое в tsx файле. В настоящее время не используется в логике, но сохраняется на всякий
//m_filename -
class SBTTileSheet: public SBTAbstractGraphicResource
{
public:
    typedef std::string SpriteSequenceID;

	SBTTileSheet() = default;

    explicit SBTTileSheet(sf::Texture& texture):SBTAbstractGraphicResource(texture), m_fileName(""),
    m_columns(0), m_size(0), m_tileWidth(0), m_tileHeight(0){}

    explicit SBTTileSheet(const std::string& metaFilePath);

    ~SBTTileSheet() = default;

	bool                    loadFromFile(const std::string& filename) override;

    bool                    loadFromFile(const std::string& filename, const std::string& filename2) override
	{
		return false;
	}

	const string&			getFileName() const override;

    const SBTSequence&      getSequence(const SequenceID& seqID) const override;

    void                    loadTexture(const std::string& textureFilePath);

    void                    setTileWidth(int w){m_tileWidth = w;}

    void                    setTileHeight(int h){m_tileHeight = h;}

    void                    setColumsCount(int columns){m_columns = columns;}

    void                    setTileCount(int sz){m_size = sz;}

    SBTTileSequence&        addSequence(const SpriteSequenceID& seqID, std::vector<int> seqBasis = std::vector<int>());

    void                    addTileToSequence(const SpriteSequenceID& seqID, int tileNum);

	explicit operator sf::Texture&() {return *m_texture;}

	sf::Sprite				getTile(int tileid) const;

    SBTFrame                getFrame(int frameNum);
	
	int						getColumns() const {return m_columns;}

    int						getTileWidth() const {return m_tileWidth;}

    int						getTileHeight() const {return m_tileHeight;}

    int                     getTileCount() const {return m_size;}
private:
    string                                      m_name;
	string							            m_fileName; // имя файла
    string                                      m_filePath;// путь к файлу
	
	int								            m_columns; //количество колонок
	int								            m_size; //суммарное количество тайлов на текстуре
	int								            m_tileWidth;
	int								            m_tileHeight;

    map<SpriteSequenceID, SBTTileSequence>		m_tileSequences; //Наборы последовательностей тайлов
};


//Сущность, являющаяся набором логически связанных тайлов. Особенность тайлов в том, что они одинаковых размеров
//Содержит именованные последовательности, представляющие собой произвольное подмножество набора кадров
//Анимация в контексте данного класса - просто набор кадров, в отличии от класса SBTAnimation, где
//вводится время, за которое данная последовательность проигрывается и признак повторяемости
//m_frames_basis - базис, состоящий из множества произвольных кадров. Кадр описывается его порядковым номером в ресурсе
//m_texture - указатель на текстуру, из которой отображаются кадры

class SBTTileSequence: public SBTSequence
{
public:
    typedef std::string frameID;

    SBTTileSequence():m_resource(nullptr){}

    SBTTileSequence(
            SBTTileSheet* texture, std::vector<int> frames_basis):
            m_resource(texture), m_framesBasis(std::move(frames_basis) )
    {

    }

    void addFrame(int tileNum)
    {
        m_framesBasis.emplace_back(tileNum);
    }

    void addFramesSet(const std::vector<int>& set)
    {
        for(auto& frame : set)
        {
            addFrame(frame);
        }
    }

    void clearBasis(sf::Texture* texture){m_framesBasis.clear();}

    const std::vector<int>& getBasis(){return m_framesBasis;}

    SBTFrame getSequenceStateFrame(int frameNum) const override
    {
        return m_resource->getFrame(m_framesBasis[frameNum]);
    }

    int getSequenceStateAngle(int frameNum) const override
    {
        return 0;
    }

    const std::string& getMyResourceFileName() const override
    {
        return m_resource->getFileName();
    }

    int size() const override {return m_framesBasis.size();}
private:
    std::vector<int> m_framesBasis;

    SBTTileSheet* m_resource;
};