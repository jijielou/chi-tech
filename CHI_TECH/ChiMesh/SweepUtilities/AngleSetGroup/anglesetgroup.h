#ifndef _chi_angleset_group_h
#define _chi_angleset_group_h

#include "ChiMesh/SweepUtilities/AngleSet/angleset.h"



//###################################################################
/**Manages the workstages of a single angleset group.*/
class chi_mesh::sweep_management::AngleSetGroup
{
public:
  std::vector<chi_mesh::sweep_management::AngleSet*> angle_sets;

private:
  int current_angle_set = 0;


public:

  //###################################################################
  AngleSetStatus AngleSetGroupAdvance(SweepChunk *sweep_chunk,
                                      int anglesetgroup_number)
  {
    //====================================== Return finished if angle sets
    //                                       depleted
    if (current_angle_set >= angle_sets.size())
      return AngleSetStatus::FINISHED;

    //====================================== Execute current angleset
    AngleSetStatus completion_status = angle_sets[current_angle_set]->
      AngleSetAdvance(sweep_chunk, current_angle_set +
      anglesetgroup_number * angle_sets.size());

    //====================================== Check if angle set finished
    if (completion_status ==  AngleSetStatus::FINISHED)
    {
      current_angle_set++;
      if (current_angle_set >= angle_sets.size())
      {
        return AngleSetStatus::FINISHED;
      }
      return AngleSetStatus::NOT_FINISHED;
    }

    return AngleSetStatus::NOT_FINISHED;
  }



public:
  //#################################################################
  void ResetSweep()
  {
    current_angle_set = 0;

    for (int as=0; as<angle_sets.size(); as++)
      angle_sets[as]->ResetSweepBuffers();
  }

};

#endif