#pragma once

#include <list>
#include <algorithm>
#include <functional>
#include "event_handler.h"
#include "event_definitions.h"
#include "trafficGen.h"
#include "estimator.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

class node;
typedef std::list<node*> nodelist;
typedef nodelist::iterator nodeiterator;
enum processor_type{LOWPOWER, HIGHPOWER};
enum rate {ONE, TWO, FIVEPOINTFIVE, ELEVEN};



class node :
	public event_handler
{
public:
	node(scheduler* gs, long id, nodelist& nl, pmmlcg* rand, processor_type myProc, double init_battery, 
		double hot, long mngt_pkt_len, std::ofstream& op, double mult, double hop);
	virtual ~node(void);
	void rx_consume(double bytes);
	void print(void);
	void determineNeighbours(void);
	double get_energy(void);
	long get_identity(void) const;
	bool get_alive(void) const;
	void battery_exhausted(void);
	double get_deathTime(void);
	static void initial_leader(nodelist& nodes);
protected:
	virtual void handler(const event* received);
	void tx_consume(double bytes);
	void tx_consume_no_check(double bytes);
	void rx_consume_no_check(double bytes);
	void tx_packet(double bytes);
	void tx_packet_no_check(double bytes);
	void backoff_consume(double microseconds);
	void processor_consume(double microseconds);
	void overhear_consume(double microseconds);
	static void change_handover_threshold(nodelist& alive_nodes);
	static double threshold_multiplier;
	void set_data_rate(rate rt);
	void set_txPower(double power);
	void check_battery_power(void);
	static void trigger_election(nodelist& nodes, long ident, double when, double bytes, double hot, scheduler* gs);
	static void gradient_election(nodelist& nodes, long ident, double when, double bytes, double hot, scheduler* gs);
	void end_the_sim(void);
	double battery_energy;
	double processor_usage;
	double txPower;
	double mtx;
	double ctx;
	double mrx;
	double crx;
	static double handover_threshold;
	nodelist neighbour_list;
	nodelist& live_nodes;
	trafficGen* activityGen;
	long identity;
	static long leader_identity;
	static node* leader_node;
	long leader_pkt_len;
	rate data_rate; // values can be 1, 2, 5.5, 11
	std::ofstream& results_file;
	std::ofstream local_file;
	bool alive;
	static double get_mean_energy(nodelist& alive_nodes);
	static double get_median_energy(nodelist& alive_nodes);
	static double get_min_energy(nodelist& alive_nodes);
	estimator predictor;
	pmmlcg* rng;
	const double handover_period; // used on for time-based triggering simulations
	// below are some temporary test vars to understand the system
	double traff_tx;
	double traff_rx;
	double control_tx;
	double control_rx;
	double proc_consump;


};

class below_threshold: public std::binary_function<node*, double, bool> {
public:
	// overload the () operator
	result_type operator()(first_argument_type inputa, second_argument_type inputb) const{
		if (inputa->get_energy() <= inputb) return true;
		else return false;
		} // () overload
}; // below_threshold

class below_zero: public std::unary_function<node*, bool> {
public:
	// overload the () operator
	result_type operator()(argument_type inputa) const{
		if (inputa->get_energy() <= 0.0) {
			inputa->battery_exhausted();
			return true;
		}
		else return false;
		} // () overload
}; // below_zero


class node_order: public std::binary_function<node*, node*, bool> {
public:
	// overload the () operator
	result_type operator()(first_argument_type inputa, second_argument_type inputb) const{
        if (inputa->get_energy() > inputb->get_energy()) return true;
		else return false;
		} // () overload
}; // node_order

class dead_nodes: public std::unary_function<node*, bool> {
public:
	// overload () operator
	result_type operator()(argument_type inputa) const {
		if (inputa->get_alive() == false) return true;
		else return false;
	} // () overload
}; // dead_nodes




class mean_energy : public std::unary_function<node*, double>{
private:
	double total_energy;
	unsigned num_nodes;
public:
	mean_energy() : total_energy(0.0), num_nodes(0) {}; // ctor
	void operator() (argument_type localNode) {
		total_energy += localNode->get_energy();
		num_nodes++;
	}
	result_type value() {return total_energy / num_nodes;}
}; // total_value

class energy_order {
public:
	// overload the () operator
	bool operator()(node* inputa, node* inputb) const{
		if (inputa->get_energy() > inputb->get_energy()) return false;
		else return true;
	} // () overload
}; // energy_order


// note this class is based on energy_order
// is has the same behaviour 
class energy_min: public std::binary_function<node*, node*, bool> {
public:
	// overload the () operator
	bool operator()(first_argument_type inputa, second_argument_type inputb) const{
		if (inputa->get_energy() < inputb->get_energy()) return true;
		else return false;
	} // () overload
}; // energy_min

class longest_life: public std::binary_function<node*, node*, bool> {
public:
	// overload the () operator
	result_type operator()(first_argument_type inputa, second_argument_type inputb) const{
        if (inputa->get_deathTime() > inputb->get_deathTime()) return true;
		else return false;
		} // () overload
}; // longest_life