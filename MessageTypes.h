#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_YouAreDumb,
  Msg_Fight,
  Msg_Hello,
  Msg_Kick,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case   Msg_YouAreDumb:

	  return "YouAreDumb";

  case   Msg_Fight:

	  return "Fight";

  case   Msg_Hello:

	  return "Hello";

  case   Msg_Kick:

	  return "Kick";

  default:

    return "Not recognized!";
  }
}

#endif