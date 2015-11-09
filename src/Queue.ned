package project6.simulations;

//
// _______________________________________________________________________________
// 
//
simple Queue
{
    parameters:
        @statistic[N_q](title="N_q"; source="N_q";record=vector,stats);
        @statistic[qTimeSig](title="Queueing_time";source="qTimeSig";record=vector,stats);
        @statistic[dropCountSig](title="#_of_dropped_jobs";source="dropCountSig";record=count);
        int queueDim=default(100000);
    gates:
        input in[];
        output out;
}
