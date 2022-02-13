#ifndef SVGOBJECT_HPP
#define SVGOBJECT_HPP
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <iterator>
#include <list>
#include <algorithm>
#include <time.h>
#include "pugixml.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "csscolorparser.hpp"

    int randomNumInRange(int rangeStart, int rangeEnd);
    std::string addZeroes(int number, int maxNumber);
    float linearInterpolate(float start, float end, int startFrame, int endFrame, int currentFrame);
    struct renderPair
        {
            std::string objectId, propertyName;
            int propertyType, startKeyframe, endKeyframe;
            std::string startValue, endValue;
        };
    //const std::list<> possibleAtributes={"stroke-width","stroke-dashoffset", "opacity", "rx", "ry", "cx", "cy", "pathLength", "width", "height", "x", "y", "fill-opacity","color"};
    const std::map<std::string, int> possibleAttributes = {
        {"stroke-opacity", 1},
        {"fill-opacity", 1},
        {"stroke-width", 1},
        {"stroke-dashoffset", 1},
        {"rx",1},
        {"ry",1},
        {"cx",1},
        {"cy",1},
        {"offset", 1},
        {"stroke-miterlimit", 1},
        {"fill-opacity", 1},
        {"path-length", 1},
        {"width", 1},
        {"height", 1},
        {"color", 2},
        {"fill", 2},
        {"stroke", 2},
        {"transform", 3}};

    class NatronSVGObject
    {
    public:

        pugi::xml_document *doc;
        pugi::xml_document *keyframeData;
        std::list<std::list<std::string>> propertyMap;
        std::list<int> keyframes;
        pugi::xpath_node_set GetObjectsList();

        void SetObjectAttributeAtKeyframe(std::string objectId, std::string attributeName, std::string value, unsigned int keyframeNum, std::string elementType = "*");
        void writeKeyframeData(std::string filename);
        void calcKeyframePoints();
        renderPair findNextReference(pugi::xml_node_iterator currentKeyframeNodeIterator, std::string objectId, std::string propertyName, std::string prevValue);
        void updateRenderingData(int keyframe);
        void readKeyframesFromFile(std::string filename);
        void displayPseudoGroups();
        void createPseudoGroup(std::string groupName, std::list<std::string> objectIds);
        void setPseudoGroupAtKeyframe(std::string groupName, std::string attributeName, std::string value, unsigned int keyframeNum, int randRangeStart = 0, int randRangeEnd = 0);
        void render(std::string folderName);
        void setKeyframeData();
        std::string ColorToRGBAString(CSSColorParser::Color clr);
    private:
        std::map<std::string, std::list<std::string>> pseudoGroups;

        std::list<renderPair> renderingData;
        void batchRender(std::string folderName);
        void writeSvg(std::string dir, std::string svgFilename, std::string outputFilename);
        int hex2int(char ch);
        std::string int2hex(int x);
        std::string transformInterpolate(renderPair rp, int currentKeyframe);
        std::map<std::string, std::list<float>> interpolateMap(std::map<std::string, std::list<float>> startMap, std::map<std::string, std::list<float>> endMap, int startKeyframe, int endKeyframe, int currentKeyframe);
        std::string createStringFromMap(std::map<std::string, std::list<float>> dataMap);
        std::string hexInterpolate(renderPair rp, int currentFrame);
        CSSColorParser::Color colorInterpolate(renderPair rp, int currentFrame);

        void removeRedundantSpaces(std::string *str);
        float linearInterpolate(renderPair rp, int currentFrame);
        float linearInterpolate(float startValue, float endValue, int startKeyframe, int endKeyframe, int currentFrame);
        void displayRenderPair(renderPair p);
        std::map<std::string, std::list<float>> createMap(std::string value);
        void displayRenderingData();

    };
#endif // SVGOBJECT_HPP