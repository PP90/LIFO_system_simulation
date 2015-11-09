#include "Sender.h"
#include "Job_m.h"
Define_Module(Sender);

//
// _______________________________________________________________________________
// This method initialize statistics and sends the first job. Then it schedule
// itself to receive a selfmessage.
//
void Sender::initialize()
{
    Job *job=new Job();
    job->setDepartureTime(0);
    job->setIat((double)par("meanIAT"));
    job->setID(0);
    send(job,"out");

    iatSig=registerSignal("iatSig");

    scheduleAt(simTime(),new cMessage());
}

//
// _______________________________________________________________________________
// The following method handles self messages scheduled every "iat" (i.e. a Random
// Variable exponentially distributed with mean set through the parameter "meanIAT")
// seconds in order to simulate the job stream incoming to the queue.
//
void Sender::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        iat=exponential((simtime_t)par("meanIAT"));
        Job *job=new Job();
        job->setDepartureTime(simTime().dbl());
        job->setIat((double)par("meanIAT"));
        send(job,"out");

        emit(iatSig,iat);

        delete msg;
        scheduleAt(simTime()+iat,new cMessage("Selfmessage"));
    }
}

