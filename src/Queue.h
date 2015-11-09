#ifndef __PROJECT6_QUEUE_H_
#define __PROJECT6_QUEUE_H_


#include <omnetpp.h>
#include<stack>
#include "Job_m.h"


//
// _______________________________________________________________________________
// The following is the class definition of the Queue, that is the module
// used for storing incoming jobs.
// Here there is the definition for the following:
//      std::stack<Job> simQueue, the data structure used to implement the queue
//      bool isServFree, a boolean used to store the server status
//      simsignal_t N_q, the signal used to retrieve the # of jobs in the queue
//      simsignal_t N, the signal used to retrieve the # of jobs in the system
//

class Queue : public cSimpleModule
{
private:
    std::stack<Job> simQueue;
    bool isServFree;
    simsignal_t N_q;
    simsignal_t qTimeSig;
    simsignal_t dropCountSig;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
