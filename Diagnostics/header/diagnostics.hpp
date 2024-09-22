#ifndef __DIAGNOSTICS__H__
#define __DIAGNOSTICS__H__

#include "UpdateSesnors.hpp"


class Diagnostics: public Update_Sensors
{
    private:
    public:
      void ExcesiveSpeed_Check(void);


};


#endif  //!__DIAGNOSTICS__H__