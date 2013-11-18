#include ".\node.h"


// static initialisation
long node::leader_identity = 0;
node* node::leader_node = 0;
double node::handover_threshold = 0.0;
double node::threshold_multiplier = 0.0;


node::node(scheduler* gs, long id, nodelist& nl, pmmlcg* rand, processor_type myProc, double init_battery, double hot, long mngt_pkt_len, std::ofstream& op, double mult, double hop) 
: event_handler(gs), live_nodes(nl), leader_pkt_len(mngt_pkt_len), results_file(op), battery_energy(init_battery), handover_period(hop)
{
	identity = id;
	// Node 0 will always comsume 1st processor cycle
	if (identity == 0) {
		send_now(new event(EV_PROCESSOR));
		//send_now(new event(EV_TRIGGER_ELECTION));
		//send_now(new event(EV_GRADIENT_ELECTION));
	}
	
	alive = true;
	handover_threshold = hot;
	threshold_multiplier = mult;

	traff_rx = 0.0;
	traff_tx = 0.0;
	control_rx = 0.0;
	control_tx = 0.0;
	proc_consump = 0.0;

	// local variables to set traffic load in each node
	long m_pkt_len = 500; // mean packket length (bytes)
	double arrival_rate = 100 / 1e6; // number of packets per sec - then converted to microsecs
	double m_pkt_time = 1 /  arrival_rate; // mean time between packets (microseconds)
	rng = rand;
	activityGen = new trafficGen(rand, m_pkt_len, m_pkt_time);
	
	// This represents the management overhead of being the leader
	// the energy consumed depends on whether the device is a laptop
	// HIGHPOWER or a mobile phone LOWPOWER.
	// Only LOWPOWER is currently used
	if (myProc == HIGHPOWER) processor_usage = 0.0001; // equiv to 100 Watts over a second
	else processor_usage = 0.000001; // equiv to 1 Watt over a second

	// set the transmitter output power
	set_txPower(1e-3);

	// initialise internal data members for power consumption calculation
	mtx = 0.0;
	ctx = 0.0;
	mrx = 0.0;
	crx = 0.0;
	set_data_rate(ELEVEN); // initially set to 1Mb/s
	
	// start chain of packet transmissions
	send_now(new event(EV_TX_PACKET));
	//std::cerr << "\nNode(" << identity << ") created, address = " << this << "\t" << "Power = " << battery_energy;

	// build file name for local file on a node per node basis
	// this file can be used to dump debug info
	std::string filename = "Node";
	std::ostringstream idstring;
	idstring << identity;
	std::string extstring = ".dat";
	filename += idstring.str();
	filename += extstring;
	//open local file - note this file is not currently in usse
	//local_file.open(filename.c_str());
}

node::~node(void)
{
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
	delete activityGen;
	// note local debug file is not currently in use
	//	local_file.close();
	std::cerr << "Node (" << identity << ") deleted\n";
	std::cerr << "\nEnergy consumed due to reception of traffic = " << traff_rx
		<< "\nEnergy consumed due to transmission of traffic = " << traff_tx
		<< "\nEnergy consumed due to reception of control info = " << control_rx
		<< "\nEnergy consumed due to transmission of control info = " << control_tx
		<< "\nEnergy consumed due to processor = " << proc_consump
		<< "\nTotal energy consumed due to traffic = " << traff_rx + traff_tx
		<< "\nTotal energy consumed due to communication = " << traff_rx + traff_tx + control_rx + control_tx;
}

