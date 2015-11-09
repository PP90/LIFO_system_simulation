package project6.simulations;

//
// _______________________________________________________________________________
// 
//
simple Server
{
    parameters:
        @statistic[stSig](title="Service_Time"; source="stSig";record=vector,stats);
        @statistic[rhoSig](title="Utilization"; source="rhoSig";record=last);
        bool isScenario1=default(true);
        double meanSTexp=default(1);
        double meanSTlogn=default(1);
        double devSTlogn=default(1);
    gates:
    input in;
    output out;
}
