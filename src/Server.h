#ifndef __PROJECT6_SERVER_H_
#define __PROJECT6_SERVER_H_

#include <omnetpp.h>

//
// _______________________________________________________________________________
//
//
class Server : public cSimpleModule
{
private:
    simsignal_t stSig;
    simsignal_t rhoSig;
    simtime_t serviceTime;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
