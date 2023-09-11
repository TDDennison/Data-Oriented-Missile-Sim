#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#include "../MathTypes/Vector3.h"
#include "../Components/Utilities.h"
#include "../Constants.h"

// Singleton class used to hold pertinent configuration data for a run that may be needed
// during the course of the run.
class Configurations
{
    public:
    static Configurations* GetInstance() {
        if(instance == nullptr) { instance = new Configurations(); }
        return instance;
    }

    std::filesystem::path GetInputFilePath() { return inputFilePath_; }
    void SetInputFilePath(std::filesystem::path inputPath) { inputFilePath_ = inputPath; }

    //================================================================================
    // Missile Starting Locations
    //================================================================================
    void AddMissileStartingLocation(std::pair<float, float> latLonPair)
    {
        missileStartingLocations_.push_back(latLonPair);
    }

    std::vector<std::pair<float, float>>& GetMissileStartingLocations()
    {
        return missileStartingLocations_;
    }

    //================================================================================
    // Target Intercept Points
    //================================================================================
    void AddTargetInterceptPoint(Vector3 interceptPoint)
    {
        targetInterceptPoints_.push_back(interceptPoint);
    }

    std::vector<Vector3>& GetTargetInterceptPoints()
    {
        return targetInterceptPoints_;
    }

    //================================================================================
    // Object Geometry
    //================================================================================
    Vector3 GetObjectGeometry(unsigned short objId)
    {

        // NOTE: MOVE THESE GEOMETRIES TO THE INPUT FILES WHEN POSSIBLE

        uint8_t componentIdRaw = (objId & 0x0F);
        ComponentUtilities::ComponentDesignators componentId = static_cast<ComponentUtilities::ComponentDesignators>(componentIdRaw);

        switch(componentId)
        {
            case ComponentUtilities::ComponentDesignators::FIRST_STAGE_SRM:
            {
                // Length, width, height in the object frame, with the object frame's axes aligning with the missile frames axes.
                // This is an overall summation.

                // If a 3D rectangle's smallest face is located on plane and centered at the origin of a reference frame with:
                // a length of 10 units in only the positive x-axis
                // a length of 1 unit in both the positive and negative directions along the y-axis
                // a length of 1 unit in both the positive and negative directions along the z-axis
                // The end result of summing the dimensions in each axis would be <10, 0, 0>
                Vector3 lwh{10, 0, 0};
                return lwh;
                break;
            }
            case ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM:
            {
                // Length, width, height in the object frame, with the object frame's axes aligning with the missile frames axes.
                Vector3 lwh{5, 0, 0};
                return lwh;
                break;
            }
            default:
            {
                return Vector3::Zero();
                break;
            }
        }
    }

    Vector3 GetObjectOffset(unsigned short objId)
    {
        // NOTE: MOVE THESE OFFSETS TO THE INPUT FILES WHEN POSSIBLE

        uint8_t componentIdRaw = (objId & 0x0F);
        ComponentUtilities::ComponentDesignators componentId = static_cast<ComponentUtilities::ComponentDesignators>(componentIdRaw);

        switch(componentId)
        {
            case ComponentUtilities::ComponentDesignators::FIRST_STAGE_SRM:
            {
                return Constants::FIRST_STAGE_BOOSTER_OFFSET_FROM_ORIGIN;
                break;
            }
            case ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM:
            {
                return Constants::SECOND_STAGE_BOOSTER_OFFSET_FROM_ORIGIN;
                break;
            }
            default:
            {
                return Vector3::Zero();
                break;
            }
        }
    }

    // Checks to make sure that all configurations that are necessary for a run to start are set properly.
    std::pair<bool, std::string> ValidateConfigurations()
    {
        if(inputFilePath_.empty()) { return std::pair<bool, std::string>(false, "Input file path has not been declared.");}

        // All configurations valid
        return std::pair<bool, std::string>(true, "");
    }

    private:
    Configurations(){};
    inline static Configurations* instance = nullptr;

    std::filesystem::path inputFilePath_;

    std::vector<std::pair<float, float>> missileStartingLocations_{};
    std::vector<Vector3> targetInterceptPoints_{};
};

#endif //CONFIGURATIONS_H