void node::handler(const event* received)
{
	switch(received->label) {
		case EV_PROCESSOR:
			send_delay(new event(EV_PROCESSOR, leader_node), 100.0); // schedule every 100 microseconds
			//processor_consume(100); // set to appropriate value later
			break;
		case EV_OVERHEAR:
			overhear_consume(10);  // set to appropriate value later
			break;
		case EV_TX_PACKET:
			send_delay(new event(EV_TX_PACKET), activityGen->getArrivalTime()); // schedule every 10 microseconds
			tx_packet(activityGen->getPktLen());
			break;
		case EV_TRIGGER_ELECTION:
			trigger_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
			send_delay(new event(EV_TRIGGER_ELECTION, leader_node), handover_period);
			break;
		case EV_GRADIENT_ELECTION:
			gradient_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
			send_delay(new event(EV_GRADIENT_ELECTION, leader_node), handover_period);
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement

}

void node::rx_consume(double bytes)
{
	battery_energy -= (mrx * bytes) + crx;
	traff_rx += (mrx * bytes) + crx;
	//local_file << "\n" << get_time() << "\t" << battery_energy;

	// the remaider of this function is not needed for time-based triggering
	
	if ((battery_energy <= handover_threshold) && (leader_identity == identity)) {
        trigger_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
		//gradient_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
	}
	
	// note these 2 lines are only needed for the gradient algorithm
	sample temp(get_time(), battery_energy);
	predictor.insert(temp);
	
}

void node::rx_consume_no_check(double bytes)
{
	battery_energy -= (mrx * bytes) + crx;
	control_rx += (mrx * bytes) + crx;
	if (battery_energy <= 0.0) alive = false;
}

void node::tx_consume(double bytes)
{
	battery_energy -= (mtx * bytes) + ctx;
	traff_tx += (mtx * bytes) + ctx;
	// the remaider of this function is not needed for time-based triggering
	
	if ((battery_energy <= handover_threshold) && (leader_identity == identity)) {
		trigger_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
	 //gradient_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
		
	}

	// note these 2 lines are only needed for the gradient algorithm
	sample temp(get_time(), battery_energy);
	predictor.insert(temp);
	
	
}

void node::tx_consume_no_check(double bytes)
{
	battery_energy -= (mtx * bytes) + ctx;
	control_tx += (mtx * bytes) + ctx;
	if (battery_energy <= 0.0) alive = false;
	sample temp(get_time(), battery_energy);
	predictor.insert(temp);
}

void node::processor_consume(double time)
{
	battery_energy -= time * processor_usage;
	proc_consump += time * processor_usage;
	// the remaider of this function is not needed for time-based triggering
	
	if ((battery_energy <= handover_threshold) && (leader_identity == identity)) 
		trigger_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
	 //gradient_election(live_nodes, identity, get_time(), (double) leader_pkt_len, handover_threshold, globalScheduler);
	 
	check_battery_power();
	
}

void node::overhear_consume(double time)
{
	// may change to bits later
	check_battery_power();

}

void node::backoff_consume(double time)
{

}



bool node::get_alive(void) const {
	return alive;
} // get_alive

void node::battery_exhausted(void)
{
	results_file << "\n" << static_cast<unsigned>(rng->get_init_stream()) << "\t" << get_time();
	alive = false;
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void node::set_data_rate(rate rt) 
{
	data_rate = rt;
	double txPowerSq = txPower * txPower;
    switch(data_rate) {
		case ONE:
			mtx = (-1.18e-3) * txPowerSq + (1.35e-4) * txPower + (1.12e-5);
			ctx = (-5.37e-2) * txPowerSq + (9.16e-3) * txPower + (1.02e-3);
			mrx = 1.03e-5;
			crx = 9.84e-4;
			break;
		case TWO:
			mtx = (-5.68e-4) * txPowerSq + (6.69e-5) * txPower + (5.62e-6);
			ctx = (-4.24e-2) * txPowerSq + (5.91e-3) * txPower + (6.62e-4);
			mrx = 5.20e-6;
			crx = 5.94e-4;
			break;
		case FIVEPOINTFIVE:
			mtx = (-2.38e-4) * txPowerSq + (2.59e-5) * txPower + (2.08e-6);
			ctx = (-2.91e-2) * txPowerSq + (4.04e-3) * txPower + (4.20e-4);
			mrx = 2.02e-6;
			crx = 3.91e-4;
			break;
		case ELEVEN:
			mtx = (-9.72e-5) * txPowerSq + (1.16e-5) * txPower + (1.07e-6);
			ctx = (-3.96e-2) * txPowerSq + (4.16e-3) * txPower + (3.50e-4);
			mrx = 1.04e-6;
			crx = 3.31e-4;
			break;
	} // end switch
}

void node::set_txPower(double power) 
{
	if ((power < 1e-3) || (power > 50e-3)) {
		std::cerr << "\nPower level invalid!!!!!!!!!!!!\n";
		return;
	} // if

	txPower = power;
	set_data_rate(data_rate); // must reset whenever power changes
}

void node::tx_packet(double bytes) {

	tx_consume(bytes);

	// call rx_consume in all nodes in neighbour vector except this node
	for_each(neighbour_list.begin(), neighbour_list.end(), std::bind2nd(std::mem_fun(rx_consume), bytes));
	check_battery_power();
}

void node::tx_packet_no_check(double bytes) {

	tx_consume_no_check(bytes);

	// call rx_consume in all nodes in neighbour vector except this node
	for_each(neighbour_list.begin(), neighbour_list.end(), std::bind2nd(std::mem_fun(rx_consume_no_check), bytes));

}

void node::print(void)
{
	std::cerr << "\nNode(" << identity << ") = " << this << "\tPower = " << battery_energy;
}

void node::determineNeighbours(void)
{
	
	neighbour_list.resize(live_nodes.size());
	std::copy(live_nodes.begin(), live_nodes.end(), neighbour_list.begin());
	neighbour_list.remove(this);
}

double node::get_energy(void)
{
	return battery_energy;
}

void node::trigger_election(nodelist& nodes, long ident, double when, double bytes, double hot, scheduler* gs)
{

	// first get each node to simulate power consumption incurred by
	// transmission of the management packet
	//for_each(nodes.begin(), nodes.end(), std::bind2nd(std::mem_fun(tx_packet_no_check), bytes));

	// now identify the node (other than this one) with the highest residual energy
	nodelist localList;
	localList.resize(nodes.size());
	std::copy(nodes.begin(), nodes.end(), localList.begin()); // local copy of all nodes

	// now remove all nodes below the handover threshold
	localList.remove_if(std::bind2nd(below_threshold(), hot));

	// if there are no nodes above the threshold then the list will be empty
	// consequently, we must simply choose the node with the highest power
	if (localList.empty()) {
		// put refill local node list with all nodes
		localList.resize(nodes.size());
		std::copy(nodes.begin(), nodes.end(), localList.begin());
		// instead of the above line could now change the handover threshold
		// to reduce the number of elections

		// this line is not required for time-based triggering
		 change_handover_threshold(nodes);
	} // if

	// need to remove nodes that are no longer alive
	localList.remove_if(dead_nodes());

	// sort nodes according to highest residual energy
	localList.sort(node_order());

	// node at top of the list is the new leader
	if (localList.empty()) {
		//std::cerr << "\nAll nodes dead: no leader";
		gs->stop();
	}
	else {
       	leader_identity = localList.front()->get_identity();
		leader_node = localList.front();
	} // else
}

void node::gradient_election(nodelist& nodes, long ident, double when, double bytes, double hot, scheduler* gs) {

	for_each(nodes.begin(), nodes.end(), std::bind2nd(std::mem_fun(tx_packet_no_check), bytes));

	// now identify the node (other than this one) with the highest residual energy
	nodelist localList;
	localList.resize(nodes.size());
	std::copy(nodes.begin(), nodes.end(), localList.begin()); // local copy of all nodes

	// sort nodes based on longest projected lifetime
	localList.sort(longest_life());

	// node at top of the list is the new leader
	if (localList.empty()) {
		//std::cerr << "\nAll nodes dead: no leader";
		gs->stop();
	}
	else {
      	leader_identity = localList.front()->get_identity();
		leader_node = localList.front();

		// this line is not required for time-based triggering
		change_handover_threshold(nodes);
	} // else
}

void node::end_the_sim(void) {

	// do stuff


}

double node::get_deathTime(void) {

	return (predictor.get_zero_crossing());

}

long node::get_identity(void) const {
	return identity;
}


// This function removes any nodes with no remaining battery power
// from list of active nodes and updates neighbour lists on
// each of these active nodes

void node::check_battery_power(void) {

	size_t previous_number_alive = live_nodes.size();
	// if below 0.0 then batterY_exhasuted is called
	// and the node is removed from the list
	live_nodes.remove_if(below_zero());
	// now need to get nodes to update their neighbour lists,
	// but only if one has expired, i.e. the number of nodes
	// has changed
	if (live_nodes.size() != previous_number_alive) 
		for_each(live_nodes.begin(), live_nodes.end(), std::mem_fun(node::determineNeighbours));
} // check_battery_power



// Normally an election is triggered only when the residual energy of the current
// leader goes below the handover threshold. However, when _all_ nodes are below
// the threshold
void node::change_handover_threshold(nodelist& alive_nodes) {

	//std::cerr << "\nChanging Handover Threshold, current value = " << handover_threshold;

	// decrement by a multiplier
	//handover_threshold *= threshold_multiplier;

	// set to multiplier times the mean power level
	handover_threshold = get_mean_energy(alive_nodes) * threshold_multiplier;

	//set to multiplier times the median power level
	//handover_threshold = get_median_energy(alive_nodes) * threshold_multiplier;

	// set to multiplier times the min power level
	//handover_threshold = get_min_energy(alive_nodes) * threshold_multiplier;



	//std::cerr << "\nNew value = " << handover_threshold;

}

double node::get_mean_energy(nodelist& alive_nodes) {
	mean_energy temp_var = for_each(alive_nodes.begin(), alive_nodes.end(), mean_energy());
	return temp_var.value();
}

double node::get_min_energy(nodelist& nodes) {
	//for_each(nodes.begin(), nodes.end(),std::mem_fun(print));
	double min = 0.0;
	if(nodes.size()){
        node* min_node = *min_element(nodes.begin(), nodes.end(), energy_min());
		min = min_node->get_energy();
	} 
	return min;
}

double node::get_median_energy(nodelist& alive_nodes) {
	if (alive_nodes.empty()) return 0.0;
	unsigned index = 0;
	double median = 0.0;

	nodelist localList;
	localList.resize(alive_nodes.size());
	std::copy(alive_nodes.begin(), alive_nodes.end(), localList.begin()); // local copy of all nodes
	localList.sort(energy_order());

	size_t num_nodes = alive_nodes.size();	
	nodeiterator localIterator = localList.begin();
	// calc of median depends on whether number of elements
	// is odd or even
	if (num_nodes & 0x01) { // bit-wise AND with LSB tells if its odd
		// odd
		index = static_cast<unsigned>(fabs(num_nodes / 2.0));
		advance(localIterator, index);
		median = (*localIterator)->get_energy();
		return median;
	}
	else {
		// even
		index = static_cast<unsigned>(fabs(num_nodes / 2.0));
		advance(localIterator, index - 1);
		median = (*localIterator)->get_energy();
		advance(localIterator, 1);
		median += (*localIterator)->get_energy();
		median /= 2.0;
		return median;
	}
	
}

void node::initial_leader(nodelist& nodes) {
	nodelist localList;
	localList.resize(nodes.size());
	std::copy(nodes.begin(), nodes.end(), localList.begin()); // local copy of all nodes

	// sort nodes according to highest residual energy
	localList.sort(node_order());
	leader_identity = localList.front()->get_identity();
	leader_node = localList.front();
	//std::cerr << "\nInitial leader is : " << leader_identity;


}