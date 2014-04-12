/*
 * sbsc_dna.h
 *
 *  Created on: Jan 10, 2013
 *      Author: fraser
 *
 * Takes an hsq code sequence and creates a self-replicating
 * and self-organizing matrix used to build the hsq application
 * structure. Once the decode and expansion process is complete,
 * the matrix has been transformed into the application structure
 *
 * Somewhat like crystal growth with some ideas from organic growth
 * Fractal growth methods will also be investigated
 *
 * Initial versions will be simple. One or two levels of unfolding.
 * Multi-level expansion later for methods that work properly
 *
 * Create a set of rules for construction of a node
 * Simple binary patterns define qty and type of elements in node
 * Binary patterns along with rules determine locations and types
 * of connections
 *
 */

#ifndef SBSC_DNA_H_
#define SBSC_DNA_H_

namespace sbsc {

class sbsc_dna {
public:
	sbsc_dna(hsq_sequence);
	virtual ~sbsc_dna();

	// contains sbsc_dna and decoded segment
	sbsc_dna replicate();

	Vector<sbsc_dna> expand(sbsc_dna);
	hsq_device extract();	// extract a device from a vector of sbsc_dna

	sbsc_lattice compound(hsq_sequence); // create scaffold for construction

	sbsc_realize(sbsc_lattice); // convert lattice to application

	sbsc_fractal(hsq_sequence); // replicate using mathematical and boolean equations

};

} /* namespace sbsc */
#endif /* SBSC_DNA_H_ */
