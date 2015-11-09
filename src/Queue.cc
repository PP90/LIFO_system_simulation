#include "Queue.h"
#include<stack>
#include "Job_m.h"

Define_Module(Queue);

using namespace std;

//
// _______________________________________________________________________________________
// The following function initialize some statistics and, according to the assumption
// set the server to free, throught its boolean status flag "isServerFree"
//
void Queue::initialize()
{
    isServFree=true;
    N_q=registerSignal("N_q");
    qTimeSig=registerSignal("qTimeSig");
    dropCountSig=registerSignal("dropCountSig");
}

//
// _______________________________________________________________________________________
// The following function handle the incoming message "msg" and discriminate it through its
// attribute "kind", a default short int defined into the cMessage class. If:
//
//    ->kind=1, the message is a server status message, it update server status information
//      inside the queue module. The message will be deleted after that "isServFree" flag is
//      set to free.
//      Then it checks if the queue contains at least one job, in this case, the server
//      flag will be set to false (server busy) and a new job will be popped and sent to
//      the server.
//
//    ->kind=0, the message is a Job, it'll be forwarded in case of the server is
//      free, enqueued otherwise.
//
void Queue::handleMessage(cMessage *msg)
{
    if(msg->getKind()==1)
    {
        delete msg;
        isServFree=true;
        EV<<"Server free"<<endl;
        if(!simQueue.empty())
        {
            isServFree=false;
            Job *j=new Job();
            *j=simQueue.top();
            simQueue.pop();
            send(j,"out");
            EV<<"Job popped and sent."<<endl;
            emit(qTimeSig,simTime().dbl()-j->getDepartureTime());
        }
    }
    else
    {
        Job *j=check_and_cast<Job*>(msg);
        j->setID(simQueue.size());
        if(isServFree)
        {
            isServFree=false;
            send(j,"out");
            EV<<"Job sent directly."<<endl;
        }
        else
        {
            if((int)simQueue.size()<(int)par("queueDim"))
            {
                simQueue.push(*j);
                EV<<"Job pushed at position "<<simQueue.size()<<endl;
            }
            else
                {
                emit(dropCountSig,1);
                EV<<dropCountSig<<" Job dropped"<<endl;
                }
            emit(qTimeSig,simTime().dbl()-j->getDepartureTime());
            delete j;
        }
    }
    emit(N_q,simQueue.size());
}

