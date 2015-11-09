#ifndef __PROJECT6_SENDER_H_
#define __PROJECT6_SENDER_H_

#include <omnetpp.h>

//
// _______________________________________________________________________________
// The following class defines the Sender module, i.e. the module that provides
// to the generation of the jobs flow.
// In this class are defined the following variables:
//      simtime_t iat, that is the Inter Arrival Time of the jobs
//      simsignal_t iatSig, that is the signal to store the IAT statistic
//
class Sender : public cSimpleModule
{
private:
    simsignal_t iatSig;
    simtime_t iat;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
